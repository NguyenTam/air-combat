/**
  *   @file LevelEditor.cpp
  *   @brief Source file for LevelEditor class
  */

#include "LevelEditor.hpp"


/*  Class LevelEditor */


/*  Constructor for LevelEditor */

LevelEditor::LevelEditor(sf::RenderWindow &render_window, sf::RenderWindow &dialog,
                        sf::RenderWindow &help):
UI(render_window, dialog, help, sf::Color(150, 200, 255, 255))
{
  //createMainScreen();
  ui_view = window.getDefaultView();
  level.setYLimit(Game::HEIGHT); // This must be set
}

/*  Create LevelEditor UI */

void LevelEditor::createMainScreen()
{
  // Set window active
  window_status = true;

  // Recreate the window with correct size
  unsigned window_width = Game::WIDTH + vertical_toolbar_width;
  unsigned window_height = Game::HEIGHT + horizontal_toolbar_height;

  // Resize window and also adjust view
  window.setSize(sf::Vector2u(window_width, window_height));
  window.setTitle("Level Editor");
  ui_view.setSize(Game::WIDTH + vertical_toolbar_width,
                  Game::HEIGHT + horizontal_toolbar_height);
  ui_view.setCenter((Game::WIDTH + vertical_toolbar_width) / 2,
                 (Game::HEIGHT + horizontal_toolbar_height) / 2);

  CreateVerticalToolbar(window_height);
  CreateHorizontalToolbar(window_width);

  // Create another view for level (it's crusial to make divisions with floats)
  float level_width = (float)Game::WIDTH / (float) window_width;
  float level_height = (float) Game::HEIGHT / (float) window_height;
  float level_x = (float) vertical_toolbar_width / (float) window_width;
  float level_y = (float) horizontal_toolbar_height / (float) window_height;
  level_view.setViewport(sf::FloatRect(level_x, level_y, level_width, level_height));
  level_view.setSize(sf::Vector2f(Game::WIDTH, Game::HEIGHT));
  level_view.setCenter(sf::Vector2f(Game::WIDTH / 2, Game::HEIGHT / 2));

}


/*  Draw current LevelEditor window */

void LevelEditor::DrawUI()
{
  // Draw level first because otherwise wide entities could be drawn on top of
  // the toolbars
  window.setView(level_view);

  // Draw Level
  level.drawLevel(window);

  window.setView(ui_view);

  // Draw toolbars
  DrawVerticalToolbar();
  DrawHorizontalToolbar();
}

/* Handle key presses */

void LevelEditor::HandleKeyPress(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    // Close window
    CloseWindow();
  }
  /*else if (event.key.code == sf::Keyboard::Right)
  {
    view_right_action();
  }
  else if (event.key.code == sf::Keyboard::Left)
  {
    view_left_action();
  }*/
  else if (event.key.code == sf::Keyboard::BackSpace)
  {
    // Clear current_entity
    level.removeCurrent();
  }

}

void LevelEditor::HandleMouseMove(sf::Event event)
{
  float x = event.mouseMove.x;
  float y = event.mouseMove.y;

  if (x < vertical_toolbar_width || y < horizontal_toolbar_height)
  {
    // Mouse is inside the toolbars

    // Check if mouse hovers on ImageButton
    bool activated = false;

    if (horizontal_toolbar.mode == ESSENTIALS_MODE)
    {
      // Check only essentials container
      for (auto it = horizontal_toolbar.essentials.begin(); it != horizontal_toolbar.essentials.end(); it++)
      {
        if ((*it)->tryActivate(x, y))
        {
          // Skip unnecessary checks (mouse can only be at one position)
          activated = true;
          break;
        }
      }
    }
    else if (horizontal_toolbar.mode == OBJECTIVES_MODE)
    {
      // Check only objectives container
      for (auto it = horizontal_toolbar.objectives.begin(); it != horizontal_toolbar.objectives.end(); it++)
      {
        if ((*it)->tryActivate(x, y))
        {
          // Skip unnecessary checks (mouse can only be at one position)
          activated = true;
          break;
        }
      }
    }
    else if (horizontal_toolbar.mode == BARRIERS_MODE)
    {
      // Check only barriers container
      for (auto it = horizontal_toolbar.barriers.begin(); it != horizontal_toolbar.barriers.end(); it++)
      {
        if ((*it)->tryActivate(x, y))
        {
          // Skip unnecessary checks (mouse can only be at one position)
          activated = true;
          break;
        }
      }
      if (! activated)
      {
        // Check also ground related Buttons
        if ( horizontal_toolbar.place_ground->tryActivate(x, y))
        {
          activated = true;
        }
        else if (horizontal_toolbar.cancel_ground->tryActivate(x, y))
        {
          activated = true;
        }
      }
    }

    if (! activated)
    {
      for (auto it = vtoolbar_buttons.begin(); it != vtoolbar_buttons.end(); it++)
      {
        if ( (*it)->tryActivate(x, y))
        {
          activated = true;
          break;
        }

      }
    }

    if (! activated)
    {
      // Check if mouse is over horizontal_toolbar mode select buttons
      if (horizontal_toolbar.show_essentials->tryActivate(x, y))
      {
        activated = true;
      }
      else if (horizontal_toolbar.show_objectives->tryActivate(x, y))
      {
        activated = true;
      }
      else if (horizontal_toolbar.show_barriers->tryActivate(x, y))
      {
        activated = true;
      }
    }
  }
  else
  {
    // Mouse hovers on the Level

    // Move current LevelEntity, use Level coordinates
    float level_x = x - vertical_toolbar_width + view * (float) Game::WIDTH;
    float level_y = y - horizontal_toolbar_height;
    level.moveCurrentEntity(level_x, level_y);
  }

}


/*  Handle mouse movement */

