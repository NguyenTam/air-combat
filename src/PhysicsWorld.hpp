/**
  *   @file PhysicsWorld.hpp
  *   @brief Header for PhysicsWorld class and structs related to it
  */

#pragma once

/*  Includes  */

#include <Box2D/Box2D.h>

/**
  *   @class PhysicsWorld
  */

class PhysicsWorld {
public:

  /**
   *   @brief Construct a PhysicsWorld object.
   */
	PhysicsWorld();

  /**
   *   @brief Destructor a PhysicsWorld object.
   */
	~PhysicsWorld();

  /**
   *   @brief Creates a dynamic body
   *   @param x X-position where new body is created
   *   @param y Y-position where new body is created
   *   @param width Width of the body
   *   @param height Height of the body
   *   @return Created body
   */
	b2Body* create_body_dynamic(double x, double y, double width, double height);

  /**
   *   @brief Creates a static body
   *   @param x X-position where new body is created
   *   @param y Y-position where new body is created
   *   @param width Width of the body
   *   @param height Height of the body
   *   @return Created body
   */
	b2Body* create_body_static(double x, double y, double width, double height);

  /**
   *   @brief Removes a body
   *   @param body Body to be removed
   */
	void remove_body(b2Body* body);

  /**
   *   @brief Creates a bullet
   *   @param x X-position where new body is created
   *   @param y Y-position where new body is created
   *   @param width Width of the body
   *   @param height Height of the body
   *   @return Created bullet
   */
	b2Body* create_body_bullet(double x, double y, double width, double height);

  /**
   *   @brief Gets the world of PhysicsWorld
   *   @return World of PhysicsWorld
   */
	b2World* get_world();

  /**
   *   @brief Move function, this is done elsewhere now
   */
	void move();
	
private:
	b2World* World; /**< World of PhysicsWorld */
};
