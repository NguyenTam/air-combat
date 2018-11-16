/**
  *   @file LevelEditor_test.cpp
  *   @brief Contains test main for LevelEditor
  */


#include "../src/LevelEditor.hpp"

int main()
{

  // Create a RenderWindow
  sf::RenderWindow window;
  window.create(sf::VideoMode(800, 600), "Level Editor", sf::Style::Default);

  LevelEditor editor = LevelEditor(&window);
  while(editor.getStatus() == 1)
  {
    editor.updateUI();
  }
  return 0;
}
