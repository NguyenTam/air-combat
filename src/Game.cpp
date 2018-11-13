#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include "Entity.h"
#include "spdlog/spdlog.h"

int main()
{
  
  try
  {
    auto logger = spdlog::basic_logger_mt("basic_logger", "../data/game-log.txt");

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
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
        entity.moveDown();
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
        entity.moveLeft();
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
        entity.moveRight();
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
      {
        entity.rotateClockWise();
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
      {
        entity.rotateCounterClockWise();
      }
      else
      { //does nothing
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

      window.clear();
      entity.drawTo(window);
      window.display();
    }
  }
  catch(const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log init failed!" << ex.what() << std::endl;  
  }
}
