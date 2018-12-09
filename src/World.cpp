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
						pworld.create_body_static(x, y, width, height);
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
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Plane>(*pworld.get_world(), *body, tex, pos, direct, Game::TEAM_ID::blue);
			body->SetUserData(entity.get());
			body->SetGravityScale(0); //gravity 0 for plane
			// add BlueAirplane to player_planes[0] (controlled by player not by AI)
			player_planes.push_front((std::move(entity)));
			break;
		}
		case Textures::BlueAntiAircraft_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Artillery>(*pworld.get_world(), *body, tex, pos, Game::TEAM_ID::blue);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::BlueBase_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Base>(*pworld.get_world(), *body, tex, pos, Game::TEAM_ID::blue);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::BlueHangar_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Hangar>(*pworld.get_world(), *body, tex, pos, Game::TEAM_ID::blue);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::BlueInfantry_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Infantry>(*pworld.get_world(), *body, tex, pos, Game::TEAM_ID::blue);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::Bullet_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Bullet>(*pworld.get_world(), *body, tex, pos, direct);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::Ground_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Ground>(*pworld.get_world(), *body, tex, pos);
			entity->setScale(width,height);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::RedAirplane_alpha: {
			if (game_mode == Game::GameMode::SinglePlayer) {
				// add RedAirplanes to the normal container (controlled by AI)
				body = pworld.create_body_dynamic(x, y, width, height);
				entity = std::make_shared<Plane>(*pworld.get_world(), *body, tex, pos, direct, Game::TEAM_ID::red);
				body->SetUserData(&(*entity));
				body->SetGravityScale(0); //gravity 0 for plane
				objects.push_back(std::move(entity));
			}
			else {
				// Add RedAirplane to player_planes container
				if (player_planes.size() == 1) {
					if (player_planes[0]->getTypeId() == Textures::BlueAirplane_alpha) {
						// only one RedAirplane is alowed and it needs to be at player_planes[1]
						body = pworld.create_body_dynamic(x, y, width, height);
						entity = std::make_shared<Plane>(*pworld.get_world(), *body, tex, pos, direct, Game::TEAM_ID::red);
						body->SetUserData(&(*entity));
						body->SetGravityScale(0); //gravity 0 for plane
						player_planes.push_back(std::move(entity));
					}
				}
				else if (player_planes.size() == 0) {
					body = pworld.create_body_dynamic(x, y, width, height);
					entity = std::make_shared<Plane>(*pworld.get_world(), *body, tex, pos, direct, Game::TEAM_ID::red);
					body->SetUserData(&(*entity));
					body->SetGravityScale(0); //gravity 0 for plane
					player_planes.push_back(std::move(entity));
				}
			}
			break;
		}
		case Textures::RedAntiAircraft_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Artillery>(*pworld.get_world(), *body, tex, pos, Game::TEAM_ID::red);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::RedBase_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Base>(*pworld.get_world(), *body, tex, pos, Game::TEAM_ID::red);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::RedHangar_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Hangar>(*pworld.get_world(), *body, tex, pos, Game::TEAM_ID::red);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::RedInfantry_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Infantry>(*pworld.get_world(), *body, tex, pos, Game::TEAM_ID::red);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::Rock_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Stone>(*pworld.get_world(), *body, tex, pos);
			body->SetUserData(entity.get());
			break;
		}
		case Textures::Tree_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Tree>(*pworld.get_world(), *body, tex, pos);
			body->SetUserData(entity.get());
			break;
		}
		default:
			std::cout << "id not found" << std::endl;
			break;
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

bool World::remove_entity(std::shared_ptr<Entity> entity) {
	auto it = std::find(objects.begin(), objects.end(), entity);

	if (it != objects.end()) {
		objects.erase(it); //erase entity from vector

		return true;
	}

	//entity was not found
	else {
		return false;
	}

}

/*  Update the world  */

void World::update() {
	//physicsworld step
	float32 timeStep = 1/60.0;      //the length of time passed to simulate (seconds)
  	int32 velocityIterations = 8;   //how strongly to correct velocity
  	int32 positionIterations = 3;   //how strongly to correct position

	pworld.get_world()->Step(timeStep, velocityIterations, positionIterations);

	for (auto it : objects) {
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

				else {
					b_entity->insert_surrounding(a_entity);
				}
			}

		}

	}

	//updating the world
	for (auto it : objects) {
		//1. send ai information
	  	AI::get_action(*it, it->get_surroundings());
		//do something with ai information

		//2. update new positions
		//new position for sprite
		float x_corr = it->getSize().x/2;
		float y_corr = it->getSize().y/2;
		float x = Game::TOPIXELS*it->getB2Body().GetPosition().x-x_corr;
		float y = Game::TOPIXELS*it->getB2Body().GetPosition().y-y_corr;
		sf::Vector2f newpos(x,y);
		it->setPos(newpos);

		//set sfml sprite's angle from body's angle
		//it->setRot(it->getB2Body().GetAngle()*RADTODEG);

		it->drawTo(window);
	}

	// Draw player planes
	for (auto it : player_planes) {
		it->drawTo(window);
	}

}

std::vector<std::shared_ptr<Entity>>& World::get_all_entities()
{
  return objects;
}
