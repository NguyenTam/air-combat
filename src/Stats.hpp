/**
  *   @file Stats.hpp
  *   @brief Header for class Stats
  */

#pragma once

/*  Includes */
#include <SFML/Window.hpp>
#include <vector>
#include "UI.hpp"
#include "button.hpp"
#include "image_button.hpp"
#include "CommonDefinitions.hpp"


/**
  *   @class Stats
  *   @brief Class which displays air combat statistics to user
  */

class Stats
{
  public:
    /**
      *   @brief Constructor for Stats
      *   @param window RenderWindow reference
      */
    Stats(sf::RenderWindow &window);

    /**
      *   @brief Update Stats until user exits
      */
    void update();

    /**
      *   @brief Click action for menu Button
      *   @details Return to MainMenu
      */
    void menu_action();

    /**
      *   @brief Get ExitStatus
      *   @return Returns exit_status
      *   @remark Inteded to be called from main.cpp after Stats returns
      */
    int getExitStatus();


  private:
    /**
      *   @brief Create all Buttons needed in Stats
      */
    void CreateButtons();

    /**
      *   @brief Draw all Buttons and text objects to the window
      */
    void DrawWindow();

    /**
      *   @brief Exit Stats and whole air combat game
      *   @details Closes window, sets correct exit_status and returns
      */
    void Exit();

    /**
      *   @brief Handle sfml Mouse press events
      *   @param event Mouse Press Event
      */
    void HandleMousePress(sf::Event &event);

    /**
      *   @brief Handle sfml Mouse move events
      *   @param event Mouse Move Event
      */
    void HandleMouseMove(sf::Event &event);


    /*  Variables */
    sf::RenderWindow &window;
    std::vector<std::shared_ptr<Button>> buttons;
    int exit_status;
    bool active = true;


};
