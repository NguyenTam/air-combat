/**
  *   @file UI.cpp
  *   @brief Source file for class UI
  */


#include "UI.hpp"


// Assign the class variable to match the amount of buttons
int UI::MainMenuButtons = 1;



/*  Class UI  */


/*  Constructor */

UI::UI(sf::RenderWindow *parent_window): window(parent_window)
{
  CreateMainMenu();
}

/*  Return window_status  */

bool UI::getStatus ()
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
  window->clear();
  DrawMenu();
  window->display();

}


 void UI::HandleKeyPress(sf::Event event)
 {

   if (event.key.code == sf::Keyboard::Escape)
   {
     // Close window
     window->close();
     window_status = false;
   }
   else if (event.key.code == sf::Keyboard::Up)
   {
     UpdateActiveButton(BUTTON_NEXT);
   }
   else if (event.key.code == sf::Keyboard::Down)
   {
     UpdateActiveButton(BUTTON_PREV);
   }
   else if (event.key.code == sf::Keyboard::Tab)
   {
     UpdateActiveButton(BUTTON_NEXT);
   }
   else if (event.key.code == sf::Keyboard::Space)
   {
     UpdateActiveButton(BUTTON_PREV);
   }

 }

 void UI::HandleMouseMove(sf::Event event)
 {
   std::cout << "Mouse moved" << std::endl;
 }

 void UI::HandleMousePress(sf::Event event)
 {
   std::cout << "Mouse pressed" << std::endl;
 }

 void UI::HandleResize(sf::Event event)
 {
   // Reset view
   sf::FloatRect new_screen = sf::FloatRect(0, 0, event.size.width, event.size.height);
   window->setView(sf::View(new_screen));

 }

 void UI::UpdateActiveButton(int action)
 {

   if ( (action == BUTTON_NEXT) && (current_button < UI::MainMenuButtons) )
   {

     current_button ++;
     // Activate button
   }


   else if ( (action == BUTTON_PREV) && (current_button > 1) )
   {
     current_button --;
     // Activate button
   }

   else if (action == BUTTON_MOUSE)
   {
     // Try to activate button
   }

 }


/*  Create main menu */

void UI::CreateMainMenu()
{
  // Create Buttons
  std::shared_ptr<Button> button1 = std::make_shared<Button>("Test", sf::Color::Red);
  button1->setPosition(100, 100);
  buttons.push_back(button1);

}


/*  Draw main menu */

void UI::DrawMenu()
{

  for(auto button = buttons.begin(); button != buttons.end(); button++)
  {
    // Draw buttons
    window->draw(**button);
  }

}
