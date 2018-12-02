/**
   @file GameEngine_test.cpp
   @brief Test file for GameEngine class
 */

#include "../src/GameEngine.hpp"

int main()
{
  sf::RenderWindow window;
  window.create(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Main Menu", sf::Style::Close);
  GameEngine game(window);
  game.run();
  return 0;
}