void LevelEditor::HandleMousePress(sf::Event event)
{
  float x = event.mouseButton.x;
  float y = event.mouseButton.y;

  if (event.mouseButton.button == sf::Mouse::Left)
  {
    // Check if some button was clicked
    bool clicked = false;

    if (x < vertical_toolbar_width || y < horizontal_toolbar_height)
    {
      // Cursor inside toolbars

      if (horizontal_toolbar.mode == ESSENTIALS_MODE)
      {
        // Check only essential buttons

        for (auto it = horizontal_toolbar.essentials.begin(); it != horizontal_toolbar.essentials.end(); it++)
        {
          if ( (*it)->checkClicked(x, y) )
          {
            clicked = true;
            if ((*it)->getChecked())
            {
              // User checked the button
              // store pointer to the clicked button
              clicked_button = it->get();
            }
            else
            {
              // User unchecked the button, set current_entity_type to none
              current_entity_type = NO_ENTITY;
            }
            level.removeCurrent(); // This has to be always done
          }
        }
      }

      else if (horizontal_toolbar.mode == OBJECTIVES_MODE)
      {
        // Check only objectives container

        for (auto it = horizontal_toolbar.objectives.begin(); it != horizontal_toolbar.objectives.end(); it++)
        {
          if ( (*it)->checkClicked(x, y) )
          {
            clicked = true;
            if ((*it)->getChecked())
            {
              // User checked the button
              // store pointer to the clicked button
              clicked_button = it->get();
            }
            else
            {
              // User unchecked the button, set current_entity_type to none
              current_entity_type = NO_ENTITY;
            }
            level.removeCurrent(); // This has to be always done
          }
        }
      }

      else if (horizontal_toolbar.mode == BARRIERS_MODE)
      {

        // Check only barries container
        for (auto it = horizontal_toolbar.barriers.begin(); it != horizontal_toolbar.barriers.end(); it++)
        {
          if ( (*it)->checkClicked(x, y) )
          {
            clicked = true;
            if ((*it)->getChecked())
            {
              // User checked the button
              // store pointer to the clicked button
              clicked_button = it->get();
            }
            else
            {
              // User unchecked the button, set current_entity_type to none
              current_entity_type = NO_ENTITY;
            }
            level.removeCurrent(); // This has to be always done
          }
        }
        if (! clicked )
        {
          // Check also ground related Buttons
          horizontal_toolbar.place_ground->checkClicked(x, y);
          horizontal_toolbar.cancel_ground->checkClicked(x, y);
        }
      }


      if (clicked)
      {
        // Set other buttons not clicked (checked)
        // This line is also reached when checked button was unchecked and
        // it is a bit excessive looping
        UncheckImageButtons(clicked_button);
      }

      else
      {

        // Go through vertical_toolbar buttons
        for (auto it = vtoolbar_buttons.begin(); it != vtoolbar_buttons.end(); it++)
        {
          if( (*it)->checkClicked(x, y) )
          {
            clicked = true;
          }
        }

        if (! clicked)
        {
          // Check if horizontal_toolbar mode select buttons have been clicked
          if (horizontal_toolbar.show_essentials->checkClicked(x, y))
          {
            clicked = true;
            // Multiple buttons can't be checked at the same time
            horizontal_toolbar.show_objectives->setUnchecked();
            horizontal_toolbar.show_barriers->setUnchecked();
          }
          else if (horizontal_toolbar.show_objectives->checkClicked(x, y))
          {
            clicked = true;
            horizontal_toolbar.show_essentials->setUnchecked();
            horizontal_toolbar.show_barriers->setUnchecked();
          }
          else if (horizontal_toolbar.show_barriers->checkClicked(x, y))
          {
            clicked = true;
            horizontal_toolbar.show_essentials->setUnchecked();
            horizontal_toolbar.show_objectives->setUnchecked();
          }
        }
      }
    }

    else
    {
      // Cursor inside Level

      // Place or create new LevelEntity
      // Notice that coordinate system origin differs in Level realative to LevelEditor
      float level_x = x - vertical_toolbar_width + view * (float) Game::WIDTH;
      float level_y = y - horizontal_toolbar_height;

      level.addEntity(level_x, level_y, current_entity_type);
    }
  }

  else
  {
    // Right mouse pressed
    if (x >= vertical_toolbar_width || y >= horizontal_toolbar_height)
    {
      // Try to flip LevelEntity
      // Notice that coordinate system origin differs in Level realative to LevelEditor
      float level_x = x - vertical_toolbar_width + view * (float) Game::WIDTH;
      float level_y = y - horizontal_toolbar_height;

      level.flipEntity(level_x, level_y);
    }
  }

}


/*  Uncheck ImageButtons */

void LevelEditor::UncheckImageButtons(ImageButton *button)
{
  if (horizontal_toolbar.mode == ESSENTIALS_MODE)
  {
    // Go through only essentials container
    for (auto it = horizontal_toolbar.essentials.begin(); it != horizontal_toolbar.essentials.end(); it++)
    {
      if (it->get() != button)
      {
        (*it)->setUnchecked();
      }
    }
  }

  else if (horizontal_toolbar.mode == OBJECTIVES_MODE)
  {
    // Go through only objectives container
    for (auto it = horizontal_toolbar.objectives.begin(); it != horizontal_toolbar.objectives.end(); it++)
    {
      if (it->get() != button)
      {
        (*it)->setUnchecked();
      }
    }
  }

  else if (horizontal_toolbar.mode == BARRIERS_MODE)
  {
    // Go through only barriers container
    for (auto it = horizontal_toolbar.barriers.begin(); it != horizontal_toolbar.barriers.end(); it++)
    {
      if (it->get() != button)
      {
        (*it)->setUnchecked();
      }
    }
  }

}


