#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include "Entity.h"

int main()
{
  sf::RenderWindow window;
  window.create(sf::VideoMode(800, 600), "SFML Moving Entity", sf::Style::Titlebar | sf::Style::Close);
  window.setKeyRepeatEnabled(true);

  Entity entity({40,40});
  entity.setPos({50,400});

  //Main loop
  while(window.isOpen())
  {
    sf::Event event;

    const float moveSpeed = 0.2;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      entity.move({0,-moveSpeed});
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      entity.move({0, moveSpeed});
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      entity.move({-moveSpeed, 0});
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      entity.move({moveSpeed, 0});
    }

    // Event Loop:
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          window.close();
      }
    }

    window.clear();
    entity.drawTo(window);
    window.display();
  }
}
