/**
  *   @file LevelEditor.cpp
  *   @brief Source file for LevelEditor class
  */

#include "LevelEditor.hpp"


/*  Class LevelEditor */

/*  Class variable initializations */
unsigned LevelEditor::Window_Width = 800;
unsigned LevelEditor::Window_Height = 600;


/*  Constructor for LevelEditor */

LevelEditor::LevelEditor(sf::RenderWindow &render_window, sf::RenderWindow &dialog):
UI(render_window, dialog, sf::Color::White)
{
  CreateEditorWindow();
  ui_view = window.getDefaultView();
  level.setYLimit(LevelEditor::Window_Height); // This must be set
}

/*  Create LevelEditor UI */

void LevelEditor::CreateEditorWindow()
{
  // Recreate the window with correct size
  unsigned window_width = LevelEditor::Window_Width + vertical_toolbar_width;
  unsigned window_height = LevelEditor::Window_Height + horizontal_toolbar_height;
  window.create(sf::VideoMode(window_width, window_height), "Level Editor", sf::Style::Close);

  CreateVerticalToolbar(window_height);
  CreateHorizontalToolbar(window_width);

  // Create another view for level (it's crusial to make divisions with floats)
  float level_width = (float)LevelEditor::Window_Width / (float) window_width;
  float level_height = (float) LevelEditor::Window_Height / (float) window_height;
  float level_x = (float) vertical_toolbar_width / (float) window_width;
  float level_y = (float) horizontal_toolbar_height / (float) window_height;
  level_view.setViewport(sf::FloatRect(level_x, level_y, level_width, level_height));
  level_view.setSize(sf::Vector2f(LevelEditor::Window_Width, LevelEditor::Window_Height));
  level_view.setCenter(sf::Vector2f(LevelEditor::Window_Width / 2, LevelEditor::Window_Height / 2));

}


/*  Draw current LevelEditor window */

void LevelEditor::DrawUI()
{
  // Draw toolbars

  DrawVerticalToolbar();
  DrawHorizontalToolbar();

  window.setView(level_view);

  // Draw Level
  level.drawLevel(window);

  window.setView(ui_view);


}

/* Handle key presses */

void LevelEditor::HandleKeyPress(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    // Close window
    window.close();
    window_status = false;
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
    }
  }
  else
  {
    // Mouse hovers on the Level

    // Move current LevelEntity, use Level coordinates
    float level_x = x - vertical_toolbar_width + view * (float) LevelEditor::Window_Width;
    float level_y = y - horizontal_toolbar_height;
    level.moveCurrentEntity(level_x, level_y);
  }

}


/*  Handle mouse movement */

void LevelEditor::HandleMousePress(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;

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
          }
          else if (horizontal_toolbar.show_objectives->checkClicked(x, y))
          {
            clicked = true;
            horizontal_toolbar.show_essentials->setUnchecked();
          }
        }
      }
    }

    else
    {
      // Cursor inside Level

      // Place or create new LevelEntity
      // Notice that coordinate system origin differs in Level realative to LevelEditor
      float level_x = x - vertical_toolbar_width + view * (float) LevelEditor::Window_Width;
      float level_y = y - horizontal_toolbar_height;

      level.addEntity(level_x, level_y, current_entity_type);
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

  // Set text colors
  vertical_toolbar.save_button->setTextColor(sf::Color::White);
  vertical_toolbar.open_button->setTextColor(sf::Color::White);
  vertical_toolbar.help_button->setTextColor(sf::Color::White);
  // Set active colors
  vertical_toolbar.save_button->setActiveColor(sf::Color(50, 50, 50, 255));
  vertical_toolbar.open_button->setActiveColor(sf::Color(50, 50, 50, 255));
  vertical_toolbar.help_button->setActiveColor(sf::Color(50, 50, 50, 255));

  // Set actions
  vertical_toolbar.save_button->setClickFunction( std::bind(&LevelEditor::save_button_action, this));
  vertical_toolbar.open_button->setClickFunction( std::bind(&LevelEditor::open_button_action, this));
  vertical_toolbar.help_button->setClickFunction( std::bind(&LevelEditor::help_button_action, this));

  // Set positions
  vertical_toolbar.save_button->setPosition(5, 110);
  vertical_toolbar.open_button->setPosition(5, 10);
  vertical_toolbar.help_button->setPosition(5, window_height - 200 );

  // Add to the container
  vtoolbar_buttons.push_back(vertical_toolbar.save_button);
  vtoolbar_buttons.push_back(vertical_toolbar.open_button);
  vtoolbar_buttons.push_back(vertical_toolbar.help_button);

  // Create view related buttons
  vertical_toolbar.view_right = std::make_shared<ImageButton>("", RIGHT_ARROW_IMG,
                                100, 100);
  vertical_toolbar.view_right->setScale(0.2);
  float right_arrow_x = 5 + width / 2;
  vertical_toolbar.view_right->setPosition(right_arrow_x, window_height - 80);
  vertical_toolbar.view_left = std::make_shared<ImageButton>("", LEFT_ARROW_IMG,
                                100, 100);
  vertical_toolbar.view_left->setScale(0.2);
  vertical_toolbar.view_left->setPosition(right_arrow_x - 30, window_height - 80);

  // Set click actions
  vertical_toolbar.view_left->setClickFunction( std::bind(&LevelEditor::view_left_action, this));
  vertical_toolbar.view_right->setClickFunction( std::bind(&LevelEditor::view_right_action, this));

  // Add to the container
  vtoolbar_buttons.push_back(vertical_toolbar.view_right);
  vtoolbar_buttons.push_back(vertical_toolbar.view_left);

  // disable view_left (start view is the left most view)
  vertical_toolbar.view_left->setEnabled(false);

  // Set buttons uncheckable
  vertical_toolbar.view_left->setCheckable(false);
  vertical_toolbar.view_right->setCheckable(false);

}