void LevelEditor::CreateVerticalToolbar(unsigned window_height)
{
  // Create rect matching vertical toolbar
  vertical_toolbar.rect = sf::RectangleShape(sf::Vector2f(vertical_toolbar_width, window_height));
  vertical_toolbar.rect.setFillColor(sf::Color(230, 230, 230, 150));
  vertical_toolbar.rect.setOutlineColor(sf::Color(50, 50, 50));
  vertical_toolbar.rect.setOutlineThickness(1);
  vertical_toolbar.rect.setPosition(0, 0);

  // Create all basic buttons
  vertical_toolbar.save_button = std::make_shared<Button>("Save", sf::Color(50, 50, 50, 100));
  float width = vertical_toolbar.save_button->getWidth();
  float height = vertical_toolbar.save_button->getHeight();
  vertical_toolbar.open_button = std::make_shared<Button>("Open", sf::Color(50, 50, 50, 100), width, height);
  vertical_toolbar.help_button = std::make_shared<Button>("Help", sf::Color(50, 50, 50, 100), width, height);
  vertical_toolbar.quit_button = std::make_shared<Button>("Menu", sf::Color(50, 50, 50, 100), width, height);

  // Set text colors
  vertical_toolbar.save_button->setTextColor(sf::Color::White);
  vertical_toolbar.open_button->setTextColor(sf::Color::White);
  vertical_toolbar.help_button->setTextColor(sf::Color::White);
  vertical_toolbar.quit_button->setTextColor(sf::Color::White);
  // Set active colors
  vertical_toolbar.save_button->setActiveColor(sf::Color(50, 50, 50, 255));
  vertical_toolbar.open_button->setActiveColor(sf::Color(50, 50, 50, 255));
  vertical_toolbar.help_button->setActiveColor(sf::Color(50, 50, 50, 255));
  vertical_toolbar.quit_button->setActiveColor(sf::Color(50, 50, 50, 255));

  // Set actions
  vertical_toolbar.save_button->setClickFunction( std::bind(&LevelEditor::save_button_action, this));
  vertical_toolbar.open_button->setClickFunction( std::bind(&LevelEditor::open_button_action, this));
  vertical_toolbar.help_button->setClickFunction( std::bind(&LevelEditor::help_button_action, this));
  vertical_toolbar.quit_button->setClickFunction( std::bind(&LevelEditor::quit_button_action, this));

  // Set positions
  vertical_toolbar.save_button->setPosition(5, 110);
  vertical_toolbar.open_button->setPosition(5, 10);
  vertical_toolbar.quit_button->setPosition(5, 210);
  vertical_toolbar.help_button->setPosition(5, window_height - 200 );

  // Add to the container
  vtoolbar_buttons.push_back(vertical_toolbar.save_button);
  vtoolbar_buttons.push_back(vertical_toolbar.open_button);
  vtoolbar_buttons.push_back(vertical_toolbar.help_button);
  vtoolbar_buttons.push_back(vertical_toolbar.quit_button);

  // Create view related buttons
  vertical_toolbar.view_right = std::make_shared<ImageButton>("", "../data/img/right_arrow.png",
                                100, 100);
  vertical_toolbar.view_right->setScale(0.2);
  float right_arrow_x = 5 + width / 2;
  vertical_toolbar.view_right->setPosition(right_arrow_x, window_height - 80);
  vertical_toolbar.view_left = std::make_shared<ImageButton>("", "../data/img/left_arrow.png",
                                100, 100);
  vertical_toolbar.view_left->setScale(0.2);
  vertical_toolbar.view_left->setPosition(right_arrow_x - 30, window_height - 80);

  // Disable outline
  vertical_toolbar.view_left->enableOutline(false);
  vertical_toolbar.view_right->enableOutline(false);

  // Set click actions
  vertical_toolbar.view_left->setClickFunction( std::bind(&LevelEditor::view_left_action, this));
  vertical_toolbar.view_right->setClickFunction( std::bind(&LevelEditor::view_right_action, this));

  // Add to the container
  vtoolbar_buttons.push_back(vertical_toolbar.view_right);
  vtoolbar_buttons.push_back(vertical_toolbar.view_left);

  // disable view_left (start view is the left most view)
  vertical_toolbar.view_left->setEnabled(false);
  vertical_toolbar.view_right->setEnabled(false);

  // Set buttons uncheckable
  vertical_toolbar.view_left->setCheckable(false);
  vertical_toolbar.view_right->setCheckable(false);

}



void LevelEditor::save_button_action()
{
  SaveLevel();
}

void LevelEditor::open_button_action()
{
  // Set correct window

  window.setSize(sf::Vector2u(Game::WIDTH, Game::HEIGHT));
  // Reset view and update set it to window
  ui_view.reset(sf::FloatRect(0, 0, Game::WIDTH, Game::HEIGHT));
  window.setView(ui_view);
  CreateSelectLevel();
}

void LevelEditor::help_button_action()
{
  // Create and activate help window
  help_window.create(sf::VideoMode(400, 600), "Help", sf::Style::Close);
  help_font.loadFromFile(FONT_ARIAL);
  help_title = sf::Text("Help" , help_font, 30);
  help_title.setStyle(sf::Text::Bold | sf::Text::Underlined);
  help_title.setPosition(100, 20);
  help_title.setColor(sf::Color::Blue);

  help_text = sf::Text("Sorry, Help unavailable", help_font, 12);
  help_text.setPosition(50, 70);
  help_text.setColor(sf::Color::Black);

  // Load text from file
  std::string help_content;
  std::ifstream file("../data/misc/help.txt");
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
  // Set help button not active (otherwise is active until mouse is moved)
  vertical_toolbar.help_button->activate(false);
  help_active = true;
}

void LevelEditor::quit_button_action()
{
  // First clear all entities from level
  level.clearAll();

  // Return to main menu
  exit_status = ExitStatus::MAINMENU;
  help_window.close();
  window_status = false;
}


void LevelEditor::DrawVerticalToolbar()
{
  // Draw rect
  window.draw(vertical_toolbar.rect);

  // Draw Buttons
  for (auto it = vtoolbar_buttons.begin(); it != vtoolbar_buttons.end(); it++)
  {
    window.draw(**it);
  }
}


