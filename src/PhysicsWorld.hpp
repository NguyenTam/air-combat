#pragma once

#include <Box2D/Box2D.h>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

const float gravity = 9.8f;

class PhysicsWorld {
public:
	PhysicsWorld();
	~PhysicsWorld();
	b2Body* create_body();
	void move();
	
private:
	b2World* World;
};