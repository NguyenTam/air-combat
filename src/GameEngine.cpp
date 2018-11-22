#include "Entity.hpp"
#include "GameEngine.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <math.h>
#include <cstdlib>
#include <sstream>
const float GameEngine::METERS_PER_PIXEL = 60.f;
const float GameEngine::PIXELS_PER_METER = 1/METERS_PER_PIXEL;
const sf::Time GameEngine::TIME_PER_FRAME = sf::seconds(1.f/FPS);
const float GameEngine::PLAYER_SPEED = 100.f;
const float GameEngine::PLAYER_ROTATION_DEGREE = 5.f;

GameEngine::GameEngine() : gameFont()
{
  renderWindow.create(sf::VideoMode(WIDTH,HEIGHT), "Air Combat 1", sf::Style::Titlebar | sf::Style::Close);
  isMovingUp = isMovingDown = isMovingLeft = isMovingRight = isRotatingClockWise = isRotatingCounterClockWise = false;

    try
    {     
      gameEngineLogger = spdlog::basic_logger_mt("basic_logger","../data/game_engine_log.txt");

      if(!playerTexture.loadFromFile("../data/img/plane.png"))
      {
        isGameEngineReady = false;
        return;    
      }
      else {
        std::cout << "Success" << std::endl;
        playerSprite.setTexture(playerTexture);
        playerSprite.setPosition(100.f,100.f);
        
        gameFont.loadFromFile("../data/fonts/Sansation.ttf");
        gameInfo.setFont(gameFont);
        gameInfo.setPosition(10.f,10.f);
        gameInfo.setCharacterSize(10);        
        
        isGameEngineReady = true;
      }
    }
    catch(const spdlog::spdlog_ex &ex)
    {
      std::cout << "Log init failed!" << ex.what() << std::endl;
      isGameEngineReady = false;
    }
}

void GameEngine::run()
{
  sf::Clock clock;
  sf::Time lastUpdateTime = sf::Time::Zero;

  while(renderWindow.isOpen())
  {
    sf::Time elapsedTime = clock.restart();
    lastUpdateTime += elapsedTime;
    
    // Time to handle events and update
    while(lastUpdateTime > TIME_PER_FRAME)      
    {
      lastUpdateTime -= TIME_PER_FRAME;
      // Handle events
      processEvents();
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
        handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        renderWindow.close();
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

void GameEngine::update(sf::Time elapsedTime)
{
  sf::Vector2f moveTo(0.f,0.f);
  float rotated = 0.f;
  if(isMovingUp)
    moveTo.y -= PLAYER_SPEED;
  if(isMovingDown)
    moveTo.y += PLAYER_SPEED;
  if(isMovingLeft)
    moveTo.x -= PLAYER_SPEED;
  if(isMovingRight)
    moveTo.x += PLAYER_SPEED;
  if(isRotatingClockWise)
    rotated += PLAYER_ROTATION_DEGREE;
  if(isRotatingCounterClockWise)
    rotated -= PLAYER_ROTATION_DEGREE;

  std::cout << "Speed:" << moveTo.x << ", " << moveTo.y << std::endl;
  std::cout << "Elapsed time:" << elapsedTime.asSeconds() << std::endl;
  playerSprite.move(moveTo * elapsedTime.asSeconds());
  playerSprite.rotate(rotated);  
}

void GameEngine::updateGameInfo()
{
  std::ostringstream convert;
  convert << rand() % 10000;
  gameInfo.setString("Entities Left: " + convert.str() + "\n" + "AAAAAAAAA");
}

void GameEngine::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
  switch(key)
  {
    case sf::Keyboard::W:
      isMovingUp = isPressed;
      std::cout << "Up" << std::endl;
      break;
    case sf::Keyboard::S:
      isMovingDown = isPressed;
      std::cout << "Down" << std::endl;
      break;
    case sf::Keyboard::A:
      isMovingLeft = isPressed;
      std::cout << "Left" << std::endl;
      break;
    case sf::Keyboard::D:
      isMovingRight = isPressed;
      std::cout << "Right" << std::endl;
      break;
    case sf::Keyboard::Z:
      isRotatingCounterClockWise = isPressed;
      std::cout << "Rotate CCW" << std::endl;
      break;
    case sf::Keyboard::X:
      isRotatingClockWise = isPressed;
      std::cout << "Rotate CW" << std::endl;
      break;
    default:
      gameEngineLogger->info("invalid input");
      std::cout << "Invalid input" << std::endl;
      break;
   }
}

/*
int main()
{  
  try
  {
    auto logger = spdlog::basic_logger_mt("basic_logger", "../data/game-log.txt");

    logger->info("Setting up window");
    sf::RenderWindow window;
    window.create(sf::VideoMode(WIDTH, HEIGHT), "SFML Moving Entity", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    logger->info("Set up player");

    b2Vec2 gravity(0.f, 9.81f);
    b2World* world(gravity);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.f, 10.f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    
    
    Entity entity(sf::Vector2f(80,40));
    entity.setPos({50,400});
    
    //Main loop
    while(window.isOpen())
    {
      world->Step(1.f/FPS,8,3); // update
      
      sf::Event event;     
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
        entity.moveUp();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
        entity.moveDown();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
        entity.moveLeft();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
        entity.moveRight();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
      {
        entity.rotateClockWise();
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
      {
        entity.rotateCounterClockWise();
      }

      // Event Loop:
      while (window.pollEvent(event))
      {
        switch (event.type)
        {
          case sf::Event::Closed:
            window.close();
            break;
          default:
            //TODO: should something be done here
            break;
        }
      }
      // clear the window with black color
      window.clear(sf::Color::Black);

      // draw something.
      entity.drawTo(window);

      // display current objects
      window.display();
    }
  }
  catch(const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log init failed!" << ex.what() << std::endl;  
  }
}
*/