void LevelEditor::CreateHorizontalToolbar(unsigned window_width)
{
  // Create the rect and lines
  horizontal_toolbar.rect = sf::RectangleShape(sf::Vector2f(Game::WIDTH, horizontal_toolbar_height));
  horizontal_toolbar.rect.setFillColor(sf::Color(230, 230, 230, 150));

  horizontal_toolbar.line[0] = sf::Vertex(sf::Vector2f(vertical_toolbar_width, horizontal_toolbar_height),
                      sf::Color(50, 50, 50));
  horizontal_toolbar.line[1] = sf::Vertex(sf::Vector2f(window_width, horizontal_toolbar_height),
                      sf::Color(50, 50, 50));

  horizontal_toolbar.rect.setPosition(vertical_toolbar_width, 0);

  horizontal_toolbar.separator_line[0] = sf::Vertex(sf::Vector2f(window_width - 200, 0),
                                          sf::Color(50, 50, 50));
  horizontal_toolbar.separator_line[1] = sf::Vertex(sf::Vector2f(window_width - 200, horizontal_toolbar_height),
                                          sf::Color(50, 50, 50));


  // Create all ESSENTIALS_MODE ImageButtons

  std::shared_ptr<ImageButton> erase_entity = std::make_shared<ImageButton>
                                          ("Erase", "../data/img/erase.png", 40, 40);
  std::shared_ptr<ImageButton> add_friendly_infantry = std::make_shared<ImageButton>
                                        ("Friendly infantry", "../data/img/BlueInfantry.png", 40, 40);
  std::shared_ptr<ImageButton> add_hostile_infantry = std::make_shared<ImageButton>
                                        ("Hostile infantry", "../data/img/RedInfantry.png", 40, 40);
  std::shared_ptr<ImageButton> add_friendly_plane = std::make_shared<ImageButton>
                                        ("Friendly plane", "../data/img/BlueAirplane.png", 40, 40);
  std::shared_ptr<ImageButton> add_hostile_plane = std::make_shared<ImageButton>
                                        ("Hostile plane", "../data/img/RedAirplane.png", 40, 40);
  std::shared_ptr<ImageButton> add_friendly_AA = std::make_shared<ImageButton>
                                        ("Friendly AA", "../data/img/BlueAntiAircraft.png", 40, 40);
  std::shared_ptr<ImageButton> add_hostile_AA = std::make_shared<ImageButton>
                                        ("Hostile AA", "../data/img/RedAntiAircraft.png", 40, 40);
  std::shared_ptr<ImageButton> add_friendly_hangar = std::make_shared<ImageButton>
                                        ("Friendly hangar", "../data/img/BlueHangar.png", 40, 40);
  std::shared_ptr<ImageButton> add_hostile_hangar = std::make_shared<ImageButton>
                                        ("Hostile hangar", "../data/img/RedHangar.png", 40, 40);

  // Set positions
  erase_entity->setPosition(150, 5);
  erase_entity->setHighlightColor(sf::Color(50, 50, 50, 160));
  add_friendly_infantry->setPosition(250, 5);
  add_hostile_infantry->setPosition(300, 5);
  add_friendly_plane->setPosition(360, 5);
  add_hostile_plane->setPosition(410, 5);
  add_friendly_AA->setPosition(470, 5);
  add_hostile_AA->setPosition(520, 5);
  add_friendly_hangar->setPosition(580, 5);
  add_hostile_hangar->setPosition(630, 5);

  // Set click_actions
  erase_entity->setClickFunction( std::bind(&LevelEditor::erase_entity_action, this) );
  add_friendly_infantry->setClickFunction( std::bind(&LevelEditor::add_friendly_infantry_action, this) );
  add_hostile_infantry->setClickFunction( std::bind(&LevelEditor::add_hostile_infantry_action, this) );
  add_friendly_plane->setClickFunction( std::bind(&LevelEditor::add_friendly_plane_action, this) );
  add_hostile_plane->setClickFunction( std::bind(&LevelEditor::add_hostile_plane_action, this) );
  add_friendly_AA->setClickFunction( std::bind(&LevelEditor::add_friendly_AA_action, this) );
  add_hostile_AA->setClickFunction( std::bind(&LevelEditor::add_hostile_AA_action, this) );
  add_friendly_hangar->setClickFunction( std::bind(&LevelEditor::add_friendly_hangar_action, this) );
  add_hostile_hangar->setClickFunction( std::bind(&LevelEditor::add_hostile_hangar_action, this) );

  // Add all buttons to the container
  horizontal_toolbar.essentials.push_back(erase_entity);
  horizontal_toolbar.essentials.push_back(add_friendly_infantry);
  horizontal_toolbar.essentials.push_back(add_hostile_infantry);
  horizontal_toolbar.essentials.push_back(add_hostile_plane);
  horizontal_toolbar.essentials.push_back(add_friendly_plane);
  horizontal_toolbar.essentials.push_back(add_friendly_AA);
  horizontal_toolbar.essentials.push_back(add_hostile_AA);
  horizontal_toolbar.essentials.push_back(add_friendly_hangar);
  horizontal_toolbar.essentials.push_back(add_hostile_hangar);

  // Create all OBJECTIVES_MODE ImageButtons
  std::shared_ptr<ImageButton> add_friendly_base = std::make_shared<ImageButton>
                              ("Friendly base", "../data/img/BlueBase.png", 40, 40);
  std::shared_ptr<ImageButton> add_hostile_base = std::make_shared<ImageButton>
                              ("Hostile base", "../data/img/RedBase.png", 40, 40);

  // Set positions and add click functions
  add_friendly_base->setPosition(250, 5);
  add_hostile_base->setPosition(300, 5);
  add_friendly_base->setClickFunction(std::bind(&LevelEditor::add_friendly_base_action, this));
  add_hostile_base->setClickFunction(std::bind(&LevelEditor::add_hostile_base_action, this));

  // Add to objectives container, add erase_entity also to objectives
  horizontal_toolbar.objectives.push_back(erase_entity);
  horizontal_toolbar.objectives.push_back(add_friendly_base);
  horizontal_toolbar.objectives.push_back(add_hostile_base);

  // Create all BARRIERS_MODE ImageButtons
  horizontal_toolbar.add_ground = std::make_shared<ImageButton>
                              ("Ground", "../data/img/Ground.png", 40, 40);
  std::shared_ptr<ImageButton> add_tree = std::make_shared<ImageButton>
                              ("Tree", "../data/img/Tree.png", 40, 40);
  std::shared_ptr<ImageButton> add_rock = std::make_shared<ImageButton>
                              ("Rock", "../data/img/Rock.png", 40, 40);
  // Set positions and click functions
  horizontal_toolbar.add_ground->setPosition(250, 5);
  add_tree->setPosition(300, 5);
  add_rock->setPosition(350, 5);
  horizontal_toolbar.add_ground->setClickFunction( std::bind(&LevelEditor::add_ground_action, this));
  add_tree->setClickFunction(std::bind(&LevelEditor::add_tree_action, this));
  add_rock->setClickFunction(std::bind(&LevelEditor::add_rock_action, this));

  // Add to barriers container, add erase_entity also to barriers
  horizontal_toolbar.barriers.push_back(erase_entity);
  horizontal_toolbar.barriers.push_back(horizontal_toolbar.add_ground);
  horizontal_toolbar.barriers.push_back(add_tree);
  horizontal_toolbar.barriers.push_back(add_rock);

  // Create Buttons related to add_ground
  horizontal_toolbar.place_ground = std::make_shared<Button>("Place", sf::Color(50, 50, 50, 100),
                                  60, 20);
  horizontal_toolbar.cancel_ground = std::make_shared<Button>("Cancel", sf::Color(50, 50, 50, 100),
                                  60, 20);
  horizontal_toolbar.place_ground->setTextStyle(sf::Text::Regular, 14, sf::Color::Blue);
  horizontal_toolbar.cancel_ground->setTextStyle(sf::Text::Regular, 14, sf::Color::Blue);
  horizontal_toolbar.place_ground->setActiveColor(sf::Color(50, 50, 50, 170));
  horizontal_toolbar.cancel_ground->setActiveColor(sf::Color(50, 50, 50, 170));
  horizontal_toolbar.place_ground->setPosition(200, 60);
  horizontal_toolbar.cancel_ground->setPosition(280, 60);
  horizontal_toolbar.place_ground->setEnabled(false);
  horizontal_toolbar.cancel_ground->setEnabled(false);
  horizontal_toolbar.place_ground->setClickFunction(std::bind(&LevelEditor::place_ground_action, this));
  horizontal_toolbar.cancel_ground->setClickFunction(std::bind(&LevelEditor::cancel_ground_action, this));

  // Create Buttons to change mode
  horizontal_toolbar.show_essentials = std::make_shared<Button>("Essentials",
                                  sf::Color::Transparent, 140, 20);
  horizontal_toolbar.show_objectives = std::make_shared<Button>("Objectives",
                                  sf::Color::Transparent, 140, 20);
  horizontal_toolbar.show_barriers = std::make_shared<Button>("Barriers",
                                  sf::Color::Transparent, 140, 20);

  //Tune text size and style
  horizontal_toolbar.show_essentials->setTextStyle(sf::Text::Regular, 12, sf::Color::Black);
  horizontal_toolbar.show_objectives->setTextStyle(sf::Text::Regular, 12, sf::Color::Black);
  horizontal_toolbar.show_barriers->setTextStyle(sf::Text::Regular, 12, sf::Color::Black);

  // Set active_color
  horizontal_toolbar.show_essentials->setActiveColor(sf::Color(50, 50, 50, 200));
  horizontal_toolbar.show_objectives->setActiveColor(sf::Color(50, 50, 50, 200));
  horizontal_toolbar.show_barriers->setActiveColor(sf::Color(50, 50, 50, 200));

  // Set positions
  horizontal_toolbar.show_essentials->setPosition(window_width - 170, 5);
  horizontal_toolbar.show_objectives->setPosition(window_width - 170, 35);
  horizontal_toolbar.show_barriers->setPosition(window_width - 170, 65);

  // Set click_actions
  horizontal_toolbar.show_essentials->setClickFunction( std::bind(&LevelEditor::show_essentials_action, this));
  horizontal_toolbar.show_objectives->setClickFunction( std::bind(&LevelEditor::show_objectives_action, this));
  horizontal_toolbar.show_barriers->setClickFunction( std::bind(&LevelEditor::show_barriers_action, this));

  // Set checkable
  horizontal_toolbar.show_essentials->setCheckable(true);
  horizontal_toolbar.show_objectives->setCheckable(true);
  horizontal_toolbar.show_barriers->setCheckable(true);
  // Set show_essentials checked to match the initial window UI
  horizontal_toolbar.show_essentials->setChecked();

  // Create info text
  horizontal_toolbar.info_text.setPosition(380, 60);
  horizontal_toolbar.info_font.loadFromFile(FONT_ARIAL);
  horizontal_toolbar.info_text.setFont(horizontal_toolbar.info_font);
  horizontal_toolbar.info_text.setCharacterSize(14);
  horizontal_toolbar.info_text.setColor(sf::Color(50, 50, 50, 180));
}

