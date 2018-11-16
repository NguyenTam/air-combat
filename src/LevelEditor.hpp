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
      *   @param render_window RenderWindow instance pointer
      *   @remark Class UI constructor with render_window as an argument
      */
    LevelEditor(sf::RenderWindow *render_window);

    /* Test functions for button click */
    void Test1(){std::cout << "Clicked________BUTTON______1";}
    void Test2(){std::cout << "Clicked________BUTTON______2";}

  protected:
    
    /**
      *   @brief Draw all buttons and other UI objects
      *   @remark Defined as pure virtual method in UI
      */
    virtual void DrawUI();

    /**
      *   @brief Handle incoming key presses
      *   @remark Defined as a pure virtual method in UI
      */
    virtual void HandleKeyPress(sf::Event event);

    /**
      *   @brief Handle mouse movement
      *   @remark Defined as a pure virtual method in UI
      */
    virtual void HandleMouseMove(sf::Event event);

    /**
      *   @brief Handle mouse presses
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


    /*  Variables */

    std::vector<std::shared_ptr <ImageButton>> buttons;

};
