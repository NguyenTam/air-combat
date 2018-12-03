/**
  *   @file UI.cpp
  *   @brief Source file for class UI
  */


#include "UI.hpp"



/*  Class UI  */


/*  Constructor */

UI::UI(sf::RenderWindow &render_window, sf::RenderWindow &dialog, sf::RenderWindow &help, sf::Color backgroundcolor):
window(render_window), dialog_window(dialog), help_window(help), BackgoundColor(backgroundcolor)
{
  // TODO error checking
  messagebox.message_font.loadFromFile(FONT_ARIAL);
}


/*  Return window_status  */

bool UI::getStatus ()
{
  return window_status;
}

/* Close active dialog */

void UI::CloseDialog()
{
  dialog_window.close();
  dialog_active = false;
  messagebox.active = false;
}

/* Close the main window */
void UI::CloseWindow()
{
  // Clear all select level containers
  level_select.buttons.clear();
  level_select.image_buttons.clear();
  level_select.level_names.clear();
  // close window and possible help window
  window.close();
  help_window.close();
  window_status = false;
  exit_status = ExitStatus::QUIT;
}



/*  Update UI based on sf::Events */

void UI::updateUI()
{
  sf::Event event;

  /* Poll window events ( if events aren't polled window will freeze, so events
    are also polled when dialog_window is active) */

  while( window.pollEvent(event) )
  {
    // Only update if there is no active dialog
    if (! dialog_active)
    {
      if (screen_mode == MAINSCREEN)
      {
        switch (event.type)
        {
          case sf::Event::Closed:
            CloseWindow();
            break;

          case sf::Event::KeyPressed:
            HandleKeyPress(event);
            break;

          case sf::Event::MouseMoved:
            HandleMouseMove(event);
            break;

          case sf::Event::MouseButtonPressed:
            HandleMousePress(event);
            break;

          case sf::Event::Resized:
            HandleResize(event);
            break;

          default:
            std::cout << "Other sf::Event" << std::endl;
        }
      }
      else if (screen_mode == LEVELSELECT)
      {
        UpdateLevelSelect(event);
      }
    }

  }
  if (! dialog_active)
  {
    // Clear and display window
    window.clear(sf::Color(BackgoundColor));
    if (screen_mode == MAINSCREEN)
    {
      DrawUI();
    }
    else if (screen_mode == LEVELSELECT)
    {
      DrawLevelSelect();
    }
    window.display();
  }

  // Handle also possible dialog_window event loop
  else if (dialog_active)
  {
    sf::Event event;
    while (dialog_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        CloseDialog();
      }
      else if (event.type == sf::Event::MouseButtonPressed)
      {
        HandleDialogMousePress(event);
      }
      else if (event.type == sf::Event::MouseMoved)
      {
        HandleDialogMouseMove(event);
      }
      else if (event.type == sf::Event::TextEntered)
      {
        HandleDialogTextEnter(event);
      }
      else if (event.type == sf::Event::KeyPressed)
      {
        HandleDialogKeyPress(event);
      }
    }
    dialog_window.clear(sf::Color::White);
    DrawDialog();
    dialog_window.display();
  }

  // Handle also possible help window
  if (help_active)
  {
    sf::Event event;
    while(help_window.pollEvent(event))
    {
      // Help window is kept as simple as possible (only close events are handled)
      if (event.type == sf::Event::Closed)
      {
        CloseHelp();
      }
    }
    help_window.clear(sf::Color::White);
    DrawHelp();
    help_window.display();
  }

}

/* Draw to dialog_window */

void UI::DrawDialog()
{
  if (messagebox.active)
  {
    // Draw messagebox
    dialog_window.draw(messagebox.message);
    dialog_window.draw(messagebox.button);
  }
}

/* Handle window resizing */

void UI::HandleResize(sf::Event event)
 {
   // Reset view
   sf::FloatRect new_screen = sf::FloatRect(0, 0, event.size.width, event.size.height);
   window.setView(sf::View(new_screen));

 }

