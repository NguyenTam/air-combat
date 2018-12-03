#pragma once

#include <Box2D/Box2D.h>

const float gravity = 9.8f;
const float SCALE = 60.f;

class PhysicsWorld {
public:
	PhysicsWorld();
	~PhysicsWorld();
	b2Body* create_body_dynamic(std::string type, double x, double y, int orientation, double width, double height);
	b2Body* create_body_static(std::string type, double x, double y, int orientation, double width, double height);
	void remove_body(b2Body* body);
	b2World* get_world();
	void move();
	
private:
	b2World* World;
};