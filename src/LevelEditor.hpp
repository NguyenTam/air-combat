/**
  *   @file LevelEditor.hpp
  *   @brief Header for class LevelEditor
  */

#pragma once

/*  Includes  */

#include <iostream>
#include <vector>
#include <memory>
#include "UI.hpp"
#include "image_button.hpp"



/*  Macros */

#define INFANTRY_IMG "../data/img/infantry.png" /**< Path to infantry.png */
#define PLANE_IMG "../data/img/plane.png" /**< Path to plane.png */


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
      *   @remark Class UI constructor with render_window as an argument
      */
    LevelEditor(sf::RenderWindow &render_window, sf::RenderWindow &dialog);

    /* Test functions for button click */
    void Test1(){std::cout << "Clicked________BUTTON______1" << std::endl;}
    void Test2(){std::cout << "Clicked________BUTTON______2" << std::endl;}


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


    /*  Variables */

    std::vector<std::shared_ptr <ImageButton>> buttons;
    ImageButton *clicked_button = nullptr;
    sf::Font message_font;
    sf::Text message;
};
