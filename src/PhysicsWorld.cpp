#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld() {
	b2Vec2 gvector(0.0f, gravity);
	World = new b2World(gvector);
}

b2Body* PhysicsWorld::create_body_dynamic(std::string type, double x, double y, int orientation, double width, double height) {
	//creating a definition of a body
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody; //creating a dynamic body
	BodyDef.position = b2Vec2(x/SCALE, y/SCALE); //set initial position (meters, not pixels)
	BodyDef.angle = 0; //set initial angle (radians)

	//creating a body
	b2Body* Body = World->CreateBody(&BodyDef);

	//creating fixture to an "invisible" body
	b2PolygonShape boxShape; //hitbox that has a shape of a box
	boxShape.SetAsBox((width/2)/SCALE, (height/2)/SCALE); 

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1; //mass of the body is AREA * density
	Body->CreateFixture(&boxFixtureDef);

	return Body; 
}

b2Body* PhysicsWorld::create_body_static(std::string type, double x, double y, int orientation, double width, double height) {
	b2BodyDef BodyDef;
	BodyDef.type = b2_staticBody;
	BodyDef.position = b2Vec2(x/SCALE, y/SCALE);

	b2Body* Body = World->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((width/2)/SCALE, (height/2)/SCALE); 

	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);

	return Body;
}

void PhysicsWorld::remove_body(b2Body* body) {
	World->DestroyBody(body);
}

b2World* PhysicsWorld::get_world() {
	return World;
}

PhysicsWorld::~PhysicsWorld() {
	delete World;
}