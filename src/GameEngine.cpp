/**
  *   @file GameEngine.cpp
  *   @brief Contains class GameEngine source
  */
#include "GameEngine.hpp"
#include "CommonDefinitions.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "World.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <math.h>
#include <sstream>
#include <sstream>


/* Initialize members*/
const float GameEngine::METERS_PER_PIXEL = 60.f;
const float GameEngine::PIXELS_PER_METER = 1/METERS_PER_PIXEL;
const sf::Time GameEngine::TIME_PER_FRAME = sf::seconds(1.f/FPS);
const float GameEngine::PLAYER_SPEED = 100.f;
const float GameEngine::PLAYER_ROTATION_DEGREE = 5.f;

GameEngine::GameEngine(sf::RenderWindow &rw)
    : renderWindow(rw), world(rw, resources) {

        playerSprite.setTexture(resources.get(Textures::ID::BlueAirplane_alpha));
        playerSprite.setPosition(100.f,100.f);

        gameFont.loadFromFile("../data/fonts/Sansation.ttf");
        gameInfo.setFont(gameFont);
        gameInfo.setPosition(10.f,10.f);
        gameInfo.setCharacterSize(10);

        isGameEngineReady = true;
        GameOver = false;
}


/**
 * Handle inputs and draw textures to the screen.
 * This function passes constant TIME_PER_FRAME to update function to achieve fixed time steps.
 * Otherwise the game can be laggy and players can pass through a wall + easier to debug.
 */
void GameEngine::run(std::string &level_file)
{
  world.clear_all();

  world.read_level(level_file, gameMode);

  sf::Time lastUpdateTime = sf::Time::Zero;
  sf::Clock clock;
  score_clock = sf::Clock();
  while(renderWindow.isOpen())
  {
    /*restart function returns elapsed time and reset the clock to zero to get elapsed time of next iteration.*/
    sf::Time elapsedTime = clock.restart();
    lastUpdateTime += elapsedTime;

    /* Time to handle events, update world and display. */
    while(lastUpdateTime > TIME_PER_FRAME)
    {
      lastUpdateTime -= TIME_PER_FRAME;
      // Handle events
      sf::Event event{};
      while(renderWindow.pollEvent(event))
      {
        if (GameOver) {
          // Use special event handler when game is over
          if (gameOverHandler(event, level_file))
          {
            // Return to MainMenu
            return;
          }
        }

        if(event.type == sf::Event::KeyPressed)
        {
          if(event.key.code == sf::Keyboard::Escape)
          {
            return;
          }
        }
      }
      update(TIME_PER_FRAME);
      render();
    }

  }
}

void GameEngine::render()
{
  renderWindow.clear(sf::Color(150,200,255));
  if (GameOver) {
    // Draw only gameover screen
    drawGameOver();
  }
  else {
    // Draw only normal game view
    GameResult result = world.update(gameMode);
    if (result != GameResult::UnFinished) {
      // Game over
      createGameOver(result);
    }
  }
  updateGameInfo();
  renderWindow.display();
}
void GameEngine::playerMoveUp(int player_number)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  Entity& player_entity = *planes[player_number];
  b2Body* player_body = player_entity.getB2Body();
  b2Vec2 vel1 = player_body->GetLinearVelocity();

  float force = 0;
  if (vel1.y > -Game::PlayerPlane::MAX_VELOCITY) {
    force = -Game::PlayerPlane::MAX_FORCE;
}
  player_body->ApplyForce(b2Vec2(0,Game::PlayerPlane::COEFFICIENT*force), player_body->GetWorldCenter(), true);

}

void GameEngine::playerMoveDown(int player_number)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  Entity& player_entity = *planes[player_number];
  b2Body* player_body = player_entity.getB2Body();
  b2Vec2 vel1 = player_body->GetLinearVelocity();

  float force = 0;
  if (vel1.y < Game::PlayerPlane::MAX_VELOCITY) {
    force = Game::PlayerPlane::MAX_FORCE;
}
  player_body->ApplyForce(b2Vec2(0,Game::PlayerPlane::COEFFICIENT*force), player_body->GetWorldCenter(), true);
}

void GameEngine::playerMoveLeft(int player_number)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  Entity& player_entity = *planes[player_number];
  b2Body* player_body = player_entity.getB2Body();
  b2Vec2 vel1 = player_body->GetLinearVelocity();

  player_entity.faceLeft();
  float force = 0;
  if (vel1.x > -Game::PlayerPlane::MAX_VELOCITY) {
    force = -Game::PlayerPlane::MAX_FORCE;
}
  player_body->ApplyForce(b2Vec2(Game::PlayerPlane::COEFFICIENT*force,0), player_body->GetWorldCenter(), true);
}

