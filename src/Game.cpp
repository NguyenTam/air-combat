#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include "Entity.hpp"
#include "spdlog/spdlog.h"

int main()
{
  
  try
  {
    //auto logger = spdlog::stdout_logger_mt("basic_logger", "../data/game-log.txt");
    auto logger = spdlog::daily_logger_st("async_file_logger", "../data/game-log.txt");

    logger->info("Setting up window");
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "SFML Moving Entity", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    logger->info("Set up player");
    Entity entity(sf::Vector2f(80,40));
    entity.setPos({50,400});
    
    //Main loop
    while(window.isOpen())
    {
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
