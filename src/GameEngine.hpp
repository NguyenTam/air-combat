/**
 * @file GameEngine.hpp
 * @brief Header for GameEngine class
 */
#pragma once
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include "World.h"
class GameEngine : private sf::NonCopyable
{
 public:

  /**
   * @brief Construct a GameEngine object.
   */
  GameEngine();
  /**
   * @brief Run game engine.
   */
  void run(); 

  static const int WIDTH = 800; /**< Width of VideoMode.*/
  static const int HEIGHT = 600;  /**< Height of VideoMode.*/
  static const int FPS = 60; /**< Frames Per Second.*/
  static const float METERS_PER_PIXEL; /**< To convert from pixels to meters.*/
  static const float PIXELS_PER_METER; /**< To convert from meters to pixels.*/
  static const sf::Time TIME_PER_FRAME; /**< Time Per Frame, e.g. Seconds Per Frame.*/
  static const float PLAYER_SPEED; /**< Player movement speed per input. */
  static const float PLAYER_ROTATION_DEGREE; /**< Player rotation degree.*/
  
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
  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
  
  sf::RenderWindow renderWindow; /**< Display window for game engine */
  sf::Texture playerTexture; /**< Player texture like aircraft image */
  sf::Sprite playerSprite; /**< Player object with texture.*/
  sf::Font gameFont; /**< Game font type and size*/
  sf::Text gameInfo; /**< To write game info on screen.*/
  bool isMovingUp; /**< Is player moving up*/
  bool isMovingDown; /**< Is player moving down*/
  bool isMovingLeft; /**< Is player moving left*/
  bool isMovingRight; /**< Is player moving right*/
  bool isRotatingClockWise; /**< Is player rotating clock wise*/
  bool isRotatingCounterClockWise; /**< Is player rotating counter clock wise*/

  bool isGameEngineReady; /**< Is the game ended*/
  std::shared_ptr<spdlog::logger> gameEngineLogger; /**< Game engine logger. Logs are written to data folder.*/
};
