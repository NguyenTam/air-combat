/**
  *   @file LevelEditor.cpp
  *   @brief Source file for LevelEditor class
  */

#include "LevelEditor.hpp"


/*  Class LevelEditor */


/*  Constructor for LevelEditor */

LevelEditor::LevelEditor(sf::RenderWindow *render_window):
UI(render_window, sf::Color::White)
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
    window->draw(**it);
  }
}


void LevelEditor::HandleKeyPress(sf::Event event)
{
  std::cout << event.type << std::endl;
}

void LevelEditor::HandleMouseMove(sf::Event event)
{
  std::cout << event.type << std::endl;
}

void LevelEditor::HandleMousePress(sf::Event event)
{
  std::cout << event.type << std::endl;
}
