/**
  *   @file Stats.cpp
  *   @brief Source for class Stats
  */

#include "Stats.hpp"

/*  Class Stats */


/*  Constructor */
Stats::Stats(sf::RenderWindow &window): window(window)
{
  CreateButtons();
}


/*  Create all Buttons */
void Stats::CreateButtons()
{
  // Create Buttons and set positions
  std::shared_ptr<Button> menu = std::make_shared<Button>("Menu", sf::Color::Blue);
  menu->setPosition(0, 0);

  // Set Button style
  menu->setActiveColor(sf::Color(15, 10, 75));

  // Set click functions
  menu->setClickFunction(std::bind(&Stats::menu_action, this));

  // Add Buttons to the container
  buttons.push_back(menu);
}

/*  Exit to MainMenu */
void Stats::menu_action()
{
  // Set correct exit_status
  exit_status = ExitStatus::MAINMENU;
  // Clear all texts TODO
  // set active false
  active = false;
}

/*  Update Eventloop during user is in Stats */
void Stats::update()
{
  while(active)
  {
    sf::Event event;

    // Poll events
    while( window.pollEvent(event) )
    {
      switch (event.type)
      {
        case sf::Event::Closed:
          // Exit whole game
          Exit();

        case sf::Event::MouseButtonPressed:
          HandleMousePress(event);
          break;

        case sf::Event::MouseMoved:
          HandleMouseMove(event);
          break;

        default:
          break;

      }
    }

    // Update and draw the window
    window.clear(sf::Color::White);
    DrawWindow();
    window.display();
  }

}


/*  Draw all Buttons and other objects to the window */
void Stats::DrawWindow()
{
  // Draw all Buttons
  for (auto it = buttons.begin(); it != buttons.end(); it ++)
  {
    window.draw(**it);
  }
}

/*  Exit the game */
void Stats::Exit()
{
  // Close the window
  window.close();
  // Set correct exit_status and set active false
  exit_status = ExitStatus::QUIT;
  active = false;
}

/*  Get exit_status */
int Stats::getExitStatus()
{
  return exit_status;
}

/*  Handle Mouse Press Events */
void Stats::HandleMousePress(sf::Event &event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;

    // Go through all Buttons and try to click those
    for (auto it = buttons.begin(); it != buttons.end(); it++)
    {
      if ((*it)->checkClicked(x, y))
      {
        // Button clicked
        break;
      }
    }
  }

}

/*  Handle Mouse Move Events */
void Stats::HandleMouseMove(sf::Event &event)
{
  float x = event.mouseMove.x;
  float y = event.mouseMove.y;

  // Try to activate Buttons
  for (auto it = buttons.begin(); it != buttons.end(); it++)
  {
    if ((*it)->tryActivate(x, y))
    {
      // Activated Button
      break;
    }
  }
}
