/**
  *   @file main.cpp
  *   @brief Contains main for Air combat game
  */

#include "UI.hpp"
#include "MainMenu.hpp"
#include "LevelEditor.hpp"
#include "CommonDefinitions.hpp"
#include "GameEngine.hpp"
#include <memory>
/**
  *   @brief Main for Air combat
  *   @details Integrates MainMenu, LevelEditor and TODO Game
  */
int main()
{
  // Create empty RenderWindows
  sf::RenderWindow window;
  sf::RenderWindow dialog_window;
  sf::RenderWindow help_window;
  
  // Create main window (size and name don't matter, MainMenu resizes and renames window)
  window.create(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Main Menu", sf::Style::Close);

  // Create Game Engine
  GameEngine game {window};

  // Create objects
  MainMenu menu = MainMenu(window, dialog_window, help_window);
  LevelEditor editor = LevelEditor(window, dialog_window, help_window);
  int exit_status = ExitStatus::MAINMENU;

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
      std::cout << "Open this level in the base game: " << level_name << std::endl;
      // TODO : From game back to main menu.
      game.run(level_name);      
      exit_status = ExitStatus::MAINMENU;
    }
    if (exit_status == ExitStatus::QUIT)
    {
      break;
    }
  }

  return 0;


}