void LevelEditor::DrawHorizontalToolbar()
{
  // Draw the rect and lines
  window.draw(horizontal_toolbar.rect);
  window.draw(horizontal_toolbar.line, 2, sf::Lines);
  window.draw(horizontal_toolbar.separator_line, 2, sf::Lines);

  // Draw mode select related buttons
  window.draw( *horizontal_toolbar.show_essentials);
  window.draw( *horizontal_toolbar.show_objectives);
  window.draw( *horizontal_toolbar.show_barriers);

  // Draw info text if counter below 50000
  if (horizontal_toolbar.info_counter < 5000)
  {
    horizontal_toolbar.info_counter ++;
    window.draw(horizontal_toolbar.info_text);
    // Info counter is reseted when text needs to be shown
  }

  // Draw correct ImageButtons

  if (horizontal_toolbar.mode == ESSENTIALS_MODE)
  {
    // Draw essentials container buttons
    for (auto it = horizontal_toolbar.essentials.begin(); it != horizontal_toolbar.essentials.end(); it++)
    {
      window.draw(** it);
    }
  }
  else if (horizontal_toolbar.mode == OBJECTIVES_MODE)
  {
    // Draw buttons in objectives container
    for (auto it = horizontal_toolbar.objectives.begin(); it != horizontal_toolbar.objectives.end(); it++)
    {
      window.draw(** it);
    }
  }
  else if (horizontal_toolbar.mode == BARRIERS_MODE)
  {
    // Draw buttons in barriers container
    for (auto it = horizontal_toolbar.barriers.begin(); it != horizontal_toolbar.barriers.end(); it++)
    {
      window.draw(** it);
    }
    // Draw ground realated Buttons
    window.draw(* horizontal_toolbar.place_ground);
    window.draw(* horizontal_toolbar.cancel_ground);
  }
}


