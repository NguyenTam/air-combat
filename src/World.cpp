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
					create_entity(type, x, y, orientation, width, height);
				}
			}
		}
	}
	return true;
}

void World::clear_all() {
	
}

World::World(sf::RenderWindow &main_window, ResourceManager &_resources) : window(main_window), resources(_resources) {
}

/*  Create entity  */

bool World::create_entity(std::string type, double x, double y, int orientation, double width, double height) {
	//b2Body* body = pworld.create_body()
	//std::shared_ptr<Entity> entity = std::make_shared<Entity>(pworld, )

	/*if (std::find(objects.begin(), objects.end(), entity) != objects.end()) {
		objects.push_back(entity);
		return true;
	}
	//entity was already added
	else {
		return false;
	}*/

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
	
	for (auto const& it : objects) {
		if (it->getB2Body().GetType() == b2_dynamicBody) {

			//new position for sprite
			sf::Vector2f newpos(TOPIXELS*it->getB2Body().GetPosition().x, TOPIXELS*it->getB2Body().GetPosition().y);
			it->setPos(newpos);
			
			//set sfml sprite's angle from body's angle
			it->setRot(it->getB2Body().GetAngle()*RADTODEG);
		}

		it->drawTo(window);
	}
	
}