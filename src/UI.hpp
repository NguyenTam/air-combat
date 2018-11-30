/**
  *   @file UI.hpp
  *   @brief Header for UI class and structs related to it
  */

#pragma once

/* To get rid of sf::setColor deprecated warnings uncomment:
#define SFML_NO_DEPRECATED_WARNINGS */

/*  Includes  */

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <experimental/filesystem>
#include <fstream>
#include "button.hpp"
#include "image_button.hpp"



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


enum ScreenMode
{
  MAINSCREEN,
  LEVELSELECT,
  SETTINGS,
  STATS,

};

enum ExitStatus
{
  QUIT,
  STARTGAME,
  STARTEDITOR,
};

/**
  *   @struct LevelSelect
  *   @brief Struct used to draw Level select window
  */
struct LevelSelect
{
  sf::Text level_name; /**< Level name displayed */
  sf::Font font; /**< Font used in texts FONT_COURIER */
  sf::Text description; /**< Level description */
  sf::Texture level_texture; /**< Texture of the current level image */
  sf::Sprite level_image; /**< Image of the currently displayed level */

  std::vector <std::shared_ptr<Button>> buttons; /**< Cancel and select buttons */
  std::vector <std::shared_ptr<ImageButton>> image_buttons; /**< Left & right buttons */
  std::vector <std::string> level_names; /**< Container for all level filenames */
  int curr_level = -1;
  int max_level = -1;

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
      *   @brief Close active dialog
      */
    void CloseDialog();

    /**
      *   @brief Get level path which user selected
      *   @details Intended to be used from main to get correct level file
      *   name for the main game
      *   @return Returns level name string (path + .txt added)
      */
    std::string getLevel();


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

    /**
      *   @brief Handle sf::TextEntered event
      *   @remark Virtual method, can be redefined in lower classes
      */
    virtual void HandleDialogTextEnter(sf::Event event) {std::cout << event.type << std::endl;}

    /**
      *   @brief Handle dialog_window sf::KeyPress event
      *   @remark Virtual method, can be redefined in lower classes
      */
    virtual void HandleDialogKeyPress(sf::Event event) {std::cout << event.type << std::endl;}

    /**
      *   @brief Create select level screen
      *   @details This method is called from MainMenu and LevelEditor
      */
    void CreateSelectLevel();

    /**
      *   @brief Draw Level select window
      */
    void DrawLevelSelect();

    /**
      *   @brief Close main window
      *   @details This is executed when user wants to stop the program
      */
    void CloseWindow();

    /**
      *   @brief Update Level select screen
      *   @param event sf::Event
      */
    void UpdateLevelSelect(sf::Event);

    /**
      *   @brief Action for select_level select button
      *   @details Does preparations to starts the main game
      *   @remark Needs to be reimplemented in LevelEditor
      */
    virtual void level_selected_action();

    /**
      *   @brief Action for select_level cancel button
      *   @details Switches screen_mode to MAINSCREEN
      *   @brief Needs to be reimplemented in LevelEditor
      */
    virtual void cancel_to_mainscreen_action();

    /**
      *   @brief Pure virtual method which recreates correct window
      *   @details This has to be defined in MainMenu and LevelEditor
      */
    virtual void CreateMainScreen() = 0;

    /**
      *   @brief Update select_level to show corret level in screen
      */
    void UpdateLevelShown();

    /**
      *   @brief Parse description from Level file
      *   @filepath Path to the Level file
      *   @return Returns description as a string
      */
    std::string ParseDescription(const std::string& filepath);

    /**
      *   @brief Display next level
      *   @remark Does nothing if current level is the last level
      */
    void LevelSelectNext();

    /**
      *   @brief Display prev level
      *   @brief Does nothing if current level is first level
      */
    void LevelSelectPrev();

    /*  Variables */

    sf::RenderWindow &window; /**< Main window */
    sf::RenderWindow &dialog_window; /**< Window used to display dialogs */
    bool dialog_active = false; /**< Whether a dialog is active or not */
    int window_status = 1; /**< 1 window active, 0 closed */
    sf::Color BackgoundColor; /**< Background color */
    struct MessageBox messagebox; /**< MessageBox instance */
    ScreenMode screen_mode = MAINSCREEN;
    ExitStatus exit_status;
    LevelSelect level_select;
    std::string level_selected; /**< Level name which user selected */

};
