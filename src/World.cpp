/**
  *   @file World.cpp
  *   @brief Source file for class Ẃorld
  */

#include "World.hpp"

/*  Class World  */

/*  Constructor  */

World::World(sf::RenderWindow &main_window, ResourceManager &_resources) : pworld(), resources(_resources), window(main_window) {}

/*  Parse level .txt file and create world's entities  */

bool World::read_level(std::string& filename, Game::GameMode game_mode) {
	//entity type; x; y; orientation; width; height
	// init score
	score = 0;
	double x, y, width, height;
  	int orientation;
  	std::string type;
	std::ifstream file(filename);
	if (file.is_open()) {
		clear_all();
		bool comments_read = false;
		std::string line;
		while(getline(file,line)) {
			if (! comments_read) {
				if (line.find("*/") != std::string::npos) {
					comments_read = true;
				}
			}
			else {
				std::istringstream temp_stream(line);
				std::string split_str;
				int i = 0;

				while(getline(temp_stream, split_str, ';')) {
					try {
						switch (i) {
						  case 0:
			                type = split_str;
			                break;
			              case 1:
			                x = std::stod(split_str);
			                break;
			              case 2:
			                y = std::stod(split_str);
			                break;
			              case 3:
			                orientation = std::stoi(split_str);
			                break;
			              case 4:
			                width = std::stod(split_str);
			                break;
			              case 5:
			                height = std::stod(split_str);
			                break;
						}
						i++;
					}

					catch (std::exception &e) {
						std::cout << e.what() << std::endl;
						//clear all
						return false;
					}
				}

				if (i != 6) {
					//failed
					clear_all();
					return false;
				}
				else {
					//all ok
					if (type == "InvisibleWall") {
					        b2Body* body = pworld.create_body_static(x, y, width, height, Game::TYPE_ID::invisible_wall);
						std::shared_ptr<Entity> entity = std::make_shared<InvisibleWall>(*pworld.get_world(), body, resources.get(Textures::alphaTextures.at("Ground")), sf::Vector2f(x,y));
						entity->setType(Textures::Ground_alpha); //TODO Id for InvisibleWall
						body->SetUserData(entity.get());
					}
					try {
						Textures::ID id = Textures::alphaTextures.at(type);
						if (x+width < Game::WIDTH)
							create_entity(id, x, y, orientation, width, height, sf::Vector2f(1.0f, 0.0f), game_mode);

					}
					catch (const std::out_of_range& er) {

					}
				}
			}
		}
	}

	return true;
}


/*  Clears the world  */

void World::clear_all() {
	objects.clear();
	player_planes.clear();
	for (b2Body* b = pworld.get_world()->GetBodyList(); b; b = b->GetNext())
		pworld.get_world()->DestroyBody(b);
}

/*  Create entity  */