void GameEngine::playerMoveRight(int player_number)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  Entity& player_entity = *planes[player_number];
  b2Body* player_body = player_entity.getB2Body();
  b2Vec2 vel1 = player_body->GetLinearVelocity();

  player_entity.faceRight();
  float force = 0;
  //player1_body.SetAngularVelocity(0);
  if (vel1.x < Game::PlayerPlane::MAX_VELOCITY) {
    force = Game::PlayerPlane::MAX_FORCE;
}
  player_body->ApplyForce(b2Vec2(Game::PlayerPlane::COEFFICIENT*force,0), player_body->GetWorldCenter(), true);
}

void GameEngine::playerRotateCounterClockWise(int player_number)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  Entity& player_entity = *planes[player_number];
  b2Body* player_body = player_entity.getB2Body();

  // rotate world player_planes[0] up
  if (player_body->GetAngularVelocity() > 0) { player_body->SetAngularVelocity(0);
}
  if (player_body->GetAngularVelocity() > - Game::PlayerPlane::MAX_ANGULAR_VELOCITY) {
    player_body->ApplyTorque((Game::PlayerPlane::MAX_ANGULAR_VELOCITY + player_body->GetAngularVelocity()) * (-Game::PlayerPlane::TORQUE), true);
  }
}

void GameEngine::playerRotateClockWise(int player_number)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  Entity& player_entity = *planes[player_number];
  b2Body* player_body = player_entity.getB2Body();

  if (player_body->GetAngularVelocity() < 0) { player_body->SetAngularVelocity(0);
}
  if (player_body->GetAngularVelocity() < Game::PlayerPlane::MAX_ANGULAR_VELOCITY) {
    player_body->ApplyTorque((Game::PlayerPlane::MAX_ANGULAR_VELOCITY - player_body->GetAngularVelocity()) * Game::PlayerPlane::TORQUE, true);
  }
}

void GameEngine::playerShoot(int player_number)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  Entity& player_entity = *planes[player_number];
  b2Body* player_body = player_entity.getB2Body();

  if (player_entity.getFacing()) {
    // facing right, shoot right
    sf::Vector2f vec(cos(player_body->GetAngle()), sin(player_body->GetAngle()));
    player_entity.shoot(vec, resources);
  }
  else {
    // facing left, shoot left
    sf::Vector2f vec(- cos(player_body->GetAngle()), - sin(player_body->GetAngle()));
    player_entity.shoot(vec, resources);
  }

}


