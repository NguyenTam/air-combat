/**
  *   @file LevelEditor.cpp
  *   @brief Source file for LevelEditor class
  */

#include "LevelEditor.hpp"


/*  Class LevelEditor */


/*  Constructor for LevelEditor */

LevelEditor::LevelEditor(sf::RenderWindow &render_window, sf::RenderWindow &dialog):
UI(render_window, dialog, sf::Color::White)
{
  CreateEditorWindow();
}

/*  Create LevelEditor UI */

void LevelEditor::CreateEditorWindow()
{
  // Create all ImageButtons
  std::shared_ptr<ImageButton> button1 = std::make_shared<ImageButton>
                                        ("Add infantry", INFANTRY_IMG, 50, 50);
  std::shared_ptr<ImageButton> button2 = std::make_shared<ImageButton>
                                        ("Add plane", PLANE_IMG, 50, 50);
  button1->setPosition(200, 0);
  button2->setPosition(300, 0);
  button1->setClickFunction( std::bind(&LevelEditor::Test1, this));
  button2->setClickFunction( std::bind(&LevelEditor::Test2, this));

  // Add all buttons to the container
  buttons.push_back(button1);
  buttons.push_back(button2);

}


/*  Draw current LevelEditor window */

void LevelEditor::DrawUI()
{
  // Draw all buttons
  for (auto it = buttons.begin(); it != buttons.end(); it++)
  {
    window.draw(**it);
  }
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

  // Check if mouse hovers on ImageButton
  bool activated = false;
  for (auto it = buttons.begin(); it != buttons.end(); it++)
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
    // TODO move LevelObjects
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
    for (auto it = buttons.begin(); it != buttons.end(); it++)
    {
      if ( (*it)->checkClicked(x, y) )
      {
        clicked = true;
        // store pointer to the clicked button
        clicked_button = it->get();
      }
    }

    if (clicked)
    {
      // Set other buttons not clicked (checked)
      UncheckImageButtons(clicked_button);
    }
    else
    {
      // TODO place or create new LevelObjects
    }
  }
}


/*  Uncheck ImageButtons */

void LevelEditor::UncheckImageButtons(ImageButton *button)
{
  for (auto it = buttons.begin(); it != buttons.end(); it++)
  {
    if (it->get() != button)
    {
      (*it)->setUnchecked();
    }
  }
}
