/**
  *   @file GameEngine.cpp
  *   @brief Contains class GameEngine source
  */
#include "GameEngine.hpp"
#include "CommonDefinitions.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "World.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include <math.h>

#define MAX_FORCE 50.f
#define MAX_VELOCITY 3.f
#define TORQUE 50.f
#define MAX_ANG_VELOCITY 0.2f

/* Initialize members*/
const float GameEngine::METERS_PER_PIXEL = 60.f;
const float GameEngine::PIXELS_PER_METER = 1/METERS_PER_PIXEL;
const sf::Time GameEngine::TIME_PER_FRAME = sf::seconds(1.f/FPS);
const float GameEngine::PLAYER_SPEED = 100.f;
const float GameEngine::PLAYER_ROTATION_DEGREE = 5.f;

GameEngine::GameEngine(sf::RenderWindow &rw)
    : renderWindow(rw), world(rw, resources) {

  /* Try spdlogger */
    try
    {
      /* Construct spdloggers */
      gameEngineLogger =spdlog::daily_logger_st("async_file_logger", Paths::Paths[Paths::PATHS::logs]+ "game-engine-log");

      /*Try to load texture from file*/

        playerSprite.setTexture(resources.get(Textures::ID::BlueAirplane_alpha));
        playerSprite.setPosition(100.f,100.f);

        gameFont.loadFromFile("../data/fonts/Sansation.ttf");
        gameInfo.setFont(gameFont);
        gameInfo.setPosition(10.f,10.f);
        gameInfo.setCharacterSize(10);

        isGameEngineReady = true;
        GameOver = false;
    }
    /* spdlog constructor threw an exception.*/
    catch(const spdlog::spdlog_ex &ex)
    {
      std::cout << "Log init failed!" << ex.what() << std::endl;
      isGameEngineReady = false;
    }
}

/**
 * Handle inputs and draw textures to the screen.
 * This function passes constant TIME_PER_FRAME to update function to achieve fixed time steps.
 * Otherwise the game can be laggy and players can pass through a wall + easier to debug.
 */
void GameEngine::run(std::string &level_file)
{
  world.clear_all();

  world.read_level(level_file, gameMode);

  sf::Time lastUpdateTime = sf::Time::Zero;
  sf::Clock clock;
  while(renderWindow.isOpen())
  {
    /*restart function returns elapsed time and reset the clock to zero to get elapsed time of next iteration.*/
    sf::Time elapsedTime = clock.restart();
    lastUpdateTime += elapsedTime;

    /* Time to handle events, update world and display. */
    while(lastUpdateTime > TIME_PER_FRAME)
    {
      lastUpdateTime -= TIME_PER_FRAME;
      // Handle events
      sf::Event event{};
      while(renderWindow.pollEvent(event))
      {
        if (GameOver) {
          // Use special event handler when game is over
          if (gameOverHandler(event, level_file))
          {
            // Return to MainMenu
            gameEngineLogger->info("Closing Game Engine");
            return;
          }
        }

        if(event.type == sf::Event::KeyPressed)
        {
          if(event.key.code == sf::Keyboard::Escape)
          {
            gameEngineLogger->info("Closing Game Engine");
            return;
          }
        }
      }
      updateGameInfo();
      update(TIME_PER_FRAME);
    }
    render();
  }
}

void GameEngine::render()
{
  renderWindow.clear(sf::Color(150,200,255));
  //renderWindow.draw(playerSprite);
  //renderWindow.draw(gameInfo);
  if (GameOver) {
    // Draw only gameover screen
    drawGameOver();
  }
  else {
    // Draw only normal game view
    world.update();
  }
  renderWindow.display();
}

