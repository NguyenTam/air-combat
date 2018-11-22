#pragma once
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
class GameEngine : private sf::NonCopyable
{
 public:
  GameEngine();
  void run();

  static const int WIDTH = 800;
  static const int HEIGHT = 600;
  static const int FPS = 60;
  static const float METERS_PER_PIXEL;
  static const float PIXELS_PER_METER;
  static const sf::Time TIME_PER_FRAME;
  static const float PLAYER_SPEED;
  static const float PLAYER_ROTATION_DEGREE;
  
 private:
  void processEvents();
  void update(sf::Time elapsedTime);
  void updateGameInfo();
  void render();
  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

  sf::RenderWindow renderWindow;
  sf::Texture playerTexture;
  sf::Sprite playerSprite;
  sf::Font gameFont;
  sf::Text gameInfo;
  bool isMovingUp;
  bool isMovingDown;
  bool isMovingLeft;
  bool isMovingRight;
  bool isRotatingClockWise;
  bool isRotatingCounterClockWise;

  bool isGameEngineReady;
  std::shared_ptr<spdlog::logger> gameEngineLogger;
};
