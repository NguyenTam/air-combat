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
  std::shared_ptr<Button> level = std::make_shared<Button> ("Level", ButtonColor, button_width, height);
  level->setPosition(width + 3 * button_dist + 2 * button_width, 0);
  std::shared_ptr<Button> time_button = std::make_shared<Button> ("Time", ButtonColor, button_width, height);
  time_button->setPosition(width + 4 * button_dist + 3 * button_width, 0);

  // Set Button style
  menu->setActiveColor(ButtonActiveColor);
  name->setCheckable(true);
  name->setActiveColor(ButtonActiveColor);
  score->setCheckable(true);
  score->setActiveColor(ButtonActiveColor);
  time_button->setCheckable(true);
  time_button->setActiveColor(ButtonActiveColor);
  time_button->setChecked();
  level->setActiveColor(ButtonActiveColor);
  level->setCheckable(true);

  // Set click functions
  menu->setClickFunction(std::bind(&Stats::menu_action, this));
  name->setClickFunction(std::bind(&Stats::sortByName, this));
  score->setClickFunction(std::bind(&Stats::sortByScore, this));
  time_button->setClickFunction(std::bind(&Stats::sortByTime, this));
  level->setClickFunction(std::bind(&Stats::sortByLevel, this));

  // Add Buttons to the container
  buttons.push_back(menu);
  buttons.push_back(name);
  buttons.push_back(score);
  buttons.push_back(level);
  buttons.push_back(time_button);

  // Create the views
  ui_view = window.getDefaultView();
  stats_view = sf::View();
  stats_view.setSize(Game::WIDTH - width - button_dist, Game::HEIGHT - height - button_dist);
  stats_view.setCenter(stats_view.getSize().x / 2, stats_view.getSize().y / 2);
  stats_view.setViewport(sf::FloatRect((width + button_dist) / Game::WIDTH, height / Game::HEIGHT, stats_view.getSize().x / Game::WIDTH, stats_view.getSize().y / Game::HEIGHT));
}

