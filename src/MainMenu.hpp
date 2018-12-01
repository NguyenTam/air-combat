/**
  *   @file MainMenu.hpp
  *   @brief Header for MainMenu class
  */

#pragma once


/*  Includes  */

#include <iostream>
#include <vector>
#include <memory>
#include "UI.hpp"
#include "button.hpp"
#include "CommonDefinitions.hpp"



/*  Macros  */

#define BUTTON_NEXT 1 /**< Tried to activate next button (button above) */
#define BUTTON_PREV 2 /**< Tried to activate previous button (button below) */


/**
  *   @class MainMenu
  *   @brief MainMenu class for air combat game
  *   @details Inherits UI to create the main menu
  */

class MainMenu: public UI
{
  public:

    static int MainMenuButtons; /**< Tells how many buttons main menu contains */

    /**
      *   @brief Constructor for MainMenu
      *   @details Creates MainMenu window
      *   @param parent_window RenderWindow which is used to display MainMenu
      *   @param dialog RenderWindow for dialogs
      *   @param help RenderWindow for possible help screen
      */
    MainMenu(sf::RenderWindow &parent_window, sf::RenderWindow &dialog,
              sf::RenderWindow &help);

    /**
      *   @brief Recreates MainMenu window
      *   @remark Defined as pure virtual method in UI
      */
    virtual void createMainScreen();

    /**
      *   @brief Action for select_level Button
      */
    void select_level_action();

    /**
      *   @brief Action for start_editor Button
      *   @details Do necessary changes to swicth to LevelEditor
      */
    void start_editor_action();

    /*  Only for testing */
    void Test3(){std::cout << "BUTTON3____________CLICKED" << std::endl;}
    void Test4(){std::cout << "BUTTON4____________CLICKED" << std::endl;}

    /**
      *   @brief Init MainMenu to safe state to restart it
      *   @details Currently the menu buttons aren't cleared
      *   because those aren't recreated (like LevelEditor recreates Toolbars)
      *   @remark Defined as pure virtual in UI
      */
    virtual void init();

  protected:

    /**
      *   @brief Draw all buttons and other UI objects
      *   @remark Defined as pure virtual method in UI
      */
    virtual void DrawUI();

    /**
      *   @brief Handle incoming key presses
      *   @param event SFML event
      *   @remark Defined as a pure virtual method in UI
      */
    virtual void HandleKeyPress(sf::Event event);

    /**
      *   @brief Handle mouse movement
      *   @param event SFML event
      *   @remark Defined as a pure virtual method in UI
      */
    virtual void HandleMouseMove(sf::Event event);

    /**
      *   @brief Handle mouse presses
      *   @param event SFML event
      *   @remark Defined as a pure virtual method in UI
      */
    virtual void HandleMousePress(sf::Event event);


  private:

    /**
      *   @brief Update active button
      *   @param action Tells by which action active button is updated
      *   @remark action should be BUTTON_NEXT or BUTTON_PREV
      */
    void UpdateActiveButton(int action);

    /**
      *   @brief Create main menu
      *   @details Creates all the necessary Buttons
      */
    void CreateMainMenu();

    /**
      *   @brief Activate current_button
      */
    void ActivateCurrentButton();

    /**
      *   @brief Click current_button
      */
    void ClickCurrentButton();


    /*  Variables */

    int current_button = 0; /**< Which button is currently active */
    std::vector<std::shared_ptr <Button> > buttons;

};
