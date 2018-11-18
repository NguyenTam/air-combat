/**
  *   @file UI.hpp
  *   @brief Header for UI class and structs related to it
  */

#pragma once


/*  Includes  */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "spdlog/spdlog.h"
#include <iostream>
#include "button.hpp"



/**
  *   @struct MessageBox
  *   @brief Struct used to display message boxes
  */

struct MessageBox
{
  bool active = false; /**< Whether MessageBox is active or not */
  Button button; /**< Button for closing the MessageBox */
  sf::Text message; /**< Text object drawn to MessageBox */
  sf::Font message_font; /**< Font used to draw MessageBoxes */
};




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
      *   @param dialog Another RenderWindow which is used to show dialogs
      *   @param backgroundcolor UI BackgoundColor
      **  @remark render_window should be a stack object in the main
      */
    UI(sf::RenderWindow &render_window, sf::RenderWindow &dialog, sf::Color backgroundcolor);

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

    /**
      *   Close active dialog
      */
    void CloseDialog();


  protected:

    /**
      *   @brief Draw all UI objects
      *   @remark Pure virtual method, implemented in a lower class
      */
    virtual void DrawUI() = 0;

    /**
      *   @brief Draw current dialog to dialog_window
      *   @remark Can be reimplemented in a lower class
      */
    virtual void DrawDialog();

    /**
      *   @brief Handle incoming key presses
      *   @param event SFML event
      *   @remark Pure virtual method, implemented in a lower class
      */
    virtual void HandleKeyPress(sf::Event event) = 0;

    /**
      *   @brief Handle mouse movement
      *   @param event SFML event
      *   @remark Pure virtual method, implemented in a lower class
      */
    virtual void HandleMouseMove(sf::Event event) = 0;

    /**
      *   @brief Handle mouse presses
      *   @param event SFML event
      *   @remark Pure virtual method, implemented in a lower class
      */
    virtual void HandleMousePress(sf::Event event) = 0;

    /**
      *   @brief Handle sf::Window resizing
      *   @param event SFML event
      *   @remark Can be reimplemented in a lower class
      */
    virtual void HandleResize(sf::Event event);

    /**
      *   @brief Handle dialog_window mouse presses
      *   @param event SFML event
      *   @remark Can be reimplemented in a lower class
      */
    virtual void HandleDialogMousePress(sf::Event event);

    /**
      *   @brief Handle dialog_window mouse movement
      *   @param event SFML event
      *   @remark Can be reimplemented in a lower class
      */
    virtual void HandleDialogMouseMove(sf::Event event);

    /**
      *   @brief Show a message box
      *   @param message Message shown in the message box
      *   @param position Initial position for the message box
      *   @bug The created message box isn't locked top of the main window.
      *   This can cause box checking to be fustrating. Fixing the issue seems
      *   complicated and needs low level os window tuning.
      *   @remark All positions related values used within the method are just
      *   result of trial and error to make the box look ok
      */
    void ShowMessageBox(std::string message, sf::Vector2i position);



    /*  Variables */

    sf::RenderWindow &window; /**< Main window */
    sf::RenderWindow &dialog_window; /**< Window used to display dialogs */
    bool dialog_active = false; /**< Whether a dialog is active or not */
    int window_status = 1; /**< 1 window active, 0 closed */
    sf::Color BackgoundColor; /**< Background color */
    struct MessageBox messagebox; /**< MessageBox instance */

};