/*  Exit to MainMenu */
void Stats::menu_action()
{
  // Set correct exit_status
  exit_status = ExitStatus::MAINMENU;
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

        case sf::Event::KeyPressed:
          HandleKeyPress(event);
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
  for (auto &button : buttons) {
    window.draw(*button);
  }

  // Draw stats texts
  window.setView(stats_view);
  for (auto &text : texts)
  {
    window.draw(*std::get<0>(text));
    window.draw(*std::get<1>(text));
    window.draw(*std::get<2>(text));
    window.draw(*std::get<3>(text));
  }
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
    for (auto &button : buttons) {
      if (button->checkClicked(x, y)) {
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
  int i = 0;
  for (auto &button : buttons) {
    if (button->tryActivate(x, y))
    {
      // Deactivate old Button
      if (current_button != i)
      {
        ActivateCurrentButton(false);
      }
      // Update current_button
      current_button = i;
      break;
    }
    i++;

  }
}

/*  Handle KeyPress Events */
void Stats::HandleKeyPress(sf::Event &event)
{
  if (event.key.code == sf::Keyboard::Up)
  {
    ViewUp();
  }
  else if (event.key.code == sf::Keyboard::Down)
  {
    ViewDown();
  }
  else if (event.key.code == sf::Keyboard::Tab)
  {
    // deactivate old current_button
    ActivateCurrentButton(false);
    // activate new current_button
    SwitchCurrentButton();
    ActivateCurrentButton(true);
  }
  else if (event.key.code == sf::Keyboard::Return)
  {
    // click current_button
    ClickCurrentButton();
  }
  else if (event.key.code == sf::Keyboard::Escape)
  {
    // Return to main menu
    menu_action();
  }
}

/*  Sort Stats by name */
void Stats::sortByName()
{
  // Uncheck other Buttons
  for (const auto &button : buttons) {
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
  for (const auto &button : buttons) {
    if (button->getText().getString() != "Time")
    {
      button->setUnchecked();
    }
  }
  // Just parse texts again from the file, they are in time
  ParseStats();
}

/*  Sort Stats by score */
void Stats::sortByScore()
{
  // Uncheck other Buttons
  for (const auto &button : buttons) {
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

/*  Sort texts by level name */
void Stats::sortByLevel()
{
  // Uncheck other Buttons
  for (const auto &button : buttons) {
    if (button->getText().getString() != "Level")
    {
      button->setUnchecked();
    }
  }
  // Sort texts
  std::sort(texts.begin(), texts.end(), [] (auto &tuple1, auto &tuple2) {
     //return std::get<3>(tuple1)->getString() < std::get<3>(tuple2)->getString();
    if ( std::get<2>(tuple1)->getString() == std::get<2>(tuple2)->getString())
    {
      // Sort by score (same names)
      try {
        return std::stoi(std::get<1>(tuple1)->getString().toAnsiString()) > std::stoi(std::get<1>(tuple2)->getString().toAnsiString());
      } catch (std::invalid_argument) {
        return true;
      }
    }
    else return std::get<2>(tuple1)->getString() < std::get<2>(tuple2)->getString();});

    // Update text positions
    UpdateTextPositions();
}

/*  Add item to texts */
void Stats::CreateText(std::string name, std::string score, std::string level, std::string time_str)
{

  texts.push_front(std::make_tuple(std::make_unique<sf::Text>(name, font, 14), std::make_unique<sf::Text>(score, font, 14),
              std::make_unique<sf::Text>(level, font, 14), std::make_unique<sf::Text>(time_str, font, 14)));
  // Set correct positions for the texts
  auto &new_entry = texts.front();
  std::get<0>(new_entry)->setPosition(button_dist, button_dist + 40 * (texts.size() - 1));
  std::get<0>(new_entry)->setColor(sf::Color::Red);
  std::get<1>(new_entry)->setPosition(button_dist * 2 + button_width, button_dist + 40 * (texts.size() - 1));
  std::get<1>(new_entry)->setColor(sf::Color::Red);
  std::get<2>(new_entry)->setPosition(button_dist * 3 + button_width * 2, button_dist + 40 * (texts.size() - 1));
  std::get<2>(new_entry)->setColor(sf::Color::Red);
  std::get<3>(new_entry)->setPosition(button_dist * 4 + button_width * 3, button_dist + 40 * (texts.size() - 1));
  std::get<3>(new_entry)->setColor(sf::Color::Red);
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
    std::get<3>(text)->setPosition(button_dist * 4 + button_width * 3, button_dist + 40 * i);
    i++;
  }
}

/*  Create stats and stats window */
void Stats::createStats()
{
  // Set correct window title
  window.setTitle("Stats");
  // Parse stats
  ParseStats();
}

/*  Move stats_view up */
void Stats::ViewUp()
{
  if (current_view > 1)
  {
    // Change current_view and update view center
    current_view --;
    stats_view.setCenter(stats_view.getSize().x / 2, stats_view.getSize().y / 2 + (current_view -1) * (stats_view.getSize().y));
  }
}

/*  Move stats_view down */
void Stats::ViewDown()
{
  // Change current_view and update view center
  current_view ++;
  stats_view.setCenter(stats_view.getSize().x / 2, stats_view.getSize().y / 2 + (current_view -1) * (stats_view.getSize().y));
}

/*  Parse log file and create stats */
void Stats::ParseStats()
{
  // open ../data/misc/stats.txt
  std::ifstream file(Paths::Paths[Paths::PATHS::stats_log]);
  if (file.is_open())
  {
    // Clear old entries
    ClearTexts();
    std::string line;
    std::string time_str, name, score, level;

    while(getline(file, line))
    {
      // Read all lines and convert to string stream. Then split content to split_str
      std::istringstream temp_stream(line);
      std::string split_str;
      int i = 0;
      while(getline(temp_stream, split_str, '['))
      {
        try
        {
          std::size_t index = split_str.find(']');
          if (index != std::string::npos)
          {
            split_str.erase(index);

            // Add str to specific string
            // Format should be : time Stats info name score level
            switch (i)
            {
              case 0:
                time_str = split_str;
                break;
              case 3:
                name = split_str;
                break;
              case 4:
                score = split_str;
                break;
              case 5:
                level = split_str;
              default:
                break;
            }
            i++;
          }


        } catch (std::exception &e)
        {
          // Fail, return
          return;
        }
      }
      if (i == 6 )
      {
        // ok, create new Text
        CreateText(name, score, level, time_str);
        // Update positions to match timestamps (newer first)
        UpdateTextPositions();
      } else {
        return;
      }
    }
  }

}

/*  Clear texts */
void Stats::ClearTexts()
{
  if (! texts.empty())
  {
    texts.clear();
  }
}

/*  Activate / deactivate current_button */
void Stats::ActivateCurrentButton(bool activate)
{
  // Check current_button value is ok
  if ((current_button > -1) && (current_button < static_cast<int>(buttons.size())))
  {
    buttons[current_button]->activate(activate);
  }
}

/*  Switch current_button value */
void Stats::SwitchCurrentButton()
{
  if (current_button <= 0) current_button_dir = true;
  else if (current_button >= static_cast<int>(buttons.size()) - 1)  current_button_dir = false;

  // current_button_dir == true -> right, otherwise left
  if (current_button_dir) current_button++;
  else current_button--;
}

/*  Click current_button */
void Stats::ClickCurrentButton()
{
  // Check current_button value is ok
  if ((current_button > -1) && (current_button < static_cast<int>(buttons.size())))
  {
    buttons[current_button]->clickAction();
  }
}

/*  Init Stats */
void Stats::init()
{
  // Reactivate
  active = true;
  // Init view and current_button and then draw it
  current_view = 1;
  current_button = 0;
  stats_view.setCenter(stats_view.getSize().x / 2, stats_view.getSize().y / 2);

}