/* Handle dialog_window mouse press */

 void UI::HandleDialogMousePress(sf::Event event)
 {
   if (event.mouseButton.button == sf::Mouse::Left)
   {
     float x = (float) event.mouseButton.x;
     float y = (float) event.mouseButton.y;

     if (messagebox.active)
     {
       // if messagebox button is clicked, it calls UI::CloseDialog
       messagebox.button.checkClicked(x, y);
     }
   }
 }

 /* Handle dialog_window mouse movement */

 void UI::HandleDialogMouseMove(sf::Event event)
 {
   float x = (float) event.mouseMove.x;
   float y = (float) event.mouseMove.y;

   if (messagebox.active)
   {
     // Check if mouse hovers on the messagebox
     messagebox.button.tryActivate(x, y);
   }
 }


/*  Create and start showing a messagebox */

 void UI::ShowMessageBox(std::string message, sf::Vector2i position)
 {
   float button_width = 40;
   float button_height = 30;
   messagebox.active = true;
   messagebox.message = sf::Text(message, messagebox.message_font, 14);
   messagebox.button = Button("Ok", sf::Color::White, button_width, button_height);

   messagebox.button.setTextColor(sf::Color::Black);
   messagebox.button.setOutline(1, sf::Color::Black);
   messagebox.button.setActiveColor(sf::Color(0, 0, 200, 50));

   sf::Text& button_text = messagebox.button.getText();
   button_text.setStyle(sf::Text::Regular);

   // Bind CloseDialog to Button click_action
   messagebox.button.setClickFunction( std::bind(&UI::CloseDialog, this) );

   // Get Text rect size
   float width = messagebox.message.getLocalBounds().width;
   float height = messagebox.message.getLocalBounds().height;
   unsigned x = (unsigned) width + button_width + 30; // Modify this if needed
   unsigned y = (unsigned) height + button_height + 50; // Modify this if needed

   // Create messagebox to the dialog_window
   dialog_window.create(sf::VideoMode(x, y), "Information", sf::Style::Close);
   dialog_window.setPosition(position);

   messagebox.message.setPosition(30, 20);
   messagebox.button.setPosition(x - (button_width + 30), y - (button_height + 10));

   messagebox.message.setColor(sf::Color::Black);

   // Change dialog_window status
   dialog_active = true;

 }

 /* Create screen for choosing level */
 void UI::CreateSelectLevel()
 {
   // Recreate the window
   //window.create(sf::VideoMode(800, 600), "Level select", sf::Style::Close);
   window.setTitle("Level Select");
   screen_mode = LEVELSELECT;

   // Create UI for LevelSelect
   std::shared_ptr<Button> cancel = std::make_shared<Button> ("Cancel", sf::Color::Blue, 100, 30);
   cancel->setPosition(150, 500);
   std::shared_ptr<Button> select = std::make_shared<Button> ("Select", sf::Color::Blue, 100, 30);
   select->setPosition(550, 500);
   select->setClickFunction(std::bind(&UI::level_selected_action, this));
   cancel->setClickFunction(std::bind(&UI::cancel_to_mainscreen_action, this));
   cancel->setActiveColor(sf::Color(15, 10, 75));
   select->setActiveColor(sf::Color(15, 10, 75));
   // Add to the container
   level_select.buttons.push_back(cancel);
   level_select.buttons.push_back(select);

   // Create ImageButtons to switch shown level
   std::shared_ptr<ImageButton> left = std::make_shared<ImageButton> ("", "../data/img/left_arrow.png", 100, 100);
   std::shared_ptr<ImageButton> right = std::make_shared<ImageButton> ("", "../data/img/right_arrow.png", 100, 100);
   right->setScale(0.2);
   left->setScale(0.2);
   right->setClickFunction(std::bind(&UI::LevelSelectNext, this));
   left->setClickFunction(std::bind(&UI::LevelSelectPrev, this));
   left->setPosition(470, 430);
   right->setPosition(510, 430);
   left->setCheckable(false);
   right->setCheckable(false);

   // Add to the container
   level_select.image_buttons.push_back(left);
   level_select.image_buttons.push_back(right);

   // Get all level name in the correct directory
   const std::string dir = "../data/level_files/";
   level_select.max_level = -1;
   try
   {
     for (auto &file : std::experimental::filesystem::directory_iterator(dir))
     {
       std::string level_name = file.path();
       level_name.erase(0, dir.length());
       level_select.level_names.push_back(level_name);
       level_select.max_level ++; // update to get how many levels there are
     }
   } catch (std::exception &e)
   {
     // Directory probably doesn't exist
     std::cout << e.what();
   }


   // Construct text and image of the first level
   level_select.font.loadFromFile(FONT_COURIER);
   level_select.level_name = sf::Text();
   level_select.description = sf::Text();
   level_select.level_name.setFont(level_select.font);
   level_select.level_name.setColor(sf::Color::Blue);
   level_select.level_name.setStyle(sf::Text::Bold);
   level_select.level_name.setCharacterSize(30);
   level_select.description.setFont(level_select.font);
   level_select.description.setColor(sf::Color::Blue);
   level_select.description.setCharacterSize(14);
   level_select.level_name.setPosition(300, 30);
   level_select.description.setPosition(50, 150);
   level_select.level_image.setPosition(300, 100);

   if (level_select.max_level == -1)
   {
     // No levels, also disable select button clicking
     level_select.level_name.setString("No levels found");
     select->enableClicking(false);
   }
   else
   {
     level_select.curr_level = 0;
     UpdateLevelShown();
   }
 }


