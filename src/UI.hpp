/**
  *   @file UI.hpp
  *   @brief Header for UI class
  */

#pragma once


/*  Includes  */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "spdlog/spdlog.h"
#include <iostream>
#include <vector>
#include <memory>
#include "button.hpp"



/*  Macros  */

#define BUTTON_MOUSE 0 /**< Button tried to activate by mouse click */
#define BUTTON_NEXT 1 /**< Tried to activate next button (button above) */
#define BUTTON_PREV 2 /**< Tried to activate previous button (button below) */


/**
  *   @class UI
  *   @brief UI class for air combat game
  */

class UI
{
  public:

    static int MainMenuButtons; /**< Tells how many buttons main menu contains */

    /**
      *   @brief Constructor for UI
      *   @details Creates Main Menu window
      *   @param parent_window RenderWindow which is used to display UI
      */
    UI(sf::RenderWindow *parent_window);

    /**
      *   @brief Get window status
      *   @return Returns false if window is closed, else true
      */
    bool getStatus();

    /**
      *   @brief Update window based on sf::Events
      *   @details Calls window.pollEvent in a loop to update the window
      */
    void updateUI();

  protected:

    /**
      *   @brief Handle incoming key presses
      *   @remark Can be reimplemented in a lower class
      */
    virtual void HandleKeyPress(sf::Event event);

    /**
      *   @brief Handle mouse movement
      *   @remark Can be reimplemented in a lower class
      */
    virtual void HandleMouseMove(sf::Event event);

    /**
      *   @brief Handle mouse presses
      *   @remark Can be reimplemented in a lower class
      */
    virtual void HandleMousePress(sf::Event event);

    /**
      *   @brief Handle sf::Window resizing
      *   @remark Can be reimplemented in a lower class
      */
    virtual void HandleResize(sf::Event event);

    /**
      *   @brief Update active button
      *   @param action Tells by which action active button is updated
      *   @remark action should be BUTTON_MOUSE, BUTTON_NEXT or BUTTON_PREV
      */
    void UpdateActiveButton(int action);

    /**
      *   @brief Create main menu
      *   @details Creates all the necessary Buttons
      */
    void CreateMainMenu();

    /**
      *   @brief Draws main menu
      */
    void DrawMenu();

    /**
      *   @brief Activate current_button
      */
    void ActivateCurrentButton();

    /**
      *   @brief Click current_button
      */
    void ClickCurrentButton();

    /*  Only for testing */
    void Test1(){std::cout << "BUTTON1____________CLICKED" << std::endl;}
    void Test2(){std::cout << "BUTTON2____________CLICKED" << std::endl;}
    void Test3(){std::cout << "BUTTON3____________CLICKED" << std::endl;}
    void Test4(){std::cout << "BUTTON4____________CLICKED" << std::endl;}


    /*  Variables */

    sf::RenderWindow *window;
    bool window_status = true; /**< Is window active (not closed) */

  private:
    int current_button = 0; /**< Which button is currently active */
    std::vector<std::shared_ptr <Button> > buttons;



};
