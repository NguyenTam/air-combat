/**
  *   @file LevelEditor_test.cpp
  *   @brief Contains test main for LevelEditor
  */


#include "../src/LevelEditor.hpp"

int main()
{

  // Create empty RenderWindows
  sf::RenderWindow window;
  sf::RenderWindow dialog_window;
  sf::RenderWindow help_window;

  // Create window, size and name don't matter, createMainScreen handles those
  window.create(sf::VideoMode(800, 600), "Level Editor", sf::Style::Close);
  LevelEditor editor = LevelEditor(window, dialog_window, help_window);
  editor.createMainScreen();

  while(editor.getStatus() == 1)
  {
    editor.updateUI();
  }
  return 0;
}
