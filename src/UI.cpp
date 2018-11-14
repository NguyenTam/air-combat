/**
  *   @file UI.cpp
  *   @brief Source file for class UI
  */


#include "UI.hpp"


// Assign the class variable to match the amount of buttons
int UI::MainMenuButtons = 4;



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
     UpdateActiveButton(BUTTON_PREV);
   }
   else if (event.key.code == sf::Keyboard::Down)
   {
     UpdateActiveButton(BUTTON_NEXT);
   }
   else if (event.key.code == sf::Keyboard::Tab)
   {
     UpdateActiveButton(BUTTON_NEXT);
   }
   else if (event.key.code == sf::Keyboard::Space)
   {
     UpdateActiveButton(BUTTON_PREV);
   }
   else if (event.key.code == sf::Keyboard::Return)
   {
     // Somehow it won't compile with Enter (Return is should be deprecated)
     ClickCurrentButton();
   }

 }

 void UI::HandleMouseMove(sf::Event event)
 {
   float x = (float) event.mouseMove.x;
   float y = (float) event.mouseMove.y;

   for (auto it = buttons.begin(); it != buttons.end(); it++)
   {
     if ( (*it)->tryActivate(x, y) )
     {
       // Button was activated, reset current_button
       current_button = 0;
     }
   }
 }


/*  Check if some button is pressed */

 void UI::HandleMousePress(sf::Event event)
 {
   if (event.mouseButton.button == sf::Mouse::Left)
   {
     float x = (float) event.mouseButton.x;
     float y = (float) event.mouseButton.y;
     for (auto it = buttons.begin(); it != buttons.end(); it++)
     {
       // Check if clicked
       (*it)->checkClicked(x, y);

     }
   }

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
   }

   else if ( (action == BUTTON_PREV) && (current_button > 1) )
   {
     current_button --;
   }
   // Activate the correct button
   ActivateCurrentButton();

 }


/*  Create main menu */

void UI::CreateMainMenu()
{
  // Create Buttons
  // First create the button with longest text and match other widths to it
  std::shared_ptr<Button> button1 = std::make_shared<Button>("Start Game", sf::Color::Blue);
  button1->setPosition(100, 100);
  buttons.push_back(button1);
  unsigned width = button1->getWidth();
  unsigned height = button1->getHeight();
  std::shared_ptr<Button> button2 = std::make_shared<Button>("Editor",
                                    sf::Color::Blue, width, height);
  std::shared_ptr<Button> button3 = std::make_shared<Button>("Settings",
                                    sf::Color::Blue, width, height);
  std::shared_ptr<Button> button4 = std::make_shared<Button>("Statistics",
                                    sf::Color::Blue, width, height);
  button2->setPosition(100, 200);
  buttons.push_back(button2);
  button3->setPosition(100, 300);
  buttons.push_back(button3);
  button4->setPosition(100, 400);
  buttons.push_back(button4);

  // Set click_actions IMPORTANT
  button1->SetClickFunction(std::bind(&UI::Test1, this));
  button2->SetClickFunction(std::bind(&UI::Test2, this));
  button3->SetClickFunction(std::bind(&UI::Test3, this));
  button4->SetClickFunction(std::bind(&UI::Test4, this));

  // Set active colors
  button1->setActiveColor(sf::Color(sf::Color::Yellow));
  button2->setActiveColor(sf::Color(sf::Color::Yellow));
  button3->setActiveColor(sf::Color(sf::Color::Yellow));
  button4->setActiveColor(sf::Color(sf::Color::Yellow));



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


void UI::ActivateCurrentButton()
{
  int i = 1;
  for (auto it = buttons.begin(); it != buttons.end(); it++, i++)
  {
    if (i == current_button)
    {
      (*it)->activate(true);
    }
    else
    {
      (*it)->activate(false);
    }
  }
}

void UI::ClickCurrentButton()
{
  int i=1;
  for (auto it = buttons.begin(); it != buttons.end(); it++, i++)
  {
    if (i == current_button)
    {
      (*it)->clickAction();
      break;
    }
  }
}
