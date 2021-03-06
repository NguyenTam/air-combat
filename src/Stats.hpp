/**
  *   @file Stats.hpp
  *   @brief Header for class Stats
  */

#pragma once

/*  Includes */
#include <SFML/Window.hpp>
#include <vector>
#include <deque>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <sstream>
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

    /**
      *   @brief Sort texs by name
      */
    void sortByName();

    /**
      *   @brief Sort texts by time
      *   @remark Sorts newer first
      */
    void sortByTime();

    /**
      *   @brief Sort texts by score
      */
    void sortByScore();

    /**
      *   @brief Sort texts by level name
      */
    void sortByLevel();

    /**
      *   @brief Create Stats from log file
      *   @remark This should be called from main.cpp after Stats is activated
      */
    void createStats();

    /**
      *   @brief Init Stats to safe state
      *   @remark Called from main.cpp after user moves to MainMenu
      */
    void init();


  private:
    /**
      *   @brief Create all Buttons needed in Stats and views
      */
    void CreateUI();

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

    /**
      *   @brief Handle sfml KeyPress events
      *   @param event KeyPress Event
      */
    void HandleKeyPress(sf::Event &event);

    /**
      *   @brief Create sf::Text to texts
      *   @param name User name
      *   @param score Game score
      *   @param time_str Timestamp
      *   @param level Level name (no .txt nor path)
      */
    void CreateText(std::string name, std::string score, std::string level, std::string time_str);

    /**
      *   @brief Update Text positions to match vector indexing
      *   @remark This should be called after vector is sorted
      */
    void UpdateTextPositions();

    /**
      *   @brief Move stats_view up
      */
    void ViewUp();

    /**
      *   @brief Move stats_view down
      */
    void ViewDown();

    /**   @details Parse log file from ../data/misc/stats.txt. Creates container
      *   so that newer entries are at the beginning of the deque
      */
    void ParseStats();

    /**
      *   @brief Clear all Texts from texts
      */
    void ClearTexts();

    /**
      *   @brief Activate / deactivate current button
      *   @param activate true -> activate , false -> deactivate
      */
    void ActivateCurrentButton(bool activate);
    /**
      *   @brief Swicth current_button
      */
    void SwitchCurrentButton();

    /**
      *   @brief Click current_button
      */
    void ClickCurrentButton();

    /*  Variables */
    sf::RenderWindow &window;
    std::vector<std::shared_ptr<Button>> buttons;
    std::deque< std::tuple <std::unique_ptr<sf::Text>, std::unique_ptr<sf::Text>, std::unique_ptr<sf::Text>, std::unique_ptr<sf::Text>>> texts;
    int exit_status;
    bool active = true;
    sf::Color ButtonColor;
    sf::Color ButtonActiveColor;
    sf::Color BackgroundColor;
    sf::View ui_view;
    sf::View stats_view;
    float button_width;
    float button_dist;
    sf::Font font;
    int current_view = 1;
    int current_button = 0;
    bool current_button_dir = true; // Tells in which direction current_button is moved (true -> right, false -> left)


};
