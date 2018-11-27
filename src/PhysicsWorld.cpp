#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld() {
	b2Vec2 gvector(0.0f, gravity);
	World = new b2World(gvector);
}

b2Body* PhysicsWorld::create_body() {
	//creating a definition of a body
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody; //creating a dynamic body
	BodyDef.position.Set(0,0); //set initial position (meters, not pixels)
	BodyDef.angle = 0; //set initial angle (radians)

	//creating a body
	b2Body* Body = World->CreateBody(&BodyDef);

	//creating fixture to an "invisible" body
	b2PolygonShape boxShape; //hitbox that has a shape of a box
	boxShape.SetAsBox(1,1); //2x2 box

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1; //mass of the body is AREA x density, here (4*1)
	Body->CreateFixture(&boxFixtureDef);

	return Body;
}