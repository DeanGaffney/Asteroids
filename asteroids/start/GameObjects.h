
#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "../../common/core.h"
#include "../../common/Pool.h"

const float ASTEROID_SCALE = 0.1f;
const int ASTEROID_GRANULARITY = 20;
const float ASTEROID_MAX_RADIUS = 1.2f;
const float ASTEROID_MIN_RADIUS = 0.8f;
const float ASTEROID_ANGLE_VARABILITY = 0.5f;

// ======================================
// BaseGameObject
// ======================================

class BaseGameObject {
public:
	enum State {ASLEEP, ALIVE, DEAD};
	State state;
		
	float damping;
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	
	float angle;
	float angularVelocity;
	float angularAcceleration;
	
	virtual void render() = 0;
	virtual void update(float dt);
	virtual void reset();
	float radius;					//used for circle collision detection
	float invincibilityTime;		//used for powerups and not destroying newly spawned asteroids
};

// ======================================
// Ship
// ======================================

class Ship: public BaseGameObject {
	float timeToFire;
	int health;
	int bulletsRemaining;

public:
	bool fire;
	void render();
	void update(float dt);
	void reset();
};

// ======================================
// Bullet
// ======================================

class Bullet: public BaseGameObject {
	float timeToDie;
public:
	void render();
	void reset();
	void update(float dt);
};

typedef Pool<Bullet> BulletPool;

// ======================================
// Asteroid
// ======================================

class Asteroid: public BaseGameObject {
	
public:
	int enumIndex;
	enum Type {LARGE, MEDIUM, SMALL, TINY};
	Type type;
	  
	float size;
	Vector2f vertices[ASTEROID_GRANULARITY];
	float angles[ASTEROID_GRANULARITY];
	void render();
	void reset();
	void update(float dt);
	void setNextType();
	int getEnumIndex();
};

typedef Pool<Asteroid> AsteroidPool;


#endif
