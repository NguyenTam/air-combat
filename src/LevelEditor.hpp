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
#include "TextInput.hpp"
#include "CommonDefinitions.hpp"



/*  Macros */

#define ESSENTIALS_MODE 1 /**< HorizontalToolbar mode, essentials shown */
#define OBJECTIVES_MODE 2  /**< HorizontalToolbar mode, objectives shown */
#define BARRIERS_MODE 3 /**< HorizontalToolbar mode, barriers shown */


/**
  *   @struct VerticalToolbar
  *   @brief Defines vertical toolbar with basic button actions
  */
struct VerticalToolbar
{
  std::shared_ptr <Button> save_button; /**< Save Button */
  std::shared_ptr <Button> open_button; /**< Open Button */
  std::shared_ptr <Button> quit_button; /**< Quit Button */
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
  std::shared_ptr <Button> show_barriers; /**< Clicking changes to BARRIERS_MODE */

  std::vector<std::shared_ptr <ImageButton>> essentials; /**< Buttons matching essential entities */
  std::vector<std::shared_ptr <ImageButton>> objectives; /**< Buttons matching objective entities */
  std::vector<std::shared_ptr <ImageButton>> barriers; /**< Buttons matching barrier entities */

  std::shared_ptr <ImageButton> add_ground; /**< Start placing ground */
  std::shared_ptr <Button> place_ground; /**< Place ground entity */
  std::shared_ptr <Button> cancel_ground; /**< Cancel placing ground */
  sf::Text info_text; /**< Text used to display information */
  sf::Font info_font; /**< Font for info_text */
  int info_counter = 10000; /**< Used to determine if info_text should be drawn or not */
};

/**
  *   @struct SaveLevelUI
  *   @brief Defines UI for save level
  */
struct SaveLevelUI
{
  sf::Text name; /**< Level name text */
  sf::Font font; /**< Font used with name */
  TextInput name_input; /**< Strict TextInput for level name */
  TextInput description_input; /**< TextInput for level description */
  sf::Text description; /**< Description text */
  sf::Text fail_text; /**< Saving failed text */
  std::shared_ptr<Button> save; /**< Button to save level */
  std::shared_ptr<Button> cancel; /**< Button to cancel from save level */
  std::shared_ptr<Button> use_old_name; /**< Button to use old level name */
  std::shared_ptr<Button> use_old_description; /**< Button to use old description */
  std::vector<std::shared_ptr <Button>> buttons; /**< Container for Buttons */
  bool saving_failed = false; /**< Whether level saving has failed */
  bool opened_level = false; /**< Whether user has opened level */

};


/**
  *   @class LevelEditor
  *   @brief Defines a level editor used in air combat game
  *   @details Inherits UI to update the window
  */

class LevelEditor: public UI
{
  public:

    /**
      *   @brief Constructor for LevelEditor
      *   @param render_window RenderWindow instance as reference
      *   @param dialog Another RenderWindow used for dialogs
      *   @param help RenderWindow for help screen
      */
    LevelEditor(sf::RenderWindow &render_window, sf::RenderWindow &dialog,
                sf::RenderWindow &help);

    /**
      *   @brief Create editor window
      *   @details Sets up buttons and other LevelEditor UI objects
      *   @remark Called from the constructor. Defined as pure virtual in UI
      */
    virtual void createMainScreen();

    /**
      *   @brief Click action for add_friendly_infantry button (horizontal_toolbar)
      *   @details Change current_entity_type to FRIENDLY_INFANTRY
      */
    void add_friendly_infantry_action();

    /**
      *   @brief Click action for add_hostile_infantry button (horizontal_toolbar)
      *   @details Change current_entity_type to HOSTILE_INFANTRY
      */
    void add_hostile_infantry_action();

    /**
      *   @brief Click action for add_friendly_plane button (horizontal_toolbar)
      *   @details Change current_entity_type to FRIENDLY_PLANE
      */
    void add_friendly_plane_action();

    /**
      *   @brief Click action for add_hostile_plane button (horizontal_toolbar)
      *   @details Change current_entity_type to HOSTILE_PLANE
      */
    void add_hostile_plane_action();

    /**
      *   @brief Click action for add_friendly_AA button (horizontal_toolbar)
      *   @details Change current_entity_type to FRIENDLY_AA
      */
    void add_friendly_AA_action();

    /**
      *   @brief Click action for add_hostile_AA button (horizontal_toolbar)
      *   @details Change current_entity_type to HOSTILE_AA
      */
    void add_hostile_AA_action();

    /**
      *   @brief Click action for add_friendly_hangar button (horizontal_toolbar)
      *   @details Change current_entity_type to FRIENDLY_HANGAR
      */
    void add_friendly_hangar_action();