/* Sum all inputs (movements and rotations) and set new position and orientation in two function call: move and rotate. */
void GameEngine::update(sf::Time elapsedTime)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  Entity& player1_entity = *planes[0];
  b2Body& player1_body = player1_entity.getB2Body();
  b2Vec2 vel1 = player1_body.GetLinearVelocity();
  bool player2_set = false;
  float max_angl_vel = 0.15f;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    // move world player_planes[0] up
    float force = 0;
    //player1_body.SetAngularVelocity(0);
    if (vel1.y > -MAX_VELOCITY)
      force = -MAX_FORCE;
    player1_body.ApplyForce(b2Vec2(0,force), player1_body.GetWorldCenter(), true);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    // move world player_planes[0] down
    float force = 0;
    //player1_body.SetAngularVelocity(0);
    if (vel1.y < MAX_VELOCITY)
      force = MAX_FORCE;
    player1_body.ApplyForce(b2Vec2(0,force), player1_body.GetWorldCenter(), true);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    // flip world player_planes[0] left
    player1_entity.faceLeft();
    float force = 0;
    //player1_body.SetAngularVelocity(0);
    if (vel1.x > -MAX_VELOCITY)
      force = -MAX_FORCE;
    player1_body.ApplyForce(b2Vec2(force,0), player1_body.GetWorldCenter(), true);

  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    // flip world player_planes[0] right
    player1_entity.faceRight();
    float force = 0;
    //player1_body.SetAngularVelocity(0);
    if (vel1.x < MAX_VELOCITY)
      force = MAX_FORCE;
    player1_body.ApplyForce(b2Vec2(force,0), player1_body.GetWorldCenter(), true);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    // rotate world player_planes[0] up
    if (player1_body.GetAngularVelocity() > 0) player1_body.SetAngularVelocity(0);
    if (player1_body.GetAngularVelocity() > - max_angl_vel) {
      player1_body.ApplyTorque((max_angl_vel + player1_body.GetAngularVelocity()) * (-TORQUE), true);
    }

  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
    // rotate world player_planes[0] down
    if (player1_body.GetAngularVelocity() < 0) player1_body.SetAngularVelocity(0);
    if (player1_body.GetAngularVelocity() < max_angl_vel) {
      player1_body.ApplyTorque((max_angl_vel - player1_body.GetAngularVelocity()) * TORQUE, true);
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
    // shoot world player_planes[0]
    sf::Vector2f vec(cos(player1_body.GetAngle()), sin(player1_body.GetAngle()));
    player1_entity.shoot(vec, resources);
  }

  if (gameMode == Game::GameMode::Multiplayer) {
    player2_set = true;
    Entity& player2_entity = *planes[1];
    b2Body& player2_body = player2_entity.getB2Body();
    b2Vec2 vel2 = player2_body.GetLinearVelocity();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
      // move world player_planes[1] up
      float force = 0;
      if (vel2.y > -MAX_VELOCITY)
        force = -MAX_FORCE;
      player2_body.ApplyForce(b2Vec2(0,force), player2_body.GetWorldCenter(), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
      // move world player_planes[1] down
      float force = 0;
      if (vel2.y < MAX_VELOCITY)
        force = MAX_FORCE;
      player2_body.ApplyForce(b2Vec2(0,force), player2_body.GetWorldCenter(), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
      // flip world player_planes[1] left
      float force = 0;
      player2_entity.faceLeft();
      if (vel2.x > -MAX_VELOCITY)
        force = -MAX_FORCE;
      player2_body.ApplyForce(b2Vec2(force,0), player2_body.GetWorldCenter(), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
      // flip world player_planes[1] right
      float force = 0;
      player2_entity.faceRight();
      if (vel2.x < MAX_VELOCITY)
        force = MAX_FORCE;
      player2_body.ApplyForce(b2Vec2(force,0), player2_body.GetWorldCenter(), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
      // rotate world player_planes[1] up
      if (player2_body.GetAngularVelocity() > 0) player2_body.SetAngularVelocity(0);
      if (player2_body.GetAngularVelocity() > - max_angl_vel) {
        player2_body.ApplyTorque((max_angl_vel + player2_body.GetAngularVelocity()) * (-TORQUE), true);
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
      // rotate world player_planes[1] down
      if (player2_body.GetAngularVelocity() < 0) player2_body.SetAngularVelocity(0);
      if (player2_body.GetAngularVelocity() < max_angl_vel) {
        player2_body.ApplyTorque((max_angl_vel - player2_body.GetAngularVelocity()) * TORQUE, true);
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
      // shoot world player_planes[1]
    }
  }

  //set forces to 0
  else {
    float forcey1 = vel1.y * -MAX_FORCE;
    float forcex1 = vel1.x * -MAX_FORCE;

    player1_body.ApplyForce(b2Vec2(forcex1,forcey1), player1_body.GetWorldCenter(), true);

    if (player2_set) {
      float forcey2 = vel1.y * -MAX_FORCE;
      float forcex2 = vel1.x * -MAX_FORCE;

      player1_body.ApplyForce(b2Vec2(forcex2,forcey2), player1_body.GetWorldCenter(), true);

    }
  }

}

void GameEngine::updateGameInfo()
{
  /*Game info to display*/
  std::ostringstream convert;
  convert << rand() % 10000;
  gameInfo.setString("Entities Left: " + convert.str() + "\n" + "AAAAAAAAA");
}

bool GameEngine::gameOverHandler(sf::Event &event, std::string &level_path)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Return) {
      // Exit to main menu
      if (gameMode == Game::GameMode::SinglePlayer) {
        // TODO real score here
        logStats(level_path, name_input.getInputText(), 100);
      }
      return true;
    }
  }
  else if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      // Try to activate name_input
      auto x = static_cast<float>(event.mouseButton.x);
      auto y = static_cast<float>(event.mouseButton.y);
      name_input.tryActivate(x, y);
    }
  }
  else if (event.type == sf::Event::TextEntered) {
    // Try to enter text to name_input
    name_input.addChar(event.text.unicode);
  }
  return false;
}

