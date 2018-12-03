/**
  *   @file MainMenu.cpp
  *   @brief Source file for class MainMenu
  */


#include "MainMenu.hpp"


// Assign the class variable to match the amount of buttons
int MainMenu::MainMenuButtons = 4;



/*  Class MainMenu  */


/*  Constructor */

MainMenu::MainMenu(sf::RenderWindow &parent_window, sf::RenderWindow &dialog,
                  sf::RenderWindow &help):
UI(parent_window, dialog, help, sf::Color(150, 200, 255, 255))
{
  //createMainScreen();
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
}

/* Draw UI */

void MainMenu::DrawUI()
{
  for(auto button = buttons.begin(); button != buttons.end(); button++)
  {
    // Draw buttons
    window.draw(**button);
  }
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
   float x = (float) event.mouseMove.x;
   float y = (float) event.mouseMove.y;

   int i = 0;
   for (auto it = buttons.begin(); it != buttons.end(); it++)
   {
     if ( (*it)->tryActivate(x, y) )
     {
       // Correct current_button
       current_button = i;
       int j = 0;
       for (auto it = buttons.begin(); it != buttons.end(); it++)
       {
         // Deactivate other buttons
         if (j != i)
         {
           (*it)->activate(false);
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
     float x = (float) event.mouseButton.x;
     float y = (float) event.mouseButton.y;
     for (auto it = buttons.begin(); it != buttons.end(); it++)
     {
       // Check if clicked
       (*it)->checkClicked(x, y);

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
   }
   else current_button = 0;
   // Activate Button
   ActivateCurrentButton();

 }


/*  Create main menu */

void MainMenu::CreateMainMenu()
{
  // Create Buttons
  // First create the button with longest text and match other widths to it
  std::shared_ptr<Button> select_level = std::make_shared<Button>("Start Game", sf::Color::Blue);
  select_level->setPosition(100, 100);
  buttons.push_back(select_level);
  unsigned width = select_level->getWidth();
  unsigned height = select_level->getHeight();
  std::shared_ptr<Button> start_editor = std::make_shared<Button>("Editor",
                                    sf::Color::Blue, width, height);
  std::shared_ptr<Button> button3 = std::make_shared<Button>("Stats",
                                    sf::Color::Blue, width, height);
  std::shared_ptr<Button> quit = std::make_shared<Button>("Quit",
                                    sf::Color::Blue, width, height);
  start_editor->setPosition(100, 200);
  buttons.push_back(start_editor);
  button3->setPosition(100, 300);
  buttons.push_back(button3);
  quit->setPosition(100, 400);
  buttons.push_back(quit);

  // Set click_actions IMPORTANT
  select_level->setClickFunction(std::bind(&MainMenu::select_level_action, this));
  start_editor->setClickFunction(std::bind(&MainMenu::start_editor_action, this));
  button3->setClickFunction(std::bind(&MainMenu::Test3, this));
  quit->setClickFunction(std::bind(&MainMenu::CloseWindow, this));

  // Set active colors
  select_level->setActiveColor(sf::Color(15, 10, 75));
  start_editor->setActiveColor(sf::Color(15, 10, 75));
  button3->setActiveColor(sf::Color(15, 10, 75));
  quit->setActiveColor(sf::Color(15, 10, 75));


}


/* Activate current_button */

void MainMenu::ActivateCurrentButton()
{
  int i = 0;
  for (auto it = buttons.begin(); it != buttons.end(); it++)
  {
    if (i != current_button)
    {
      (*it)->activate(false);
    }
    else (*it)->activate(true);
    i++;
  }
}

/* Click current_button */

void MainMenu::ClickCurrentButton()
{
  int i = 0;
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

/*  Swicth to LevelEditor */
void MainMenu::start_editor_action()
{
  // Set correct exit status
  exit_status = ExitStatus::STARTEDITOR;
  // Clear all Buttons

  window_status = false;
}

/*  Init MainMenu */
void MainMenu::init()
{
  ClearLevelSelectContainers();
  // Set Main menu buttons to non-actived
  for (auto it = buttons.begin(); it != buttons.end(); it++)
  {
    (*it)->activate(false);
  }
  level_select.curr_button = -1;
  current_button = -1;
  // Switch to the main menu screen
  screen_mode = MAINSCREEN;
}