/* Sum all inputs (movements and rotations) and set new position and orientation in two function call: move and rotate. */
void GameEngine::update(sf::Time  /*elapsedTime*/)
{
  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  if (!planes.empty()) {
    Entity& player1_entity = *planes[0];
    b2Body* player1_body = player1_entity.getB2Body();
    b2Body* player2_body = nullptr;
    b2Vec2 vel1 = player1_body->GetLinearVelocity();
    bool player2_set = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      playerMoveUp(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      // move world player_planes[0] down
      playerMoveDown(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      // flip world player_planes[0] left
      playerMoveLeft(0);

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      // flip world player_planes[0] right
      playerMoveRight(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
      playerRotateCounterClockWise(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
      playerRotateClockWise(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
      // shoot world player_planes[0]
      playerShoot(0);
    }

    if ((planes.size()==2) && (gameMode == Game::GameMode::Multiplayer)) {
      player2_set = true;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
        // move world player_planes[1] up
        playerMoveUp(1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        // move world player_planes[1] down
        playerMoveDown(1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        // flip world player_planes[1] left
        playerMoveLeft(1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        // flip world player_planes[1] right
        playerMoveRight(1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
        playerRotateCounterClockWise(1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
        playerRotateClockWise(1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        playerShoot(1);
      }
    }

    //set forces to 0
    else {
      float forcey1 = vel1.y * -Game::PlayerPlane::MAX_FORCE;
      float forcex1 = vel1.x * -Game::PlayerPlane::MAX_FORCE;

      player1_body->ApplyForce(b2Vec2(forcex1,forcey1), player1_body->GetWorldCenter(), true);

      if (player2_set && player2_body != nullptr) {
        float forcey2 = vel1.y * -Game::PlayerPlane::MAX_FORCE;
        float forcex2 = vel1.x * -Game::PlayerPlane::MAX_FORCE;

        player2_body->ApplyForce(b2Vec2(forcex2,forcey2), player2_body->GetWorldCenter(), true);

      }
    }
  }

}

void GameEngine::updateGameInfo()
{
  /*Game info to display*/

  std::deque<std::shared_ptr<Entity>> planes = world.get_player_planes();
  std::stringstream display_information;
  if ( !planes.empty() )
  {
    std::shared_ptr<Plane> player_plane  = std::dynamic_pointer_cast<Plane>(planes[0]);
    display_information << "Player 1 | hitpoints: " << player_plane->getHitPoints()
                        << " | killed: " << player_plane->getGrandTotalKill() << "\n";
  }
  if ( planes.size() > 1 )
  {
    std::shared_ptr<Plane> player_plane  = std::dynamic_pointer_cast<Plane>(planes[1]);
    display_information << "Player 2 | hitpoints: " << player_plane->getHitPoints()
                        << " | killed: " << player_plane->getGrandTotalKill() << "\n";
  }
  gameInfo.setString(display_information.str());
  renderWindow.draw(gameInfo);
}

bool GameEngine::gameOverHandler(sf::Event &event, std::string &level_path)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Return) {
      // Exit to main menu
      if (gameMode == Game::GameMode::SinglePlayer) {
        logStats(level_path, name_input.getInputText(), score);
      }
      return true;
    }
  }
  else if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      // Try to activate name_input
      auto x = static_cast<float>(event.mouseButton.x);
      auto y = static_cast<float>(event.mouseButton.y);
      name_input.tryActivate(x, y);
    }
  }
  else if (event.type == sf::Event::TextEntered) {
    // Try to enter text to name_input
    name_input.addChar(event.text.unicode);
  }
  return false;
}

void GameEngine::createGameOver(GameResult result)
{
  //  Clear level
  world.clear_all();

  if (gameMode == Game::GameMode::SinglePlayer) {
    // Single player, create valid name_input
    // Set also info text
    name_input_info = sf::Text("Enter name and press Enter", gameFont, 20);
    name_input = TextInput(Game::WIDTH / 2 - 75, Game::HEIGHT / 2, 150, 30);
    name_input.activate();
  }
  else {
    // Create empty name_input
    name_input = TextInput();
    name_input_info = sf::Text("Press Enter to return Main Menu", gameFont, 20);
  }
  name_input_info.setPosition(Game::WIDTH / 2 - 110, Game::HEIGHT / 2 - 50);
  name_input_info.setFillColor(sf::Color::Black);

  if (result == GameResult::BlueWon) {
    // Blue team won
    game_over_text = sf::Text("Game Over: Blue Team Won", gameFont, 30);
    game_over_text.setPosition(Game::WIDTH / 2 - 200, 100);
    game_over_text.setFillColor(sf::Color::Blue);
  }
  else if (result == GameResult::RedWon){
    // Red team won
    game_over_text = sf::Text("Game Over: Red Team Won", gameFont, 30);
    game_over_text.setPosition(Game::WIDTH / 2 - 200, 100);
    game_over_text.setFillColor(sf::Color::Red);
  }
  else {
    game_over_text = sf::Text("Game Over: Tie", gameFont, 30);
    game_over_text.setPosition(Game::WIDTH / 2 - 200, 100);
    game_over_text.setFillColor(sf::Color::Green);
  }
  // Update score
  score = score_clock.getElapsedTime().asSeconds();
  if (score > 0) {
    // time based score and add world kill based score to it
    // if world score is 0, player lost
    int world_kill_score = world.getScore();
    if (world_kill_score > 0) {
      score = 100000 / score + world_kill_score;
    }
    else { score = 0; // player lost
}

  }
  else { score = 0;
}

  GameOver = true;
}

void GameEngine::drawGameOver()
{
  // Draw game_over_text
  renderWindow.draw(game_over_text);
  // Draw name_input and its info text
  renderWindow.draw(name_input);
  // also call highlightEffect
  name_input.highlightEffect();
  renderWindow.draw(name_input_info);
}

void GameEngine::logStats(std::string level_path, const std::string& user_name, int score)
{
  // Get level name from level_path
  const std::string cmp1 = "../data/level_files/";
  const std::string cmp2 = ".txt";
  if (level_path.size() >= cmp1.size() + cmp2.size())
  {
    // Erase ../data/level_files/
    level_path.erase(0, cmp1.size());
    // Erase .txt
    level_path.erase(level_path.size() - 4);
  }
  // Construct a log message, format: [name] [score] [level]
  std::string log_msg = "[" + user_name + "] [" + std::to_string(score) + "] [" + level_path + "]";

  // Get current time and create a string from it
  std::time_t time_now = std::time(nullptr);
  std::string time_str = std::asctime(std::localtime(&time_now));
  // These kind of format is used because initially spdlog was used (didn't work on older Ubuntu machines)
  std::string message = "[" + time_str.erase(time_str.size() -1) + "] [Stats] [Entry] " + log_msg;

  // Write message to the log
  std::ofstream file;
  file.open(Paths::Paths[Paths::PATHS::stats_log], std::ios_base::app);
  if (file.is_open())
  {
    file << message << std::endl;
  }

}

void GameEngine::setGameMode(Game::GameMode gameMode)
{
  this->gameMode = gameMode;
  // reset GameOver
  GameOver = false;
}
