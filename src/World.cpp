/**
  *   @file World.cpp
  *   @brief Source file for class Ẃorld
  */

#include "World.hpp"
/*  Class World  */

/*  Constructor  */

World::World(sf::RenderWindow &main_window, ResourceManager &_resources) : pworld(), window(main_window), resources(_resources) {}

/*  Parse level .txt file and create world's entities  */

bool World::read_level(std::string& filename) {
	//entity type; x; y; orientation; width; height
	double x, y, width, height;
  	int orientation;
  	std::string type;
	std::ifstream file(filename);
	if (file.is_open()) {
		//clear all
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
					//clear all
					return false;
				}
				else {
					//all ok
					try {
						Textures::ID id = Textures::alphaTextures.at(type);
						create_entity(id, x, y, orientation, width, height);
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

void World::clear_all() {}

/*  Create entity  */

bool World::create_entity(Textures::ID id, double x, double y, int orientation, double width, double height) {
	sf::Texture &tex = resources.get(id);
	sf::Vector2f pos(x,y);
	b2Body* body;
	std::shared_ptr<Entity> entity;
	
	switch(id) {
		case Textures::BlueAirplane_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Plane>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::BlueAntiAircraft_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Artillery>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::BlueBase_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Base>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::BlueHangar_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Hangar>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::BlueInfantry_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Infantry>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::Bullet_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Bullet>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::Ground_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Ground>(*pworld.get_world(), *body, tex, pos);
			entity->setScale(width,height);
			break;
		}
		case Textures::RedAirplane_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Plane>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::RedAntiAircraft_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Artillery>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::RedBase_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Base>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::RedHangar_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Hangar>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::RedInfantry_alpha: {
			body = pworld.create_body_dynamic(x, y, width, height);
			entity = std::make_shared<Infantry>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::Rock_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Stone>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		case Textures::Tree_alpha: {
			body = pworld.create_body_static(x, y, width, height);
			entity = std::make_shared<Tree>(*pworld.get_world(), *body, tex, pos);
			break;
		}
		default:
			std::cout << "id not found" << std::endl;
			break;
	}
	
	if (entity) {	
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

	for (b2Contact* contact = pworld.get_world()->GetContactList(); contact;  contact = contact->GetNext()) {
		if (contact->IsTouching()){
			b2Body* a_body = contact->GetFixtureA()->GetBody();
			b2Body* b_body = contact->GetFixtureB()->GetBody();

			std::shared_ptr<Entity> a_entity;
			std::shared_ptr<Entity> b_entity;

			for (auto it = objects.begin(); it != objects.end(); it++) {
				if (&(*it)->getB2Body() == a_body)
					a_entity = *it;
				else if (&(*it)->getB2Body() == b_body)
					b_entity = *it;
			}
		}


	}
	
	for (auto it : objects) {
		//new position for sprite
		float x_corr = it->getSize().x/2;
		float y_corr = it->getSize().y/2;
		float x = Game::TOPIXELS*it->getB2Body().GetPosition().x-x_corr;
		float y = Game::TOPIXELS*it->getB2Body().GetPosition().y-y_corr;
		sf::Vector2f newpos(x,y); 
		it->setPos(newpos);
		
		//set sfml sprite's angle from body's angle
		it->setRot(it->getB2Body().GetAngle()*RADTODEG);
		
		it->drawTo(window);
	}
	
}
