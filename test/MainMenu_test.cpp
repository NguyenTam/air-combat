/**
  *   @file MainMenu_test.cpp
  *   @brief Test file for MainMenu class
  */


#include "../src/MainMenu.hpp"




int main ()
{

  sf::RenderWindow window;
  sf::RenderWindow dialog_window;
  sf::RenderWindow help_window;

  // Create window, size and name don't matter, createMainScreen handles those
  window.create(sf::VideoMode(800, 600), "", sf::Style::Close);

  MainMenu menu = MainMenu(window, dialog_window, help_window);
  menu.createMainScreen();

  while (menu.getStatus() == 1)
  {
    menu.updateUI();
  }

  return 0;
}
