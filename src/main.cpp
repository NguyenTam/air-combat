/**
  *   @file main.cpp
  *   @brief Contains main for Air combat game
  */

#include "UI.hpp"
#include "MainMenu.hpp"
#include "LevelEditor.hpp"
#include "CommonDefinitions.hpp"
#include "GameEngine.hpp"
#include "Stats.hpp"
#include <memory>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <SFML/Audio/Music.hpp>

/**
  *   @brief Set window position to the center of the screen
  *   @param window sf::RenderWindow to be centered
  */
void setWindowPosition(sf::RenderWindow &window)
{
  // Try to center the window on screen
  int x = (sf::VideoMode::getDesktopMode().width - Game::WIDTH) / 2;
  int y = (sf::VideoMode::getDesktopMode().height - Game::HEIGHT) / 2;
  window.setPosition(sf::Vector2i(x, y));
}


/**
  *   @brief Main for Air combat
  *   @details Integrates MainMenu, LevelEditor and Game
  */
int main()
{
  // random seed
  std::srand(std::time(nullptr));
  
  // Create empty RenderWindows
  sf::RenderWindow window;
  sf::RenderWindow dialog_window;
  sf::RenderWindow help_window;

  // Create main window (size and name don't matter, MainMenu resizes and renames window)
  window.create(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Main Menu", sf::Style::Close);
  setWindowPosition(window);

  // Create Game Engine
  GameEngine game {window};

  // Create objects
  MainMenu menu = MainMenu(window, dialog_window, help_window);
  LevelEditor editor = LevelEditor(window, dialog_window, help_window);
  // Create Stats
  Stats stats = Stats(window);

  int exit_status = ExitStatus::MAINMENU;

  // Create music playback
  sf::Music music;
  music.openFromFile("../data/music/extremeaction.wav");
  music.play();
  music.setLoop(true);

  while(true)
  {
    if (exit_status == ExitStatus::MAINMENU)
    {
      // Create correct window for MainMenu
      menu.createMainScreen();
      while (menu.getStatus())
      {
        menu.updateUI();
      }
      // Init MainMenu to safe state
      menu.init();
      exit_status = menu.getExitStatus();
    }
    if (exit_status == ExitStatus::STARTEDITOR)
    {

      // Create correct window for LevelEditor
      editor.createMainScreen();
      while(editor.getStatus())
      {
        editor.updateUI();
      }
      // Init LevelEditor to safe state
      editor.init();
      exit_status = editor.getExitStatus();
    }
    if (exit_status == ExitStatus::STARTGAME)
    {
      std::string level_name = menu.getLevel();
      game.setGameMode(menu.getGameMode());
      window.setTitle("Air Combat 1");
      game.run(level_name);
      exit_status = ExitStatus::MAINMENU;
      window.setTitle("Main Menu");
    }
    if (exit_status == ExitStatus::QUIT)
    {
      break;
    }
    if (exit_status == ExitStatus::STATS)
    {
      // Update Stats until user exits Stats
      stats.createStats();
      stats.update();
      // Get ExitStatus from Stats
      exit_status = stats.getExitStatus();
      // Init Stats
      stats.init();
    }
  }

  return 0;


}
