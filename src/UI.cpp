/**
  *   @file UI.cpp
  *   @brief Source file for class UI
  */


#include "UI.hpp"



/*  Class UI  */


/*  Constructor */

UI::UI(sf::RenderWindow *render_window, sf::Color backgroundcolor):
window(render_window), BackgoundColor(backgroundcolor) {}


/*  Return window_status  */

int UI::getStatus ()
{
  return window_status;
}


/*  Update UI based on sf::Events */

void UI::updateUI()
{
  sf::Event event;

  // Poll window events

  while( window->pollEvent(event) )
  {
    switch (event.type)
    {
      case sf::Event::Closed:
        window->close();
        window_status = false;
        break;

      case sf::Event::KeyPressed:
        HandleKeyPress(event);
        break;

      case sf::Event::MouseMoved:
        HandleMouseMove(event);
        break;

      case sf::Event::MouseButtonPressed:
        HandleMousePress(event);
        break;

      case sf::Event::Resized:
        HandleResize(event);
        break;

      default:
        std::cout << "Other sf::Event" << std::endl;
    }

  }

  // Clear and display window
  window->clear(sf::Color(BackgoundColor));
  DrawUI();
  window->display();

}


/* Handle window resizing */

void UI::HandleResize(sf::Event event)
 {
   // Reset view
   sf::FloatRect new_screen = sf::FloatRect(0, 0, event.size.width, event.size.height);
   window->setView(sf::View(new_screen));

 }
