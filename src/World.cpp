/**
  *   @file World.cpp
  *   @brief Source file for class Ẃorld
  */

#include "World.h"

/*  Class World  */

/*  Constructor  */

World::World(sf::RenderWindow *main_window) : window(main_window) {
}

/*  Add entity  */

bool World::add_entity(Entity *entity) {

	if (std::find(objects.begin(), objects.end(), entity) != objects.end()) {
		objects.push_back(entity);
		return true;
	}
	//entity was already added
	else {
		return false;
	}
}

/*  Remove entity  */

bool World::remove_entity(Entity *entity) {
	
	auto it = std::find(objects.begin(), objects.end(), entity);
	
	if (it != objects.end()) {
		objects.erase(it);
		return true;
	}

	//entity was not found
	else {
		return false;
	}
}
/*  Update the world  */

void World::update() {

}