void UI::DrawLevelSelect()
{
  for (auto it = level_select.buttons.begin(); it != level_select.buttons.end(); it++)
  {
    window.draw(**it);
  }
  for (auto it = level_select.image_buttons.begin(); it != level_select.image_buttons.end(); it++)
  {
    window.draw(**it);
  }
  // Draw texts and image
  window.draw(level_select.level_name);
  window.draw(level_select.description);
  window.draw(level_select.level_image);
}

/* Update Level select screen */
void UI::UpdateLevelSelect(sf::Event event)
{
  if (event.type == sf::Event::Closed)
  {
    // Stop program
    CloseWindow();
  }
  if (event.type == sf::Event::MouseButtonPressed)
  {
    // Try to press level_select Buttons
    bool clicked = false;

    for (auto it = level_select.buttons.begin(); it != level_select.buttons.end(); it++)
    {
      if ((*it)->checkClicked(event.mouseButton.x, event.mouseButton.y))
      {
        clicked = true;
        break;
      }
    }
    if (! clicked)
    {
      for (auto it = level_select.image_buttons.begin(); it != level_select.image_buttons.end(); it++)
      {
        if ((*it)->checkClicked(event.mouseButton.x, event.mouseButton.y))
        {
          break;
        }
      }
    }

  }
  else if (event.type == sf::Event::MouseMoved)
  {
    // Try to activate level_select Buttons
    bool activated = false;
    int i = 0;
    for (auto it = level_select.buttons.begin(); it != level_select.buttons.end(); it++)
    {
      if ((*it)->tryActivate(event.mouseMove.x, event.mouseMove.y))
      {
        activated = true;
        level_select.curr_button = i;
        break;
      }
      i++;
    }
    if (! activated)
    {
      level_select.curr_button = -1;
      for (auto it = level_select.image_buttons.begin(); it != level_select.image_buttons.end(); it++)
      {
        if ((*it)->tryActivate(event.mouseMove.x, event.mouseMove.y))
        {
          break;
        }
      }
    }
  }
  else if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Left)
    {
      LevelSelectPrev();
    }
    else if (event.key.code == sf::Keyboard::Right)
    {
      LevelSelectNext();
    }
    else if (event.key.code == sf::Keyboard::Tab)
    {
      if (level_select.curr_button == 0)
      {
        level_select.curr_button = 1;
        level_select.buttons[1]->activate(true);
        level_select.buttons[0]->activate(false);
      }
      else
      {
        level_select.curr_button = 0;
        level_select.buttons[0]->activate(true);
        level_select.buttons[1]->activate(false);
      }
    }
    else if (event.key.code == sf::Keyboard::Return)
    {
      if ((level_select.curr_button == 0) || (level_select.curr_button == 1))
      {
        // Check curr_button ok
        level_select.buttons[level_select.curr_button]->clickAction();
      }

    }
  }
}

