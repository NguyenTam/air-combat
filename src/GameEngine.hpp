/**
 * @file GameEngine.hpp
 * @brief Header for GameEngine class
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "ResourceManager.hpp"
#include "TextInput.hpp"

/**
  *   @class GameEngine
  *   @brief Integrates World and user input
  *   @details This is the class responsible to update the base game based on user
  *   inputs and AI
  */

class GameEngine : private sf::NonCopyable
{
 public:

  /**
   * @brief Construct a GameEngine object.
   */
  GameEngine(sf::RenderWindow &);
  /**
   * @brief Run game engine.
   */
  void run(std::string &level_file);

  static const int FPS = 60; /**< Frames Per Second.*/
  static const float METERS_PER_PIXEL; /**< To convert from pixels to meters.*/
  static const float PIXELS_PER_METER; /**< To convert from meters to pixels.*/
  static const sf::Time TIME_PER_FRAME; /**< Time Per Frame, e.g. Seconds Per Frame.*/
  static const float PLAYER_SPEED; /**< Player movement speed per input. */
  static const float PLAYER_ROTATION_DEGREE; /**< Player rotation degree.*/

  /**
    *   @brief Set gameMode
    *   @param gameMode true -> single_player, false -> multiplayer
    */
  void setGameMode(Game::GameMode gameMode);

 private:
  /**
   *@brief Process all events and inputs from the user.
   */
  void processEvents();
  /**
   * @brief Update the Box2d world.
   * @param elapsedTime Box2d world after .
   * @see updateGameInfo()
   */
  void update(sf::Time elapsedTime);
  /**
   *@brief Update game or Box2d world information.
   */
  void updateGameInfo();
  /**
   * @brief Clear current view and display updates.
   * @see update(), updateGameInfo()
   */
  void render();
  /**
   * @brief Handle player input.
   * @see processEvents()
   */


   /**
    *   @brief Special handler which processes events when game is over
    *   @param event sf::Event
    *   @param level_path Current level path from main.cpp
    *   @return Returns true if the game should return to main menu
    */
   bool gameOverHandler(sf::Event &event, std::string &level_path);

   /**
    *   @brief Create window for game over
    *   @param result GameResult @see world.hpp
    *   @details Creates user_input if single_player has ended
    */
   void createGameOver(GameResult result);

   /**
    *   @brief Draw window when game is over
    *   @remark Normal game level isn't drawn
    */
   void drawGameOver();

   /**
    *   @brief Log game stats when game is over
    *   @param level_path Level path (should be what run gets from main.cpp)
    *   @param user_name name_input content (name user set)
    *   @param score Player score
    *   @remark This should be only called when single_player has ended
    */
   void logStats(std::string level_path, const std::string& user_name, int score);


  void playerMoveUp(int player_number);
  void playerMoveDown(int player_number);
  void playerMoveLeft(int player_number);
  void playerMoveRight(int player_number);
  void playerRotateCounterClockWise(int player_number);
  void playerRotateClockWise(int player_number);
  void playerShoot(int player_number);


  sf::RenderWindow &renderWindow; /**< Display window for game engine */
  ResourceManager resources;
  sf::Texture playerTexture; /**< Player texture like aircraft image */
  sf::Sprite playerSprite; /**< Player object with texture.*/
  sf::Font gameFont; /**< Game font type and size*/
  sf::Text gameInfo; /**< To write game info on screen.*/

  bool isGameEngineReady; /**< Is the game ended*/
  World world;

  bool GameOver; /**< Game over -> show TextInput */
  Game::GameMode gameMode;
  TextInput name_input; /**< Used to get user name when single player game is over */
  sf::Text game_over_text;
  sf::Text name_input_info;
  sf::Clock score_clock;
  int score = 0;
};
