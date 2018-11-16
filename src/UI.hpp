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


/**
  *   @class UI
  *   @brief UI class for air combat game
  *   @details An abstract class which is inherited by MainMenu and LevelEditor
  */

class UI
{
  public:

    /**
      *   @brief Constructor for UI
      *   @param render_window window for UI
      *   @param backgroundcolor UI BackgoundColor
      **  @remark render_window should probably be a stack object in the main
      */
    UI(sf::RenderWindow *render_window, sf::Color backgroundcolor);

    /**
      *   @brief Update UI
      *   @details Called from the main to update MainMenu or LevelEditor
      *   @remark Can be reimplemented in a lower class
      */
    virtual void updateUI();

    /**
      *   @brief Get window status
      *   @return Returns 0 if window is closed
      */
    int getStatus();


  protected:

    /**
      *   @brief Draw all UI objects
      *   @remark Pure virtual method, implemented in a lower class
      */
    virtual void DrawUI() = 0;

    /**
      *   @brief Handle incoming key presses
      *   @remark Pure virtual method, implemented in a lower class
      */
    virtual void HandleKeyPress(sf::Event event) = 0;

    /**
      *   @brief Handle mouse movement
      *   @remark Pure virtual method, implemented in a lower class
      */
    virtual void HandleMouseMove(sf::Event event) = 0;

    /**
      *   @brief Handle mouse presses
      *   @remark Pure virtual method, implemented in a lower class
      */
    virtual void HandleMousePress(sf::Event event) = 0;

    /**
      *   @brief Handle sf::Window resizing
      *   @remark Can be reimplemented in a lower class
      */
    virtual void HandleResize(sf::Event event);



    /*  Variables */

    sf::RenderWindow *window;
    int window_status = 1; /**< 1 window active, 0 closed */
    sf::Color BackgoundColor;

};