void UI::level_selected_action()
{
  // Set window statusto false and exit status to STARTGAME
  level_selected = level_select.level_name.getString();
  exit_status = STARTGAME;
  window_status = false;
}

void UI::cancel_to_mainscreen_action()
{
  // Clear all select_level containers
  level_select.buttons.clear();
  level_select.image_buttons.clear();
  level_select.level_names.clear();

  // Switch to main screen (MainMenu / LevelEditor)
  screen_mode = MAINSCREEN;
  window.setTitle("Main Menu");

}

/*  Update to show correct level */
void UI::UpdateLevelShown()
{
  std::string level = level_select.level_names[level_select.curr_level];
  // Parse description
  level_select.description.setString(ParseDescription("../data/level_files/" + level));

  // remove .txt ending
  level.erase(level.length() - 4);
  level_select.level_name.setString(level);

  // Set correct image to the sprite
  if (level_select.level_texture.loadFromFile("../data/level_img/" + level + ".png"))
  {
    level_select.level_image.setTexture(level_select.level_texture);
  }
  else
  {
    // Loading failed, assign an empty image to correct position
    level_select.level_image = sf::Sprite();
    level_select.level_image.setPosition(300, 100);
  }


}

/*  Parse description out of level file */
std::string UI::ParseDescription(const std::string& filepath)
{
  // Description format: /* xxxxxx(can be multiple lines) */

  std::string description = "";
  std::ifstream file(filepath);
  if (file.is_open())
  {
    std::string line;
    while(getline(file, line))
    {
      description += line;
      std::size_t end_index = line.find("*/");
      if (end_index !=  std::string::npos)
      {
        // end found
        std::size_t start_index = description.find("/*");
        if (start_index != std::string::npos)
        {
          // Erase from begin to start index  + 3 and last three chars
          description.erase(0, start_index + 3);
          if (description.length() >= 3)
          {
            description.erase(description.length() - 3);
          }
          else
          {
            // Smt went wrong
            return "";
          }
        }
        else
        {
          // Smt went wrong
          return "";
        }

        break;
      }
      description += "\n"; // Add line feed as in the original description
    }
  }
  return description;
}

/*  Display new level */
void UI::LevelSelectNext()
{
  if (level_select.curr_level < level_select.max_level)
  {
    // Ok to show next level
    level_select.curr_level ++;
    // Display correct image and texts
    UpdateLevelShown();
  }
}

/*  Display prev level */
void UI::LevelSelectPrev()
{
  if (level_select.curr_level > 0)
  {
    // Ok to show prev level
    level_select.curr_level --;
    // Display correct image and texts
    UpdateLevelShown();
  }
}

/*  Get level path */
std::string UI::getLevel()
{
  return "../data/level_files/" + level_selected + ".txt";
}

/*  Close help window */
void UI::CloseHelp()
{
  help_window.close();
}

/*  Draw help window */
void UI::DrawHelp()
{
  // Draw help_text and title
  help_window.draw(help_text);
  help_window.draw(help_title);
}

/*  Get exit_status */
int UI::getExitStatus()
{
  return exit_status;
}

/*  Clear level select containers */
void UI::ClearLevelSelectContainers()
{
  // Check containers aren't empty
  if (! level_select.buttons.empty())
  {
    level_select.buttons.clear();
  }
  if (! level_select.image_buttons.empty())
  {
    level_select.image_buttons.clear();
  }
  if (! level_select.level_names.empty())
  {
    level_select.level_names.clear();
  }
}
