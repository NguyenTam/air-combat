/**
  *   @file MainMenu_test.cpp
  *   @brief Test file for MainMenu class
  */


#include "../src/MainMenu.hpp"




int main ()
{

  sf::RenderWindow window;
  sf::RenderWindow dialog_window;

  MainMenu menu = MainMenu(window, dialog_window);

  while (menu.getStatus() == 1)
  {
    menu.updateUI();
  }

  return 0;
}
