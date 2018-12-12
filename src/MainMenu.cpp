/**
  *   @file MainMenu.cpp
  *   @brief Source file for class MainMenu
  */


#include "MainMenu.hpp"


// Assign the class variable to match the amount of buttons
int MainMenu::MainMenuButtons = 5;



/*  Class MainMenu  */


/*  Constructor */

MainMenu::MainMenu(sf::RenderWindow &parent_window, sf::RenderWindow &dialog,
                  sf::RenderWindow &help):
UI(parent_window, dialog, help, sf::Color(150, 200, 255, 255))
{
  ui_view = window.getDefaultView();
  CreateMainMenu();
}


/*  Create / recreate window for MainMenu */
void MainMenu::createMainScreen()
{
  // Set window active
  window_status = true;

  window.setSize(sf::Vector2u(Game::WIDTH, Game::HEIGHT));
  window.setTitle("Main Menu");
  // Reset view and update set it to window
  ui_view.reset(sf::FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
  window.setView(ui_view);

  // init game_mode
  game_mode = Game::GameMode::SinglePlayer;
}

/* Draw UI */

void MainMenu::DrawUI()
{
  for (auto &button : buttons) {
    // Draw buttons
    window.draw(*button);
  }
  // Draw background_img
  window.draw(background_img);
}


/* Handle key presses */

 void MainMenu::HandleKeyPress(sf::Event event)
 {

   if (event.key.code == sf::Keyboard::Escape)
   {
     // Close window
     CloseWindow();
   }
   else if (event.key.code == sf::Keyboard::Up)
   {
     UpdateActiveButton(BUTTON_PREV);
   }
   else if (event.key.code == sf::Keyboard::Down)
   {
     UpdateActiveButton(BUTTON_NEXT);
   }
   else if (event.key.code == sf::Keyboard::Tab)
   {
     UpdateActiveButton();
   }
   else if (event.key.code == sf::Keyboard::Return)
   {
     // In older sfml version there is no Enter
     ClickCurrentButton();
   }

 }

/* Handle mouse moving */

 void MainMenu::HandleMouseMove(sf::Event event)
 {
   auto x = static_cast<float>(event.mouseMove.x);
   auto y = static_cast<float>(event.mouseMove.y);

   int i = 0;
   for (auto it = buttons.begin(); it != buttons.end(); it++)
   {
     if ( (*it)->tryActivate(x, y) )
     {
       // Correct current_button
       current_button = i;
       int j = 0;
       for (auto &button : buttons) {
         // Deactivate other buttons
         if (j != i)
         {
           button->activate(false);
         }
         j ++;
       }
       break;
     }
     i ++;
   }
   if (i == MainMenu::MainMenuButtons)
   {
     // No Button was activated, reset current_button
     current_button = -1;
   }
 }


/*  Check if some button is pressed */

 void MainMenu::HandleMousePress(sf::Event event)
 {
   if (event.mouseButton.button == sf::Mouse::Left)
   {
     auto x = static_cast<float>(event.mouseButton.x);
     auto y = static_cast<float>(event.mouseButton.y);
     for (auto &button : buttons) {
       // Check if clicked
       button->checkClicked(x, y);
     }
   }

 }

/* Update Buttons */

 void MainMenu::UpdateActiveButton(int action)
 {
   if ( (action == BUTTON_NEXT) && (current_button < MainMenu::MainMenuButtons -1) )
   {
     current_button ++;
   }

   else if ( (action == BUTTON_PREV) && (current_button > 0) )
   {
     current_button --;
   }
   // Activate the correct button
   ActivateCurrentButton();
 }

 /* Update active button */
 void MainMenu::UpdateActiveButton()
 {
   if (current_button < MainMenu::MainMenuButtons - 1)
   {
     current_button ++;
   } else {
     current_button = 0;
   }
   // Activate Button
   ActivateCurrentButton();

 }


/*  Create main menu */

void MainMenu::CreateMainMenu()
{
  // Create Buttons
  // First create the button with longest text and match other widths to it
  std::shared_ptr<Button> select_level = std::make_shared<Button>("Start Game", sf::Color::Blue);
  select_level->setPosition(100, 80);
  buttons.push_back(select_level);
  unsigned width = select_level->getWidth();
  unsigned height = select_level->getHeight();
  std::shared_ptr<Button> start_editor = std::make_shared<Button>("Editor",
                                    sf::Color::Blue, width, height);
  std::shared_ptr<Button> start_stats = std::make_shared<Button>("Stats",
                                    sf::Color::Blue, width, height);
  std::shared_ptr<Button> controls = std::make_shared<Button>("Controls",
                                    sf::Color::Blue, width, height);
  std::shared_ptr<Button> quit = std::make_shared<Button>("Quit",
                                    sf::Color::Blue, width, height);
  start_editor->setPosition(100, 180);
  buttons.push_back(start_editor);
  start_stats->setPosition(100, 280);
  buttons.push_back(start_stats);
  controls->setPosition(100, 380);
  buttons.push_back(controls);
  quit->setPosition(100, 480);
  buttons.push_back(quit);

  // Set click_actions IMPORTANT
  select_level->setClickFunction(std::bind(&MainMenu::select_level_action, this));
  start_editor->setClickFunction(std::bind(&MainMenu::start_editor_action, this));
  start_stats->setClickFunction(std::bind(&MainMenu::start_stats_action, this));
  controls->setClickFunction(std::bind(&MainMenu::controls_action, this));
  quit->setClickFunction(std::bind(&MainMenu::CloseWindow, this));

  // Set active colors
  select_level->setActiveColor(sf::Color(15, 10, 75));
  start_editor->setActiveColor(sf::Color(15, 10, 75));
  start_stats->setActiveColor(sf::Color(15, 10, 75));
  controls->setActiveColor(sf::Color(15, 10, 75));
  quit->setActiveColor(sf::Color(15, 10, 75));

  // Construct background_img
  if (background_img_texture.loadFromFile("../data/img/SPITFIRE.png"))
  {
    background_img = sf::Sprite(background_img_texture);
    background_img.setPosition(500, 100);
  }


}


/* Activate current_button */

void MainMenu::ActivateCurrentButton()
{
  int i = 0;
  for (auto &button : buttons) {
    if (i != current_button)
    {
      button->activate(false);
    } else {
      button->activate(true);
    }
    i++;
  }
}

/* Click current_button */

void MainMenu::ClickCurrentButton()
{
  if ((current_button) > -1 && (current_button < MainMenu::MainMenuButtons))
  {
    buttons[current_button]->clickAction();
  }
}

/*  Activate level select */
void MainMenu::select_level_action()
{
  CreateSelectLevel();
}

/*  Switch to LevelEditor */
void MainMenu::start_editor_action()
{
  // Set correct exit status
  exit_status = ExitStatus::STARTEDITOR;

  window_status = false;
}

/*  Switch to Stats */
void MainMenu::start_stats_action()
{
  // Set correct exit_status
  exit_status = ExitStatus::STATS;
  window_status = false;
}

/*  Construct and show controls help screen */
void MainMenu::controls_action()
{
  // Create and activate help window
  help_window.create(sf::VideoMode(400, 500), "Help", sf::Style::Close);
  help_font.loadFromFile(FONT_ARIAL);
  help_title = sf::Text("Controls" , help_font, 30);
  help_title.setStyle(sf::Text::Bold | sf::Text::Underlined);
  help_title.setPosition(100, 20);
  help_title.setColor(sf::Color::Blue);

  help_text = sf::Text("Sorry, Controls unavailable", help_font, 12);
  help_text.setPosition(50, 70);
  help_text.setColor(sf::Color::Black);

  // Load text from file
  std::string help_content;
  std::ifstream file("../data/misc/controls.txt");
  if (file.is_open())
  {
    std::string line;
    while(getline(file, line))
    {
      // Read all lines to help_content
      help_content += line;
      help_content += "\n";
    }
    help_text.setString(help_content);
  }
  // Set control buttons non-active (otherwise remains active)
  for (auto it : buttons)
  {
    if (it->getText().getString() == "Controls")
    {
      it->activate(false);
    }
  }

  help_active = true;

}

/*  Init MainMenu */
void MainMenu::init()
{
  ClearLevelSelectContainers();
  // Set Main menu buttons to non-actived
  for (auto &button : buttons) {
    button->activate(false);
  }
  level_select.curr_button = -1;
  current_button = -1;
  // Switch to the main menu screen
  screen_mode = MAINSCREEN;
  // Close possible help window
  CloseHelp();
}

/*  Finish creating the partially created (in UI) GameModeButtons */
void MainMenu::CreateGameModeButtons()
{
  // Set click functions to the Buttons
  level_select.single_player->setClickFunction(std::bind(&MainMenu::single_player_action, this));
  level_select.multiplayer->setClickFunction(std::bind(&MainMenu::multiplayer_action, this));

  // Set correct style for Buttons
  level_select.single_player->setCheckable(true);
  level_select.multiplayer->setCheckable(true);
  level_select.single_player->setChecked();
  level_select.single_player->setTextStyle(sf::Text::Bold, 14, sf::Color::Red);
  level_select.multiplayer->setTextStyle(sf::Text::Bold, 14, sf::Color::Red);
  level_select.single_player->enableClicking(false);
  level_select.single_player->setCheckedColor(sf::Color(15, 10, 75));
  level_select.multiplayer->setCheckedColor(sf::Color(15, 10, 75));

  // Add Buttons to the container
  level_select.buttons.push_back(level_select.single_player);
  level_select.buttons.push_back(level_select.multiplayer);


}

/*  Set game_mode to SinglePlayer and update the GameModeButtons */
void MainMenu::single_player_action()
{
  // allow user click only multiplayer
  level_select.single_player->enableClicking(false);
  level_select.multiplayer->enableClicking(true);
  // Set multiplayer unchecked
  level_select.multiplayer->setUnchecked();
  level_select.single_player->setChecked();
  // Set game_mode to SinglePlayer
  game_mode = Game::GameMode::SinglePlayer;
}

/*  Set game_mode to Multiplayer and update the GameModeButtons */
void MainMenu::multiplayer_action()
{
  // allow user click only single_player
  level_select.single_player->enableClicking(true);
  level_select.multiplayer->enableClicking(false);
  // Set single_player unchecked
  level_select.single_player->setUnchecked();
  level_select.multiplayer->setChecked();
  // Set game_mode to Multiplayer
  game_mode = Game::GameMode::Multiplayer;
}

/*  Change checked Buttons & GameMode */
void MainMenu::ChangeGameMode()
{
  if (level_select.single_player->getChecked())
  {
    multiplayer_action();
  } else {
    single_player_action();
  }
}