/*  Simple Toolbar ImageButton actions to change entity_type */
void LevelEditor::add_friendly_infantry_action()
{
  current_entity_type = FRIENDLY_INFANTRY;
}

void LevelEditor::add_hostile_infantry_action()
{
  current_entity_type = HOSTILE_INFANTRY;
}

void LevelEditor::add_friendly_plane_action()
{
  current_entity_type = FRIENDLY_PLANE;
}

void LevelEditor::add_hostile_plane_action()
{
  current_entity_type = HOSTILE_PLANE;
}

void LevelEditor::add_friendly_AA_action()
{
  current_entity_type = FRIENDLY_AA;
}

void LevelEditor::add_hostile_AA_action()
{
  current_entity_type = HOSTILE_AA;
}

void LevelEditor::add_friendly_hangar_action()
{
  current_entity_type = FRIENDLY_HANGAR;
}

void LevelEditor::add_hostile_hangar_action()
{
  current_entity_type = HOSTILE_HANGAR;
}

void LevelEditor::add_friendly_base_action()
{
  current_entity_type = FRIENDLY_BASE;
}

void LevelEditor::add_hostile_base_action()
{
  current_entity_type = HOSTILE_BASE;
}

void LevelEditor::add_tree_action()
{
  current_entity_type = TREE_ENTITY;
}

void LevelEditor::add_rock_action()
{
  current_entity_type = ROCK_ENTITY;
}

void LevelEditor::erase_entity_action()
{
  current_entity_type = ERASE_ENTITY;
  level.removeCurrent();
}

void LevelEditor::add_ground_action()
{
  // Disable clicking from all visible toolbar buttons except place_ground and
  // cancel_ground
  for (auto it = horizontal_toolbar.barriers.begin(); it != horizontal_toolbar.barriers.end(); it++)
  {
    (*it)->enableClicking(false);
  }
  horizontal_toolbar.show_essentials->enableClicking(false);
  horizontal_toolbar.show_objectives->enableClicking(false);
  // Enable clicking of the correct Buttons
  horizontal_toolbar.place_ground->enableClicking(true);
  horizontal_toolbar.place_ground->setEnabled(true);
  horizontal_toolbar.cancel_ground->enableClicking(true);
  horizontal_toolbar.cancel_ground->setEnabled(true);
  // Set correct LevelEntity type
  level.removeCurrent();
  current_entity_type = GROUND_ENTITY;
}

void LevelEditor::place_ground_action()
{
  if (level.finishAddingGround())
  {
    // Show info_text
    horizontal_toolbar.info_text.setString("Ground placed");
    horizontal_toolbar.info_counter = 0;
  }
}

void LevelEditor::cancel_ground_action()
{
  // Enable clicking for all buttons which clikcing was disabled
  for (auto it = horizontal_toolbar.barriers.begin(); it != horizontal_toolbar.barriers.end(); it++)
  {
    (*it)->enableClicking(true);
  }
  horizontal_toolbar.show_essentials->enableClicking(true);
  horizontal_toolbar.show_objectives->enableClicking(true);
  horizontal_toolbar.cancel_ground->setEnabled(false);
  horizontal_toolbar.place_ground->setEnabled(false);

  // Set add_ground unchecked
  horizontal_toolbar.add_ground->setUnchecked();
  // Clear current_entity and current_entity_type
  level.removeCurrent();
  current_entity_type = NO_ENTITY;
}


/*  Switch to ESSENTIALS_MODE, clear current_entity */
void LevelEditor::show_essentials_action()
{
  horizontal_toolbar.mode = ESSENTIALS_MODE;
  current_entity_type = NO_ENTITY;
  level.removeCurrent();
  // Set all objectives and barriers buttons unchecked
  for (auto it = horizontal_toolbar.objectives.begin(); it != horizontal_toolbar.objectives.end(); it++)
  {
    (*it)->setUnchecked();
  }
  for (auto it = horizontal_toolbar.barriers.begin(); it != horizontal_toolbar.barriers.end(); it++)
  {
    (*it)->setUnchecked();
  }
}

/*  Switch to OBJECTIVES_MODE, clear current_entity */
void LevelEditor::show_objectives_action()
{
  horizontal_toolbar.mode = OBJECTIVES_MODE;
  current_entity_type = NO_ENTITY;
  level.removeCurrent();
  // Set all essentials and barriers buttons unchecked
  for (auto it = horizontal_toolbar.essentials.begin(); it != horizontal_toolbar.essentials.end(); it++)
  {
    (*it)->setUnchecked();
  }
  for (auto it = horizontal_toolbar.barriers.begin(); it != horizontal_toolbar.barriers.end(); it++)
  {
    (*it)->setUnchecked();
  }

}

/* Switch to BARRIERS_MODE, clear current_entity */
void LevelEditor::show_barriers_action()
{
  horizontal_toolbar.mode = BARRIERS_MODE;
  current_entity_type = NO_ENTITY;
  level.removeCurrent();
  // Set all essentials and objectives buttons unchecked
  for (auto it = horizontal_toolbar.essentials.begin(); it != horizontal_toolbar.essentials.end(); it++)
  {
    (*it)->setUnchecked();
  }
  for (auto it = horizontal_toolbar.objectives.begin(); it != horizontal_toolbar.objectives.end(); it++)
  {
    (*it)->setUnchecked();
  }
}

/* Move view one Window_Width left */
void LevelEditor::view_left_action()
{
  if (view > 0)
  {
    view --;
    level_view.setCenter(sf::Vector2f((float) Game::WIDTH * (0.5 + view), (float) Game::HEIGHT / 2));
    if (view == 0.f)
    {
      // Disable left_arrow (inpossible to move left)
      vertical_toolbar.view_left->setEnabled(false);
    }
  }
}

