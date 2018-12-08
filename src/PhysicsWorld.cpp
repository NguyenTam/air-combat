#include "PhysicsWorld.hpp"
#include "CommonDefinitions.hpp"
PhysicsWorld::PhysicsWorld() {
        b2Vec2 gvector(0.0f, Game::GRAVITY);
	World = new b2World(gvector);
}

b2Body* PhysicsWorld::create_body_dynamic(double x, double y, double width, double height) {
	//creating a definition of a body
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody; //creating a dynamic body
	BodyDef.position = b2Vec2((x+(width/2))/Game::TOPIXELS, (y+(height/2))/Game::TOPIXELS); //set initial position (meters, not pixels)
	BodyDef.angle = 0; //set initial angle (radians)

	//creating a body
	b2Body* Body = World->CreateBody(&BodyDef);

	//creating fixture to an "invisible" body
	b2PolygonShape boxShape; //hitbox that has a shape of a box
	boxShape.SetAsBox((width/2)/Game::TOPIXELS, (height/2)/Game::TOPIXELS); 

	b2FixtureDef FixtureDef;
	FixtureDef.shape = &boxShape;
	FixtureDef.density = 1; //mass of the body is AREA * density
	FixtureDef.filter.categoryBits = 0x0004;
	Body->CreateFixture(&FixtureDef);

	//sensor
	b2CircleShape radarshape;
	b2FixtureDef radar;
	radarshape.m_radius = 50; //radius of the sensor
	radar.shape = &radarshape;
	radar.isSensor = true;
	radar.filter.categoryBits = 0x0002; //id for dynamic body
	radar.filter.maskBits = 0x0004; //make radar only detect dynamic bodies

	Body->CreateFixture(&radar);

	return Body; 
}

b2Body* PhysicsWorld::create_body_static(double x, double y, double width, double height) {
	b2BodyDef BodyDef;
	BodyDef.type = b2_staticBody;
	BodyDef.position = b2Vec2((x+(width/2))/Game::TOPIXELS, (y+(height/2))/Game::TOPIXELS);

	b2Body* Body = World->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((width/2)/Game::TOPIXELS, (height/2)/Game::TOPIXELS); 

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