void LevelEditor::save_button_action()
{
  std::cout << "Save button pressed " << std::endl;
}

void LevelEditor::open_button_action()
{
  std::cout << "Open button pressed" << std::endl;
}

void LevelEditor::help_button_action()
{
  std::cout << "Help button pressed" << std::endl;
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
  horizontal_toolbar.rect = sf::RectangleShape(sf::Vector2f(LevelEditor::Window_Width, horizontal_toolbar_height));
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
                                          ("Erase", ERASE_IMG, 40, 40);
  std::shared_ptr<ImageButton> add_infantry = std::make_shared<ImageButton>
                                        ("Add infantry", INFANTRY_IMG, 40, 40);
  std::shared_ptr<ImageButton> add_plane = std::make_shared<ImageButton>
                                        ("Add plane", PLANE_IMG, 40, 40);
  erase_entity->setPosition(150, 5);
  erase_entity->setHighlightColor(sf::Color(50, 50, 50, 160));
  add_infantry->setPosition(250, 5);
  add_plane->setPosition(350, 5);
  erase_entity->setClickFunction( std::bind(&LevelEditor::erase_entity_action, this));
  add_infantry->setClickFunction( std::bind(&LevelEditor::add_infantry_action, this));
  add_plane->setClickFunction( std::bind(&LevelEditor::add_plane_action, this));

  // Add all buttons to the container
  horizontal_toolbar.essentials.push_back(erase_entity);
  horizontal_toolbar.essentials.push_back(add_infantry);
  horizontal_toolbar.essentials.push_back(add_plane);

  // Create all OBJECTIVES_MODE ImageButtons
  // Add erase_entity also to objectives
  horizontal_toolbar.objectives.push_back(erase_entity);

  // Create Buttons to change mode
  horizontal_toolbar.show_essentials = std::make_shared<Button>("Essentials",
                                  sf::Color::Transparent, 140, 20);
  horizontal_toolbar.show_objectives = std::make_shared<Button>("Objectives",
                                  sf::Color::Transparent, 140, 20);
  //Tune text size and style
  horizontal_toolbar.show_essentials->setTextStyle(sf::Text::Regular, 12, sf::Color::Black);
  horizontal_toolbar.show_objectives->setTextStyle(sf::Text::Regular, 12, sf::Color::Black);

  // Set active_color
  horizontal_toolbar.show_essentials->setActiveColor(sf::Color(50, 50, 50, 200));
  horizontal_toolbar.show_objectives->setActiveColor(sf::Color(50, 50, 50, 200));

  // Set positions
  horizontal_toolbar.show_essentials->setPosition(window_width - 170, 5);
  horizontal_toolbar.show_objectives->setPosition(window_width - 170, 35);

  // Set click_actions
  horizontal_toolbar.show_essentials->setClickFunction( std::bind(&LevelEditor::show_essentials_action, this));
  horizontal_toolbar.show_objectives->setClickFunction( std::bind(&LevelEditor::show_objectives_action, this));

  // Set checkable
  horizontal_toolbar.show_essentials->setCheckable(true);
  horizontal_toolbar.show_objectives->setCheckable(true);
  // Set show_essentials checked to match the initial window UI
  horizontal_toolbar.show_essentials->setChecked();
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
}

void LevelEditor::add_infantry_action()
{
  current_entity_type = INFANTRY_ENTITY;
}

void LevelEditor::add_plane_action()
{
  current_entity_type = PLANE_ENTITY;
}

void LevelEditor::erase_entity_action()
{
  current_entity_type = ERASE_ENTITY;
  level.removeCurrent();
}

/*  Switch to ESSENTIALS_MODE, clear current_entity */
void LevelEditor::show_essentials_action()
{
  horizontal_toolbar.mode = ESSENTIALS_MODE;
  current_entity_type = NO_ENTITY;
  level.removeCurrent();
  // Set all objectives buttons unchecked
  for (auto it = horizontal_toolbar.objectives.begin(); it != horizontal_toolbar.objectives.end(); it++)
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
  // Set all essentials buttons unchecked
  for (auto it = horizontal_toolbar.essentials.begin(); it != horizontal_toolbar.essentials.end(); it++)
  {
    (*it)->setUnchecked();
  }
}

/* Move view one Window_Width left */
void LevelEditor::view_left_action()
{
  view --;
  level_view.setCenter(sf::Vector2f((float) LevelEditor::Window_Width * (0.5 + view), (float) LevelEditor::Window_Height / 2));
  if (view == 0.f)
  {
    // Disable left_arrow (inpossible to move left)
    vertical_toolbar.view_left->setEnabled(false);
  }
}

/* Move view one Window_Width right */
void LevelEditor::view_right_action()
{
  // Enable left_arrow
  vertical_toolbar.view_left->setEnabled(true);
  view ++;
  level_view.setCenter(sf::Vector2f((float) LevelEditor::Window_Width * (0.5 + view), (float) LevelEditor::Window_Height / 2));
}
