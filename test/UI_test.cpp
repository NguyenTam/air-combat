/**
  *   @file UI_test.cpp
  *   @brief Test file for UI class
  */


#include "../src/UI.hpp"




int main ()
{

  sf::RenderWindow window;
  window.create(sf::VideoMode(800, 600), "Air combat", sf::Style::Default);


  UI ui = UI(&window);

  while (ui.getStatus())
  {
    ui.updateUI();
  }





  /*while(window.isOpen())
  {
    sf::Event event;
    while( window.pollEvent(event) )
    {
      if (event.type == sf::Event::Resized)
    {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));

    }

    }
    window.clear();
    window.display();
  }*/


  return 0;
}
