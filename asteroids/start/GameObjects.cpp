#include "asteroids.h"
#include "GameObjects.h"

// ======================================
// BaseGameObject
// ======================================
 
void BaseGameObject::update(float dt) {
	// linear movement
	velocity += dt*acceleration;
	position += dt*velocity;
	velocity *= pow(damping, dt);
	
	//anglular movement
	angle += dt*angularVelocity;
}

void BaseGameObject::reset() {
	state = BaseGameObject::ALIVE;
	velocity = Vector2f::ZERO;
	position = Vector2f::ZERO;
	acceleration = Vector2f::ZERO;
	angle = 0;
	angularVelocity = 0;
	damping = 1;
}

// ======================================
// Ship
// ======================================

void Ship::reset() {
	BaseGameObject::reset();
	
	position = Vector2f(ASPECT/2,0.5);
	damping = 0.8;
	
	timeToFire = 0;
}

void Ship::update(float dt) {
	// TODO - update position (using base class)
	// TODO - process ship control events (update velocity)
	// TODO - process fire events 
}

// ======================================
// Bullet
// ======================================

void Bullet::reset() {
	// TODO - reset start (using base class),  and reset time left to die.
}

void Bullet::update(float dt) {
	// TODO - update position (using base class), update and check time left to die.
}


// ======================================
// Asteroid
// ======================================

void Asteroid::reset() {
	BaseGameObject::reset();
	
	// TODO - create random asteroid as outlined in class
	
	// TODO - random rotation angle 
}

void Asteroid::update(float dt) {
	BaseGameObject::update(dt);
}