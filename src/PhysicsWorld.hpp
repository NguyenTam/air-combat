#pragma once

#include <Box2D/Box2D.h>

const float gravity = 9.8f;

class PhysicsWorld {
public:
	PhysicsWorld();
	~PhysicsWorld();
	b2Body* create_body();
	void remove_body(b2Body* body);
	b2World* get_world();
	void move();
	
private:
	b2World* World;
};