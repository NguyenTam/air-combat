/**
  *   @file Gameengine.cpp
  *   @brief Contains class GameEngine source
  */
#include "Entity.hpp"
#include "GameEngine.hpp"
#include "CommonDefinitions.hpp"
#include "ResourceManager.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <math.h>
#include <cstdlib>
#include <sstream>

/* Initialize members*/
const float GameEngine::METERS_PER_PIXEL = 60.f;
const float GameEngine::PIXELS_PER_METER = 1/METERS_PER_PIXEL;
const sf::Time GameEngine::TIME_PER_FRAME = sf::seconds(1.f/FPS);
const float GameEngine::PLAYER_SPEED = 100.f;
const float GameEngine::PLAYER_ROTATION_DEGREE = 5.f;

GameEngine::GameEngine(sf::RenderWindow & rw) : renderWindow(rw), gameFont()
{
  /* Construct a render window.*/
  //renderWindow.create(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "Air Combat 1", sf::Style::Titlebar | sf::Style::Close);

  renderWindow.setTitle("Air Combat 1");

  /* Try spdlogger */
    try
    {
      /*Construct spdlogger*/
      gameEngineLogger =spdlog::daily_logger_st("async_file_logger", Paths::Paths[Paths::PATHS::logs]+ "game-engine-log");

      /*Try to load texture from file*/
      if(!resources.init())
      {
        isGameEngineReady = false;
        return;
      }
      /*If loading is success, then load font and set game info position on render window*/
      else {
        playerSprite.setTexture(resources.get(Textures::ID::BlueAirplane_alpha));
        playerSprite.setPosition(100.f,100.f);

        gameFont.loadFromFile("../data/fonts/Sansation.ttf");
        gameInfo.setFont(gameFont);
        gameInfo.setPosition(10.f,10.f);
        gameInfo.setCharacterSize(10);

        isGameEngineReady = true;
      }
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
void GameEngine::run()
{

  sf::Clock clock;
  sf::Time lastUpdateTime = sf::Time::Zero;

  /* While render window = game is on.*/
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
      sf::Event event;
      while(renderWindow.pollEvent(event))
      {
        if(event.type == sf::Event::KeyReleased)
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

void GameEngine::processEvents()
{
  sf::Event event;
  while(renderWindow.pollEvent(event))
  {
    switch(event.type)
    {
      case sf::Event::KeyPressed:
        //handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        //handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        // renderWindow.close();
        gameEngineLogger->info("Closing Game Engine");
        break;
      default:
        gameEngineLogger->info("Unspecified Key");
        break;
    }
  }
}

void GameEngine::render()
{
  renderWindow.clear();
  renderWindow.draw(playerSprite);
  renderWindow.draw(gameInfo);
  renderWindow.display();
}

/* Sum all inputs (movements and rotations) and set new position and orientation in two function call: move and rotate. */
void GameEngine::update(sf::Time elapsedTime)
{

  sf::Vector2f moveTo(0.f,0.f);
  float rotated = 0.f;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    moveTo.y -= PLAYER_SPEED;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    moveTo.y += PLAYER_SPEED;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    moveTo.x -= PLAYER_SPEED;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    moveTo.x += PLAYER_SPEED;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
    rotated += PLAYER_ROTATION_DEGREE;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    rotated -= PLAYER_ROTATION_DEGREE;


  playerSprite.move(moveTo * elapsedTime.asSeconds());
  playerSprite.rotate(rotated);
}

void GameEngine::updateGameInfo()
{
  /*Game info to display*/
  std::ostringstream convert;
  convert << rand() % 10000;
  gameInfo.setString("Entities Left: " + convert.str() + "\n" + "AAAAAAAAA");
}