bool World::create_entity(Textures::ID id, double x, double y, int orientation, double width, double height, sf::Vector2f direct, Game::GameMode game_mode) {
	sf::Texture &tex = resources.get(id);
	sf::Vector2f pos(x,y);
	b2Body* body;
	std::shared_ptr<Entity> entity;

	switch(id) {
		case Textures::BlueAirplane_alpha: {
		        body = pworld.create_body_dynamic(x, y, width, height,1);
			entity = std::make_shared<Plane>(*pworld.get_world(), body, tex, pos, direct, Game::TEAM_ID::blue);
			entity->setType(Textures::BlueAirplane_alpha);
			body->SetUserData(entity.get());
			body->SetGravityScale(0); //gravity 0 for plane
			// add BlueAirplane to player_planes[0] (controlled by player not by AI)
                        if (orientation == 0)
                        {
                          entity->setDirection({-1.f,0});
                          entity->faceLeft();
                        }
			player_planes.push_front((std::move(entity)));
			break;
		}
		case Textures::BlueAntiAircraft_alpha: {
		        body = pworld.create_body_dynamic(x, y, width, height, 1);
			entity = std::make_shared<Artillery>(*pworld.get_world(), body, tex, pos, Game::TEAM_ID::blue);
			entity->setType(Textures::BlueAntiAircraft_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::BlueBase_alpha: {
		        body = pworld.create_body_static(x, y, width, height, Game::TYPE_ID::base);
			entity = std::make_shared<Base>(*pworld.get_world(), body, tex, pos, Game::TEAM_ID::blue);
			entity->setType(Textures::BlueBase_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::BlueHangar_alpha: {
		        body = pworld.create_body_static(x, y, width, height, Game::TYPE_ID::hangar);
			entity = std::make_shared<Hangar>(*pworld.get_world(), body, tex, pos, Game::TEAM_ID::blue);
			entity->setType(Textures::BlueHangar_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::BlueInfantry_alpha: {
		        body = pworld.create_body_dynamic(x, y, width, height, 1000);
			entity = std::make_shared<Infantry>(*pworld.get_world(), body, tex, pos, Game::TEAM_ID::blue);
			entity->setType(Textures::BlueInfantry_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::Ground_alpha: {
		        body = pworld.create_body_static(x, y, width, height, Game::TYPE_ID::ground);
			entity = std::make_shared<Ground>(*pworld.get_world(), body, tex, pos);
			entity->setType(Textures::Ground_alpha);
			entity->setScale(width,height);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::RedAirplane_alpha: {
			if (game_mode == Game::GameMode::SinglePlayer) {
				// add RedAirplanes to the normal container (controlled by AI)
			        body = pworld.create_body_dynamic(x, y, width, height, 1);
				entity = std::make_shared<Plane>(*pworld.get_world(), body, tex, pos, direct, Game::TEAM_ID::red);
				entity->setType(Textures::RedAirplane_alpha);
				body->SetUserData(entity.get());
				body->SetGravityScale(0); //gravity 0 for plane
                                if (orientation == 0)
                                {
                                  entity->setDirection({-1.f,0});
                                  entity->faceLeft();
                                }
				objects.push_back(std::move(entity));
			}
			else {
				// Add RedAirplane to player_planes container
				if (player_planes.size() == 1) {
					if (player_planes[0]->getType() == Textures::ID::BlueAirplane_alpha) {
						// only one RedAirplane is alowed and it needs to be at player_planes[1]
					        body = pworld.create_body_dynamic(x, y, width, height, 1);
						entity = std::make_shared<Plane>(*pworld.get_world(), body, tex, pos, direct, Game::TEAM_ID::red);
						entity->setType(Textures::RedAirplane_alpha);
						body->SetUserData(entity.get());
						body->SetGravityScale(0); //gravity 0 for plane
                                                if (orientation == 0)
                                                {
                                                  entity->setDirection({-1.f,0});
                                                  entity->faceLeft();
                                                }
						player_planes.push_back(std::move(entity));
					}
				}
				else if (player_planes.size() == 0) {

				        body = pworld.create_body_dynamic(x, y, width, height,1 );
					entity = std::make_shared<Plane>(*pworld.get_world(), body, tex, pos, direct, Game::TEAM_ID::red);
					entity->setType(Textures::RedAirplane_alpha);
					body->SetUserData(entity.get());
					body->SetGravityScale(0); //gravity 0 for plane
                                        if (orientation == 0)
                                        {
                                          entity->setDirection({-1.f,0});
                                          entity->faceLeft();
                                        }
					player_planes.push_back(std::move(entity));
				}
			}
			break;
		}
		case Textures::RedAntiAircraft_alpha: {
		        body = pworld.create_body_dynamic(x, y, width, height,1);
			entity = std::make_shared<Artillery>(*pworld.get_world(), body, tex, pos, Game::TEAM_ID::red);
			entity->setType(Textures::RedAntiAircraft_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::RedBase_alpha: {
		        body = pworld.create_body_static(x, y, width, height, Game::TYPE_ID::base);
			entity = std::make_shared<Base>(*pworld.get_world(), body, tex, pos, Game::TEAM_ID::red);
			entity->setType(Textures::RedBase_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::RedHangar_alpha: {
		        body = pworld.create_body_static(x, y, width, height, Game::TYPE_ID::hangar);
			entity = std::make_shared<Hangar>(*pworld.get_world(), body, tex, pos, Game::TEAM_ID::red);
			entity->setType(Textures::RedHangar_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::RedInfantry_alpha: {
		        body = pworld.create_body_dynamic(x, y, width, height, 1000);
			entity = std::make_shared<Infantry>(*pworld.get_world(), body, tex, pos, Game::TEAM_ID::red);
			entity->setType(Textures::RedInfantry_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::Rock_alpha: {
			body = pworld.create_body_static(x, y, width, height, Game::TYPE_ID::rock);
			entity = std::make_shared<Stone>(*pworld.get_world(), body, tex, pos);
			entity->setType(Textures::Rock_alpha);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::Tree_alpha: {
			body = pworld.create_body_static(x, y, width, height, Game::TYPE_ID::tree);
			entity = std::make_shared<Tree>(*pworld.get_world(), body, tex, pos);
			entity->setType(Textures::Tree_alpha);
			body->SetUserData(entity.get());
			break;
		}
		default:
			std::cout << "id not found" << std::endl;
			break;
	}

        if (id != Textures::RedAirplane_alpha && id != Textures::BlueAirplane_alpha &&  orientation == 0)
        {
          entity->setDirection({-1.f,0});
          entity->faceLeft();
        }

	if (entity && (id != Textures::BlueAirplane_alpha) && (id != Textures::RedAirplane_alpha)) {
	  objects.push_back(std::move(entity));
	  return true;
	}
	//entity was already added
	else {
		return false;
		}
}

/*  Remove entity  */

bool World::remove_bullet(Entity *bullet, Entity *entity) {
	for (auto it = objects.begin(); it != objects.end(); it++) {
		std::list<std::shared_ptr<Entity>>& bullets_list = (*it)->get_active_bullets();
		for (auto item = bullets_list.begin(); item != bullets_list.end(); item++) {
			if ((item->get() == bullet) && (bullet->getOwner() != entity)) {
				// raw pointers match, erase bullet
				b2Body* body = (*item)->getB2Body();
				body->SetUserData(nullptr);
				bullets_list.erase(item);
				// remove body also
				pworld.remove_body(body);
				return true;
			}
		}
	}
	for (auto it = player_planes.begin(); it != player_planes.end(); it++) {
		// Check also player_planes bullets
		std::list<std::shared_ptr<Entity>>& bullets_list = (*it)->get_active_bullets();
		for (auto item = bullets_list.begin(); item != bullets_list.end(); item++) {
			if ((item->get() == bullet) && (bullet->getOwner() != entity)) {
				// raw pointers match, erase bullet
				b2Body* body = (*item)->getB2Body();
				body->SetUserData(nullptr);
				bullets_list.erase(item);
				// remove body also
				pworld.remove_body(body);
				return true;
			}
		}
	}

	return false;
}
bool World::remove_entity(Entity *entity)
{
		for (auto it = objects.begin(); it != objects.end(); it++) {
			if (it->get() == entity) {
				// raw pointers match, erase entity from the vector
				std::list<std::shared_ptr<Entity>>& bullets_list = (*it)->get_active_bullets();
				for (auto item = bullets_list.begin(); item != bullets_list.end(); ) {
						// remove all entity's bullets
						b2Body* body = (*item)->getB2Body();
						body->SetUserData(nullptr);
						item = bullets_list.erase(item);
						// remove body also
						pworld.remove_body(body);
					}
				b2Body* body = (*it)->getB2Body();
				body->SetUserData(nullptr);
				objects.erase(it);
				pworld.remove_body(body);
				return true;
			}
		}
		// go through also player_planes
		for (auto it = player_planes.begin(); it != player_planes.end(); it++) {
			if (it->get() == entity) {
				// get player's bullets
				std::list<std::shared_ptr<Entity>>& bullets_list = (*it)->get_active_bullets();
				for (auto item = bullets_list.begin(); item != bullets_list.end(); ) {
						// remove all entity's bullets
						b2Body* body = (*item)->getB2Body();
						body->SetUserData(nullptr);
						item = bullets_list.erase(item);
						// remove body also
						pworld.remove_body(body);
					}
				b2Body* body = (*it)->getB2Body();
				body->SetUserData(nullptr);
				player_planes.erase(it);
				pworld.remove_body(body);
				return true;
			}
		}


	//entity was not found
	return false;
}

/*  Update the world  */

GameResult World::update(Game::GameMode game_mode) {
	//physicsworld step
	float32 timeStep = 1/60.0;      //the length of time passed to simulate (seconds)
  	int32 velocityIterations = 8;   //how strongly to correct velocity
  	int32 positionIterations = 3;   //how strongly to correct position

	pworld.get_world()->Step(timeStep, velocityIterations, positionIterations);

	for (auto &it : objects) {
		it->erase_surroundings();
	}
	for (auto &it : player_planes) {
		it->erase_surroundings();
	}

	//collision detection
	for (b2Contact* contact = pworld.get_world()->GetContactList(); contact;  contact = contact->GetNext()) {
		if (contact->IsTouching()){
			b2Fixture* a_fixture = contact->GetFixtureA();
			b2Fixture* b_fixture = contact->GetFixtureB();

			b2Body* a_body = a_fixture->GetBody();
			b2Body* b_body = b_fixture->GetBody();

			Entity* a_entity = static_cast<Entity*>(a_body->GetUserData());
			Entity* b_entity = static_cast<Entity*>(b_body->GetUserData());


			bool a_sensor = a_fixture->IsSensor();
			bool b_sensor = b_fixture->IsSensor();

			//only one was a sensor
			if (a_sensor ^ b_sensor) {
				if (a_sensor) {
					a_entity->insert_surrounding(b_entity);
				}

				else if (b_sensor) {
					b_entity->insert_surrounding(a_entity);
				}
			}

			else if ((a_sensor == false) && (b_sensor == false)) {
				if (a_entity->getType() == Textures::Bullet_alpha) {
					if (b_entity->getType() == Textures::Bullet_alpha) {
						// remove both bullets
						destroyed_bullet_bodies.push_back(b_body);
						// remove a_entity which is a bullet
						destroyed_bullet_bodies.push_back(a_body);
					}
					else if (a_entity->getOwner() != b_entity){
						if (b_entity->damage(10)) {
							destroyed_entity_bodies.push_back(b_body);
							/*Entity* owner = a_entity->getOwner();
							if ( owner->getTypeId() == Game::TYPE_ID::airplane)
							{
								Plane* owner_plane = dynamic_cast<Plane*>(owner);
								owner_plane->addToKillList(b_entity);
							}*/
						}
						// remove a_entity which is a bullet
						destroyed_bullet_bodies.push_back(a_body);
					}


				}
				else if (b_entity->getType() == Textures::Bullet_alpha) {

					if (b_entity->getOwner() != a_entity) {
						if (a_entity->damage(10)) {
							destroyed_entity_bodies.push_back(a_body);
							// A is killed by the owner of bullet B
							/*Entity* owner = b_entity->getOwner();
							if ( owner->getTypeId() == Game::TYPE_ID::airplane)
							{
								Plane* owner_plane = dynamic_cast<Plane*>(owner);
								owner_plane->addToKillList(a_entity);
							}*/
						}
						// remove b_entity which is a bullet
						destroyed_bullet_bodies.push_back(b_body);
					}


				}
				else if (a_entity->getTypeId() == Game::TYPE_ID::airplane) {
					if (b_entity->getTypeId() == Game::TYPE_ID::ground) {
						// airplane destroyed
						destroyed_entity_bodies.push_back(a_body);
					}
					else if (b_entity->getTypeId() == Game::TYPE_ID::airplane)
					{
						// damage both planes
						if (a_entity->damage(10)){
							destroyed_entity_bodies.push_back(a_body);
						}
						if (b_entity->damage(10)){
							destroyed_entity_bodies.push_back(b_body);
							//(reinterpret_cast<Plane*> (a_entity))->addToKillList(b_entity);
						}
					}
					else if (b_entity->getTypeId() == Game::TYPE_ID::infantry) {
              //(reinterpret_cast<Plane*> (a_entity))->addToKillList(b_entity);
						// destroy infantry and damage plane
						destroyed_entity_bodies.push_back(b_body);
						if (a_entity->damage(10)) {
							destroyed_entity_bodies.push_back(a_body);
						}
					}
				}
				else if (b_entity->getTypeId() == Game::TYPE_ID::airplane) {
					if (a_entity->getTypeId() == Game::TYPE_ID::ground) {
						// airplane destroyed
						destroyed_entity_bodies.push_back(b_body);
					}
					else if (a_entity->getTypeId() == Game::TYPE_ID::airplane)
					{
						// damage both planes
						if (b_entity->damage(10)) {
							destroyed_entity_bodies.push_back(b_body);
							//(reinterpret_cast<Plane*> (a_entity))->addToKillList(b_entity);
						}
						if (a_entity->damage(10)) {
							destroyed_entity_bodies.push_back(a_body);
							//(reinterpret_cast<Plane*> (b_entity))->addToKillList(a_entity);
						}
					}
					else if (a_entity->getTypeId() == Game::TYPE_ID::infantry) {
              //(reinterpret_cast<Plane*> (b_entity))->addToKillList(a_entity);
						// destroy infantry and damage plane
						destroyed_entity_bodies.push_back(a_body);
						if (b_entity->damage(10)) {
							destroyed_entity_bodies.push_back(b_body);
						}
					}
				}



			}

		}

	}
	// remove destroyed_bodies from the world
	// bullets must be removed first because they are stored within other entities

	// sort the list and remove dublicates so that no entity / bullet is removed twice
	destroyed_bullet_bodies.sort();
	destroyed_bullet_bodies.unique();
	for (auto it : destroyed_bullet_bodies) {
		Entity* bullet = static_cast<Entity*>(it->GetUserData());
		remove_bullet(bullet, bullet);
	}
	// clear all old pointers which have been removed
	destroyed_bullet_bodies.clear();

	destroyed_entity_bodies.sort();
	destroyed_entity_bodies.unique();
	for (auto it : destroyed_entity_bodies) {
		Entity* entity = static_cast<Entity*>(it->GetUserData());
		remove_entity(entity);
	}
	destroyed_entity_bodies.clear();

	//updating the world
	for (auto it : objects) {
		//1. send ai information
                AI::get_action(*it, it->get_surroundings(), resources);
		//do something with ai information

		//2. update new positions
		//new position for sprite
		float x_corr = it->getSize().x/2;
		float y_corr = it->getSize().y/2;
		float x = Game::TOPIXELS*it->getB2Body()->GetPosition().x-x_corr;
		float y = Game::TOPIXELS*it->getB2Body()->GetPosition().y-y_corr;
		sf::Vector2f newpos(x,y);
		it->setPos(newpos);

		std::list<std::shared_ptr<Entity>> bullets = it->get_active_bullets();

		for (auto b : bullets) {
			float x_corr = b->getSize().x/2;
			float y_corr = b->getSize().y/2;
			float x = Game::TOPIXELS*b->getB2Body()->GetPosition().x-x_corr;
			float y = Game::TOPIXELS*b->getB2Body()->GetPosition().y-y_corr;
			sf::Vector2f newpos(x,y);
			b->setPos(newpos);

			b->drawTo(window);
		}

		//set sfml sprite's angle from body's angle
		//it->setRot(it->getB2Body().GetAngle()*RADTODEG);

		it->drawTo(window);
	}

	// Draw player planes
	for (auto it : player_planes) {
		float x_corr = it->getSize().x/2;
		float y_corr = it->getSize().y/2;
		float x = Game::TOPIXELS*it->getB2Body()->GetPosition().x-x_corr;
		float y = Game::TOPIXELS*it->getB2Body()->GetPosition().y-y_corr;
		sf::Vector2f newpos(x,y);
		it->setPos(newpos);

		std::list<std::shared_ptr<Entity>> bullets = it->get_active_bullets();

		for (auto b : bullets) {
			float x_corr = b->getSize().x/2;
			float y_corr = b->getSize().y/2;
			float x = Game::TOPIXELS*b->getB2Body()->GetPosition().x-x_corr;
			float y = Game::TOPIXELS*b->getB2Body()->GetPosition().y-y_corr;
			sf::Vector2f newpos(x,y);
			b->setPos(newpos);

			b->drawTo(window);
		}

		//set sfml sprite's angle from body's angle
		it->setRot(it->getB2Body()->GetAngle()*RADTODEG);

		it->drawTo(window);
	}

	return checkGameStatus(game_mode);
}

std::vector<std::shared_ptr<Entity>>& World::get_all_entities()
{
  return objects;
}

std::deque<std::shared_ptr<Entity>>& World::get_player_planes()
{
	return player_planes;
}

std::vector<std::shared_ptr<Entity>>& World::get_bullets()
{
	return bullets;
}

GameResult World::checkGameStatus(Game::GameMode game_mode)
{
	if (game_mode == Game::GameMode::SinglePlayer) {
		// Red team won if blue plane destroyed
		if (player_planes.size() == 0) {
			return GameResult::RedWon;
		}
		else {
			// Blue team won if all red planes and bases destroyed
			for (auto it : objects){
				if ((it->getType() == Textures::RedBase_alpha )|| (it->getType() == Textures::RedAirplane_alpha)) {
					// not all red planes and bases destroyed, game UnFinished
					return GameResult::UnFinished;
				}
			}
			// All red planes and bases destroyed
			return GameResult::BlueWon;
		}
	}
	else {
		// Multiplayer is over when red or blue plane is destroyed
		if (player_planes.size() < 2) {
			if (player_planes.size() == 1) {
				if (player_planes[0]->getType() == Textures::RedAirplane_alpha) {
					return GameResult::RedWon;
				}
				else return GameResult::BlueWon;
			}
			else return GameResult::TieGame;

		}
		// both planes still active
		return GameResult::UnFinished;
	}
}

int World::getScore()
{
	return score;
}