    /**
      *   @brief Click action for add_hostile_hangar button (horizontal_toolbar)
      *   @details Change current_entity_type to HOSTILE_HANGAR
      */
    void add_hostile_hangar_action();

    /**
      *   @brief Click action for add_friendly_base button (horizontal_toolbar)
      *   @details Change current_entity_type to FRIENDLY_BASE
      */
    void add_friendly_base_action();

    /**
      *   @brief Click action for add_hostile_base button (horizontal_toolbar)
      *   @details Change current_entity_type to HOSTILE_BASE
      */
    void add_hostile_base_action();

    /**
      *   @brief Click action for add_tree button (horizontal_toolbar)
      *   @details Change current_entity_type to TREE_ENTITY
      */
    void add_tree_action();

    /**
      *   @brief Click action for add_rock button (horizontal_toolbar)
      *   @details Change current_entity_type to ROCK_ENTITY
      */
    void add_rock_action();


    /**
      *   @brief Click action for erase_entity button (horizontal_toolbars)
      *   @details Change current_entity_type to ERASE_ENTITY
      */
    void erase_entity_action();

    /**
      *   @brief Click action for add_ground button (horizontal_toolbar)
      *   @details Change current_entity_type to GROUND_ENTITY
      */
    void add_ground_action();

    /**
      *   @brief Click action for place_ground button (horizontal_toolbar)
      */
    void place_ground_action();

    /**
      *   @brief Click action for cancel_ground button (horizontal_toolbar)
      */
    void cancel_ground_action();

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
      *   @brief Click action for vertical_toolbar quit_button
      */
    void quit_button_action();

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
      *   @brief Click action for horizontal_toolbar show_barriers button
      *   @brief Clears current_entity and switches to BARRIERS_MODE
      */
    void show_barriers_action();


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

    /**
      *   @brief Cancel from level saving
      *   @details Closes dialog_window
      */
    void cancelSaving();

    /**
      *   @brief Write Level to file
      *   @details On success returns to main level editor window. Otherwise,
      *   remains in the save dialog (and shows error text to user)
      */
    void writeLevel();

    /**
      *   @brief Click action for use_old_name button (Save Level)
      */
    void use_old_name_action();

    /**
      *   @brief Click action for use_old_description button (Save Level)
      */
    void use_old_description_action();

    /**
      *   @brief Init LevelEditor to safe state to restart it
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

    /**
      *   @brief Handle sf::TextEntered event
      *   @remark Redefined from UI::HandleTextEnter
      */
    virtual void HandleDialogTextEnter(sf::Event event);

    /**
      *   @brief Handle dialog_window mouse presses
      *   @remark Redefined from UI::HandleDialogMousePress
      *   @param event sf::Event
      */
    virtual void HandleDialogMousePress(sf::Event event);

    /**
      *   @brief Handle dialog_window mouse movement
      *   @remark reimplemented from UI::HandleDialogMouseMove
      *   @param event Mouse move sf::Event
      */
    virtual void HandleDialogMouseMove(sf::Event event);

    /**
      *   @brief Handle dialog_window key presses
      *   @remark Redefined from UI::HandleDialogKeyPress
      *   @param event sf::Event
      */
    virtual void HandleDialogKeyPress(sf::Event event);

    /**
      *   @brief Draw dialog_window
      *   @remark reimplemented from UI, used while user is saving level
      */
    virtual void DrawDialog();

    /**
      *   @brief Action for level_selected button (UI::level_select)
      *   @remark Reimplemented from the base class UI
      */
    virtual void level_selected_action();

    /**
      *   @brief Action for cancel button in UI::level_select
      *   @remark Reimplemented from the base class UI
      */
    virtual void cancel_to_mainscreen_action();

  private:

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

    /**
      *   brief Create dialog to save Level
      */
    void SaveLevel();

    /**
      *   @brief Clear all buttons
      *   @remark Call this from main when on exit from LevelEditor
      *   @details Buttons are shared_ptrs so no memory leaks should emerge.
      *   Next time when toolbars are recreated e.g. horizontal_toolbar.add_ground
      *   is replaced with new std::shared_ptr, then old buttons reference count is 0
      *   and it is deleted automatically. So clearing is done to avoid duplicate buttons
      *   in the containers
      */
    void ClearAllButtons();


    /*  Variables */

    std::vector<std::shared_ptr <Button>> vtoolbar_buttons;
    ImageButton *clicked_button = nullptr;
    unsigned vertical_toolbar_width = 120;
    unsigned horizontal_toolbar_height = 100;

    VerticalToolbar vertical_toolbar;
    HorizontalToolbar horizontal_toolbar;
    float view = 0; /**< Tells position on the level view */
    sf::View level_view;

    Level level; /** Level Object */
    int current_entity_type = NO_ENTITY; /**< Used with Level::addEntity() */
    struct SaveLevelUI saveUI;

};
