#include "../src/ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(640, 480), "Resources");
  window.setFramerateLimit(20);

  // Try to load resources
  ResourceManager textures;

  // Access resources
  sf::Sprite blueantiaircraft(textures.get(Textures::BlueAntiAircraft));
  blueantiaircraft.setPosition(100.f,100.f);
  sf::Sprite blueairplane(textures.get(Textures::BlueAirplane));
  blueairplane.setPosition(200.f, 200.f);

  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::KeyPressed || event.type == sf::Event::Closed)
	    return 0;
	}

      window.clear();
      window.draw(blueantiaircraft);
      window.draw(blueairplane);
      window.display();
    }
}