/* Move view one Window_Width right */
void LevelEditor::view_right_action()
{
  // Enable left_arrow
  vertical_toolbar.view_left->setEnabled(true);
  view ++;
  level_view.setCenter(sf::Vector2f((float) Game::WIDTH * (0.5 + view), (float) Game::HEIGHT / 2));
}


/*  Save Level, create dialog window */
void LevelEditor::SaveLevel()
{
  dialog_window.create(sf::VideoMode(500, 400), "Save level", sf::Style::Close);

  saveUI.font.loadFromFile(FONT_ARIAL);
  saveUI.name = sf::Text("Level Name:", saveUI.font, 24);
  saveUI.name.setColor(sf::Color::Blue);
  saveUI.name.setStyle(sf::Text::Bold);
  saveUI.name.setPosition(50, 50);
  saveUI.fail_text = sf::Text("Level saving failed: incorrect level name", saveUI.font, 16);
  saveUI.fail_text.setColor(sf::Color::Red);
  saveUI.fail_text.setPosition(50, 20);

  saveUI.name_input = TextInput(250, 60, 150, 20);
  saveUI.name_input.setOutline(sf::Color::Black, 1);
  saveUI.name_input.enableStrictSanitization(true);

  saveUI.description = sf::Text("Description:", saveUI.font, 24);
  saveUI.description.setColor(sf::Color::Blue);
  saveUI.description.setStyle(sf::Text::Bold);
  saveUI.description.setPosition(50, 160);

  saveUI.description_input = TextInput(50, 200, 200, 100);
  saveUI.description_input.setOutline(sf::Color::Black, 1);

  // Construct Buttons
  saveUI.cancel = std::make_shared<Button>("Cancel", sf::Color(50, 50, 50, 100),
                  150, 60);
  saveUI.save = std::make_shared<Button>("Save", sf::Color(50, 50, 50, 100),
                  150, 60);
  saveUI.cancel->setPosition(50, 320);
  saveUI.save->setPosition(300, 320);
  saveUI.save->setActiveColor(sf::Color(50, 50, 50, 180));
  saveUI.cancel->setActiveColor(sf::Color(50, 50, 50, 180));
  saveUI.save->setClickFunction(std::bind(&LevelEditor::writeLevel, this));
  saveUI.cancel->setClickFunction(std::bind(&LevelEditor::cancelSaving, this));
  saveUI.save->setTextColor(sf::Color::Blue);
  saveUI.cancel->setTextColor(sf::Color::Blue);
  saveUI.buttons.push_back(saveUI.cancel);
  saveUI.buttons.push_back(saveUI.save);

  // Construct also use existing Buttons
  saveUI.use_old_name = std::make_shared<Button>("Existing name", sf::Color(50, 50, 50, 100),
                        200, 20);
  saveUI.use_old_description = std::make_shared<Button>("Existing description", sf::Color(50, 50, 50, 100),
                        200, 20);
  saveUI.use_old_name->setTextStyle(sf::Text::Regular, 14, sf::Color::Blue);
  saveUI.use_old_description->setTextStyle(sf::Text::Regular, 14, sf::Color::Blue);

  saveUI.use_old_name->setPosition(50, 90);
  saveUI.use_old_description->setPosition(50, 130);
  saveUI.use_old_name->setActiveColor(sf::Color(50, 50, 50, 180));
  saveUI.use_old_description->setActiveColor(sf::Color(50, 50, 50, 180));
  saveUI.use_old_name->setClickFunction(std::bind(&LevelEditor::use_old_name_action, this));
  saveUI.use_old_description->setClickFunction(std::bind(&LevelEditor::use_old_description_action, this));

  // Deactivate by default if no level opened
  if (! saveUI.opened_level)
  {
    saveUI.use_old_name->setEnabled(false);
    saveUI.use_old_description->setEnabled(false);
  }


  saveUI.buttons.push_back(saveUI.use_old_name);
  saveUI.buttons.push_back(saveUI.use_old_description);

  // Reset possible old failed text
  saveUI.saving_failed = false;
  dialog_active = true;
}

/* Handle sf::TextEntered event */
void LevelEditor::HandleDialogTextEnter(sf::Event event)
{
  if (dialog_active)
  {
    saveUI.name_input.addChar(event.text.unicode);
    saveUI.description_input.addChar(event.text.unicode);
  }
}

/* Handle dialog mouse presses */
void LevelEditor::HandleDialogMousePress(sf::Event event)
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
    else
    {
      // Save level active
      if (saveUI.name_input.tryActivate(x, y))
      {
        saveUI.description_input.deactivate();
        // Also get rid of the error text
        saveUI.saving_failed = false;
      }
      else if (saveUI.description_input.tryActivate(x, y))
      {
        saveUI.name_input.deactivate();
      }
      else
      {
        // Check buttons
        for (auto it = saveUI.buttons.begin(); it != saveUI.buttons.end(); it++)
        {
          if ((*it)->checkClicked(x, y))
          {
            break;
          }
        }
      }

    }
  }
}


/*  Handle dialog_window mouse movement */
void LevelEditor::HandleDialogMouseMove(sf::Event event)
{
  float x = (float) event.mouseMove.x;
  float y = (float) event.mouseMove.y;

  if (messagebox.active)
  {
    // Check if mouse hovers on the messagebox
    messagebox.button.tryActivate(x, y);
  }
  else
  {
    // Handle mouse move in level save
    for (auto it = saveUI.buttons.begin(); it != saveUI.buttons.end(); it++)
    {
      if ((*it)->tryActivate(x, y))
      {
        break;
      }
    }
  }
}


/*  Handle dialog_window KeyPresses */
void LevelEditor::HandleDialogKeyPress(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    // Close the dialog
    cancelSaving();
  }
}

