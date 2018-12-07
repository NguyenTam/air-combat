/**
  *   @file Stats.cpp
  *   @brief Source for class Stats
  */

#include "Stats.hpp"

/*  Class Stats */


/*  Constructor */
Stats::Stats(sf::RenderWindow &window): window(window), ButtonColor(sf::Color(100, 50, 50, 100)), ButtonActiveColor(sf::Color(100, 50, 50)),
BackgroundColor(sf::Color(30, 30, 30, 100))
{
  CreateUI();
  // Create font
  font.loadFromFile("../data/fonts/arial.ttf");
}


/*  Create all Buttons */
void Stats::CreateUI()
{
  // Create Buttons and set positions
  std::shared_ptr<Button> menu = std::make_shared<Button> ("Menu", ButtonColor);
  menu->setPosition(0, 0);
  float width = menu->getWidth();
  float height = 30;
  button_dist = 10;
  button_width = (Game::WIDTH - width) / 4 - 2 * button_dist;
  std::shared_ptr<Button> name = std::make_shared<Button> ("Name", ButtonColor, button_width, height);
  name->setPosition(width + button_dist, 0);
  std::shared_ptr<Button> score = std::make_shared<Button> ("Score", ButtonColor, button_width, height);
  score->setPosition(width + 2 * button_dist + button_width, 0);
  std::shared_ptr<Button> time_button = std::make_shared<Button> ("Time", ButtonColor, button_width, height);
  time_button->setPosition(width + 3 * button_dist + 2 * button_width, 0);

  // Set Button style
  menu->setActiveColor(ButtonActiveColor);
  name->setCheckable(true);
  name->setActiveColor(ButtonActiveColor);
  score->setCheckable(true);
  score->setActiveColor(ButtonActiveColor);
  time_button->setCheckable(true);
  time_button->setActiveColor(ButtonActiveColor);
  time_button->setChecked();

  // Set click functions
  menu->setClickFunction(std::bind(&Stats::menu_action, this));
  name->setClickFunction(std::bind(&Stats::sortByName, this));
  score->setClickFunction(std::bind(&Stats::sortByScore, this));
  time_button->setClickFunction(std::bind(&Stats::sortByTime, this));

  // Add Buttons to the container
  buttons.push_back(menu);
  buttons.push_back(name);
  buttons.push_back(score);
  buttons.push_back(time_button);

  // Create the views
  ui_view = window.getDefaultView();
  stats_view = sf::View();
  stats_view.setSize(Game::WIDTH - width - button_dist, Game::HEIGHT - height);
  stats_view.setCenter(stats_view.getSize().x / 2, stats_view.getSize().y / 2);
  stats_view.setViewport(sf::FloatRect((width + button_dist) / Game::WIDTH, height / Game::HEIGHT, stats_view.getSize().x / Game::WIDTH, stats_view.getSize().y / Game::HEIGHT));
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
    window.clear(BackgroundColor);
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

  // Draw stats texts
  window.setView(stats_view);
  for (auto &text : texts)
  {
    window.draw(*std::get<0>(text));
    window.draw(*std::get<1>(text));
    window.draw(*std::get<2>(text));
  }
  window.draw(test);
  window.setView(ui_view);
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
    (*it)->tryActivate(x, y);
  }
}

/*  Sort Stats by name */
void Stats::sortByName()
{
  // Uncheck other Buttons
  for (auto button : buttons)
  {
    if (button->getText().getString() != "Name")
    {
      button->setUnchecked();
    }
  }
  // Sort texts
  std::sort(texts.begin(), texts.end(), [] (auto &tuple1 , auto &tuple2)
  {
    std::string str1 = std::get<0>(tuple1)->getString();
    std::transform(str1.begin(), str1.end(),str1.begin(), ::toupper);
    std::string str2 = std::get<0>(tuple2)->getString();
    std::transform(str2.begin(), str2.end(),str2.begin(), ::toupper);
    return str1 < str2;
  });
  // Update Text positions
  UpdateTextPositions();
}

/*  Sort Stats by time */
void Stats::sortByTime()
{
  // Uncheck other Buttons
  for (auto button : buttons)
  {
    if (button->getText().getString() != "Time")
    {
      button->setUnchecked();
    }
  }
}

/*  Sort Stats by score */
void Stats::sortByScore()
{
  // Uncheck other Buttons
  for (auto button : buttons)
  {
    if (button->getText().getString() != "Score")
    {
      button->setUnchecked();
    }
  }
  // Sort texts
  std::sort(texts.begin(), texts.end(), [] (auto &tuple1 , auto &tuple2)
  {
    try {
      return std::stoi(std::get<1>(tuple1)->getString().toAnsiString()) > std::stoi(std::get<1>(tuple2)->getString().toAnsiString());
    } catch (std::invalid_argument) {
      return true;
    }
  });
  // Update Text positions
  UpdateTextPositions();
}

/*  Add item to texts */
void Stats::CreateText(std::string name, std::string score, std::string time_str)
{

  texts.push_back(std::make_tuple(std::make_unique<sf::Text>(name, font, 14), std::make_unique<sf::Text>(score, font, 14),
              std::make_unique<sf::Text>(time_str, font, 14)));
  // Set correct positions for the texts
  auto &new_entry = texts.back();
  std::get<0>(new_entry)->setPosition(button_dist, button_dist + 40 * (texts.size() - 1));
  std::get<0>(new_entry)->setColor(sf::Color::Red);
  std::get<1>(new_entry)->setPosition(button_dist * 2 + button_width, button_dist + 40 * (texts.size() - 1));
  std::get<1>(new_entry)->setColor(sf::Color::Red);
  std::get<2>(new_entry)->setPosition(button_dist * 3 + button_width * 2, button_dist + 40 * (texts.size() - 1));
  std::get<2>(new_entry)->setColor(sf::Color::Red);
}

/*  Create Stats */
void Stats::createStats()
{
  test.setColor(sf::Color::Red);
  test.setPosition(0, 0);
  CreateText(std::string("Lauri 1."), std::string("100"), std::string("2018-07-12 13:56:45"));
  CreateText(std::string("AAA"), std::string("50"), std::string("2018-07-13-74"));
  CreateText(std::string("Hello "), std::string("200"), std::string("2018-07-12 14:56:45"));
  CreateText(std::string("dD"), std::string("hhf"), std::string("2018-07-12 14:56:45"));

}

/*  Update Texts positions */
void Stats::UpdateTextPositions()
{
  // Change positions accordingly
  int i = 0;
  for (auto &text : texts)
  {
    std::get<0>(text)->setPosition(button_dist, button_dist + 40 * i);
    std::get<1>(text)->setPosition(button_dist * 2 + button_width, button_dist + 40 * i);
    std::get<2>(text)->setPosition(button_dist * 3 + button_width * 2, button_dist + 40 * i);
    i++;
  }
}
