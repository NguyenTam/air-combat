/**
  *   @file Stats_test.cpp
  *   @brief Test main for Stats class
  */

#include "../src/Stats.hpp"


/**
  *   @brief Test main for Stats
  */

int main()
{
  // Create RenderWindow and construct Stats
  sf::RenderWindow window;
  window.create(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Main Menu", sf::Style::Close);
  Stats stats = Stats(window);

  // Update Stats until user exits Stats
  stats.createStats();
  stats.update();
  // Get ExitStatus from Stats
  int exit_status = stats.getExitStatus();
  std::cout << "ExitStatus: " << exit_status << std::endl;
  return 0;
}
