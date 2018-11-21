/**
  *   @file LevelEditor.hpp
  *   @brief Header for class LevelEditor and structs relating to it
  */

#pragma once

/*  Includes  */

#include <iostream>
#include <vector>
#include <memory>
#include "UI.hpp"
#include "image_button.hpp"
#include "button.hpp"
#include "Level.hpp"



/*  Macros */

#define INFANTRY_IMG "../data/img/infantry.png" /**< Path to infantry.png */
#define PLANE_IMG "../data/img/plane.png" /**< Path to plane.png */
#define RIGHT_ARROW_IMG "../data/img/right_arrow.png" /**< Path to right_arrow.png */
#define LEFT_ARROW_IMG "../data/img/left_arrow.png" /**< Path to left_arrow.png */
#define ERASE_IMG "../data/img/erase.png" /**< Path to erase.png */
#define ESSENTIALS_MODE 1 /**< HorizontalToolbar mode, essentials shown */
#define OBJECTIVES_MODE 2  /**< HorizontalToolbar mode, objectives shown */


/**
  *   @struct VerticalToolbar
  *   @brief Defines vertical toolbar with basic button actions
  */
struct VerticalToolbar
{
  std::shared_ptr <Button> save_button; /**< Save Button */
  std::shared_ptr <Button> open_button; /**< Open Button */
  std::shared_ptr <Button> help_button; /**< Help Button */
  sf::RectangleShape rect; /**< Toolbar rect */

  std::shared_ptr <ImageButton> view_left; /**< Change view left */
  std::shared_ptr <ImageButton> view_right; /**< Change view right */
};

/**
  *   @struct HorizontalToolbar
  *   @brief Defines horizontal toolbar with basic button actions
  */
struct HorizontalToolbar
{
  int mode = ESSENTIALS_MODE; /**< Tells which buttons are shown */
  sf::RectangleShape rect; /**< Toolbar rect */
  sf::Vertex line[2]; /**< Line between the toolbars */
  sf::Vertex separator_line[2]; /**< Line that separates buttons */

  std::shared_ptr <Button> show_essentials; /**< Clicking changes to ESSENTIALS_MODE */
  std::shared_ptr <Button> show_objectives; /**< Clicking changes to OBJECTIVES_MODE */

  std::vector<std::shared_ptr <ImageButton>> essentials; /**< Buttons matching essential entities */
  std::vector<std::shared_ptr <ImageButton>> objectives; /**< Buttons matching objective entities */

};


/**
  *   @class LevelEditor
  *   @brief Defines a level editor used in air combat game
  *   @details Inherits UI to update the window
  */

class LevelEditor: public UI
{
  public:

    /**< Air combat main game window width */
    static unsigned Window_Width;

    /**< Air combat main game window height */
    static unsigned Window_Height;

    /**
      *   @brief Constructor for LevelEditor
      *   @param render_window RenderWindow instance as reference
      *   @remark Class UI constructor with render_window as an argument
      */
    LevelEditor(sf::RenderWindow &render_window, sf::RenderWindow &dialog);

    /**
      *   @brief Click action for add_infantry button (horizontal_toolbar)
      *   @details Change current_entity_type to INFANTRY_ENTITY
      */
    void add_infantry_action();

    /**
      *   @brief Click action for add_plane button (horizontal_toolbar)
      *   @details Change current_entity_type to PLANE_ENTITY
      */
    void add_plane_action();

    /**
      *   @brief Click action for erase_entity button (both toolbars)
      *   @details Change current_entity_type to ERASE_ENTITY
      */
    void erase_entity_action();

    /**
      *   @brief Click action for vertical_toolbar save_button
      */
    void save_button_action();

    /**
      *   @brief Click action for vertical_toolbar open_button
      */
    void open_button_action();

    /**
      *   @brief Click action for vertical_toolbar help_button
      */
    void help_button_action();

    /**
      *   @brief Click action for horizontal_toolbar show_essentials button
      *   @details Clears current_entity and switches to ESSENTIALS_MODE
      */
    void show_essentials_action();

    /**
      *   @brief Click action for horizontal_toolbar show_objectives button
      *   @brief Clears current_entity and switches to OBJECTIVES_MODE
      */
    void show_objectives_action();

    /**
      *   @brief Click action for vertical_toolbar view_left
      *   @details Moves view one LevelEditor::Window_Width left
      */
    void view_left_action();

    /**
      *   @brief Click action for vertical_toolbar view_right
      *   @details Moves view one LevelEditor::Window_Width right
      */
    void view_right_action();


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
      *   @brief Create editor window
      *   @details Sets up buttons and other LevelEditor UI objects
      *   @remark Called from the constructor
      */
    void CreateEditorWindow();

    /**
      *   @brief Draw current editor window
      *   @details Draws all buttons and graphical objects
      */
    void DrawEditorWindow();

    /**
      *   @brief Set ImageButtons unchecked
      *   @details Calls setUnchecked for all ImageButton that don't match to
      *   button
      *   @param button ImageButton which isn't unchecked (probably clicked_button)
      */
    void UncheckImageButtons(ImageButton *button);

    /**
      *   @brief Create VerticalToolbar
      *   @param window_height LevelEditor window height
      */
    void CreateVerticalToolbar(unsigned window_height);

    /**
      *   @brief Draw VerticalToolbar buttons
      */
    void DrawVerticalToolbar();

    /**
      *   @brief Create HorizontalToolbar
      *   @param window_width LevelEditor window width
      */
    void CreateHorizontalToolbar(unsigned window_width);

    /**
      *   @brief Draw HorizontalToolbar
      */
    void DrawHorizontalToolbar();


    /*  Variables */

    std::vector<std::shared_ptr <Button>> vtoolbar_buttons;
    ImageButton *clicked_button = nullptr;
    unsigned vertical_toolbar_width = 120;
    unsigned horizontal_toolbar_height = 70;

    VerticalToolbar vertical_toolbar;
    HorizontalToolbar horizontal_toolbar;
    float view = 0; /**< Tells position on the level view */
    sf::View ui_view;
    sf::View level_view;

    Level level; /** Level Object */
    int current_entity_type = NO_ENTITY; /**< Used with Level::addEntity() */
};
