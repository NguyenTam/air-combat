/**
  *   @file World.cpp
  *   @brief Source file for class Ẃorld
  */

#include "World.hpp"

/*  Class World  */

/*  Constructor  */

World::World(sf::RenderWindow *main_window) : window(main_window) {
}

/*  Add entity  */

bool World::add_entity(Entity *entity) {

	if (objects.find(entity) != objects.end()) {
		//add new pair (Entity*,Body*) to objects-map
		objects[entity] = pworld.create_body();

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
			//set new body position as entity's position
		}
	}

}