/*  Draw dialog_window */
void LevelEditor::DrawDialog()
{
  if (messagebox.active)
  {
    // Draw messagebox
    dialog_window.draw(messagebox.message);
    dialog_window.draw(messagebox.button);
  }
  else
  {
    dialog_window.draw(saveUI.name);
    dialog_window.draw(saveUI.name_input);
    dialog_window.draw(saveUI.description);
    dialog_window.draw(saveUI.description_input);
    // Also effects for TextInputs
    saveUI.name_input.highlightEffect();
    saveUI.description_input.highlightEffect();

    if (saveUI.saving_failed)
    {
      // Draw only when level saving has failed
      dialog_window.draw(saveUI.fail_text);
    }
    // Draw all buttons
    for (auto it = saveUI.buttons.begin(); it != saveUI.buttons.end(); it++)
    {
      dialog_window.draw(**it);
    }

  }

}

/*  Cancel level saving */
void LevelEditor::cancelSaving()
{
  // Set TextInputs deactivated
  saveUI.name_input.deactivate();
  saveUI.description_input.deactivate();
  dialog_window.close();
  dialog_active = false;
  // Clear all buttons from the level UI container
  saveUI.buttons.clear();
}

/*  Save Level to file */
void LevelEditor::writeLevel()
{
  // Set TextInputs deactivated
  saveUI.name_input.deactivate();
  saveUI.description_input.deactivate();
  // Overwrite old level if user has set name matching level_selected
  int ret_value = -1;
  if (saveUI.name_input.getInputText() == level_selected && level_selected != "")
  {
    // Truncate the old level
    ret_value = level.saveToFile(saveUI.name_input.getInputText(), saveUI.description_input.getInputText(), true);
  }
  else
  {
    // Don't truncate (overwrite)
    ret_value = level.saveToFile(saveUI.name_input.getInputText(), saveUI.description_input.getInputText(), false);
  }
  if (ret_value)
  {
    // Successfully saved

    horizontal_toolbar.info_text.setString("Level succesfully saved");
    horizontal_toolbar.info_counter = 0;

    // Draw Level to rendertexture and save the texture as an image
    sf::RenderTexture level_content;
    level_content.create(Game::WIDTH / 2, Game::HEIGHT / 2);
    sf::View texture_view;
    texture_view.setSize(Game::WIDTH / 2, Game::HEIGHT / 2);
    texture_view.zoom(4); // zoom out ( make 1/ 4 of the normal size)
    texture_view.setCenter(level.getLevelWidth() / 2, Game::HEIGHT / 2);
    level_content.setView(texture_view);
    level_content.clear(BackgoundColor);
    level.drawTexture(level_content);
    level_content.display();
    // The image is named as the level name + .png (and correct path to the folder)
    std::string image_name = "../data/level_img/" + saveUI.name_input.getInputText() + ".png";
    level_content.getTexture().copyToImage().saveToFile(image_name);
    cancelSaving();
  }
  else if (ret_value == -1)
  {
    // Saving failed, file related error
    saveUI.fail_text.setString("Level saving failed: incorrect level name");
    saveUI.saving_failed = true;
  }
  else
  {
    // Saving failed to level missing planes
    saveUI.fail_text.setString("Level cannot be saved: add 1 blue and at least 1 red plane");
    saveUI.saving_failed = true;
  }

}

/*  Cancel from Level Select */
void LevelEditor::cancel_to_mainscreen_action()
{
  // Clear all select_level containers
  level_select.buttons.clear();
  level_select.image_buttons.clear();
  level_select.level_names.clear();
  level_select.curr_button = -1; // init

  // Switch to main screen (LevelEditor)
  screen_mode = MAINSCREEN;

  // Resize the window and set correct title
  window.setSize(sf::Vector2u(Game::WIDTH + vertical_toolbar_width,
                  Game::HEIGHT + horizontal_toolbar_height ));
  window.setTitle("Level Editor");
  ui_view.setSize(Game::WIDTH + vertical_toolbar_width,
                  Game::HEIGHT + horizontal_toolbar_height);
  ui_view.setCenter((Game::WIDTH + vertical_toolbar_width) / 2,
                 (Game::HEIGHT + horizontal_toolbar_height) / 2);

  // Deactivate active color on open button
  vertical_toolbar.open_button->activate(false);
}

/*  Update Level UI to match opened Level */
void LevelEditor::level_selected_action()
{
  // Construct Level
  level_selected = level_select.level_name.getString();
  std::string levelpath = getLevel();
  if (level.parseLevel(levelpath))
  {
    // Success
    // Show info text
    horizontal_toolbar.info_text.setString("Level successfully opened");
    // Make it possible to save with old name & description
    saveUI.opened_level = true;
  }
  else
  {
    horizontal_toolbar.info_text.setString("Level opening failed");
    // Hide Buttons that make possible to save with old name & description
    saveUI.opened_level = false;
  }
  horizontal_toolbar.info_counter = 0;

  // Go back to main screen
  cancel_to_mainscreen_action();
}


/*  Use old name in Save Level */
void LevelEditor::use_old_name_action()
{
  saveUI.name_input.setText(level_selected);
}

/*  Use old description in Save Level */
void LevelEditor::use_old_description_action()
{
  std::string new_desc = level_select.description.getString();
  saveUI.description_input.setText(new_desc);
}

/*  Clear all buttons from containers to avoid duplicates */
void LevelEditor::ClearAllButtons()
{
   // First vertical toolbar buttons
   if (! vtoolbar_buttons.empty())
   {
     vtoolbar_buttons.clear();
   }

  // The horizontal_toolbar
  if (! horizontal_toolbar.essentials.empty())
  {
    horizontal_toolbar.essentials.clear();
  }
  if (! horizontal_toolbar.objectives.empty())
  {
    horizontal_toolbar.objectives.clear();
  }
  if (! horizontal_toolbar.barriers.empty())
  {
    horizontal_toolbar.barriers.clear();
  }

  // Save Level buttons
  if (! saveUI.buttons.empty())
  {
    saveUI.buttons.clear();
  }
}

/*  Init LevelEditor */
void LevelEditor::init()
{
  // Clear all buttons
  ClearAllButtons();
  // Clear level select related containers
  ClearLevelSelectContainers();
  // Set Level opened to standard value
  saveUI.opened_level = false;
}