void GameEngine::createGameOver(bool blue_won)
{
  //  Clear level
  world.clear_all();

  if (gameMode == Game::GameMode::SinglePlayer) {
    // Single player, create valid name_input
    // Set also info text
    name_input_info = sf::Text("Enter name and press Enter", gameFont, 20);
    name_input = TextInput(Game::WIDTH / 2 - 75, Game::HEIGHT / 2, 150, 30);
    name_input.activate();
  }
  else {
    // Create empty name_input
    name_input = TextInput();
    name_input_info = sf::Text("Press Enter to return Main Menu", gameFont, 20);
  }
  name_input_info.setPosition(Game::WIDTH / 2 - 110, Game::HEIGHT / 2 - 50);
  name_input_info.setColor(sf::Color::Black);

  if (blue_won) {
    // Blue team won
    game_over_text = sf::Text("Game Over: Blue Team Won", gameFont, 30);
    game_over_text.setPosition(Game::WIDTH / 2 - 200, 100);
    game_over_text.setColor(sf::Color::Blue);
  }
  else {
    // Red team won
    game_over_text = sf::Text("Game Over: Red Team Won", gameFont, 30);
    game_over_text.setPosition(Game::WIDTH / 2 - 200, 100);
    game_over_text.setColor(sf::Color::Red);
  }

  GameOver = true;
}

void GameEngine::drawGameOver()
{
  // Draw game_over_text
  renderWindow.draw(game_over_text);
  // Draw name_input and its info text
  renderWindow.draw(name_input);
  // also call highlightEffect
  name_input.highlightEffect();
  renderWindow.draw(name_input_info);
}

void GameEngine::logStats(std::string level_path, std::string user_name, int score)
{
  // Get level name from level_path
  const std::string cmp1 = "../data/level_files/";
  const std::string cmp2 = ".txt";
  if (level_path.size() >= cmp1.size() + cmp2.size())
  {
    // Erase ../data/level_files/
    level_path.erase(0, cmp1.size());
    // Erase .txt
    level_path.erase(level_path.size() - 4);
  }
  // Construct a log message, format: [name] [score] [level]
  std::string log_msg = "[" + user_name + "] [" + std::to_string(score) + "] [" + level_path + "]";

  // Get current time and create a string from it
  std::time_t time_now = std::time(nullptr);
  std::string time_str = std::asctime(std::localtime(&time_now));
  // These kind of format is used because initially spdlog was used (didn't work on older Ubuntu machines)
  std::string message = "[" + time_str.erase(time_str.size() -1) + "] [Stats] [Entry] " + log_msg;

  // Write message to the log
  std::ofstream file;
  file.open(Paths::Paths[Paths::PATHS::stats_log], std::ios_base::app);
  if (file.is_open())
  {
    file << message << std::endl;
  }

}

void GameEngine::setGameMode(Game::GameMode gameMode)
{
  this->gameMode = gameMode;
}
