/**
  *   @file World.cpp
  *   @brief Source file for class Ẃorld
  */

#include "World.hpp"

/*  Class World  */

/*  Constructor  */

//change map's first element to template?

bool World::read_level(std::string filename) {
	//entity type; x; y; orientation; width; height
	std::string parsed[5];
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
			                parsed[0] = std::string(split_str);
			                break;
			              case 1:
			                parsed[1] = std::stod(split_str);
			                break;
			              case 2:
			                parsed[2] = std::stod(split_str);
			                break;
			              case 3:
			                parsed[3] = std::stoi(split_str);
			                break;
			              case 4:
			                parsed[4] = std::stod(split_str);
			                break;
			              case 5:
			                parsed[5] = std::stod(split_str);
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
					//ADD ENTITY HERE
				}
			}
		}
	}
	return true;
}

void World::clear_all() {
	
}

World::World(sf::RenderWindow *main_window) : window(main_window) {
}

/*  Add entity  */

bool World::add_entity(Entity *entity) {

	if (objects.find(entity) != objects.end()) {
		//add new pair (Entity*,Body*) to objects-map
		//objects[entity] = pworld.create_body_dynamic();

		return true;
	}
	//entity was already added
	else {
		return false;
	}
}

/*  Remove entity  */

bool World::remove_entity(Entity *entity) {
	auto it = objects.find(entity);
	
	if (it != objects.end()) {
		pworld.remove_body(it->second); //remove body from physics world
		objects.erase(it); //erase from objects maps
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

	for (auto const& it : objects) {
		if (it.second->GetType() == b2_dynamicBody) {

			//new position for sprite
			sf::Vector2f newpos(TOPIXELS*it.second->GetPosition().x, TOPIXELS*it.second->GetPosition().y);
			it.first->setPos(newpos);
			
			//set sfml sprite's angle from body's angle
			it.first->setRot(it.second->GetAngle()*RADTODEG);
		}

		it.first->drawTo(*window);
	}

}