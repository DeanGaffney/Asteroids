
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
	virtual void wrap();
	float radius;						//used for circle collision detection
	float spawnInvincibilityTime;		//used for powerups and not destroying newly spawned asteroids
};

// ======================================
// Ship
// ======================================

class Ship: public BaseGameObject {
	float timeToFire;
	float shieldTimer;
public:
	enum Activity {FIGHT,FLIGHT,AMMO,HEALTH,WAIT};
	Activity activity;
	
	bool hasTarget;
	bool autoNavigation;
	float damageRecoveryTimer;
	bool isShieldActive;
	float shieldSize;
	int health;
	int bulletsRemaining;
	bool fire;
	void render();
	void update(float dt);
	void reset();
	void wrap();
	void fireBullet();
	bool isAllowedFire();
	bool isTakingDamage();
	float getAngleToPowerup(const int type);
	bool isTypeInPowerups(const int type);
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
	void wrap();
};

typedef Pool<Asteroid> AsteroidPool;

class Powerup: public BaseGameObject{
	float timeToDie;
public:
	enum Type {HEALTH,AMMO,REPEL,SHIELD};
	Type type;
	
	float size;
	void render();
	void reset();
	void update(float dt);
	void wrap();
	void giveShipHealth(Ship & ship);
	void giveShipBullets(Ship & ship);
	void repelAsteroids(Ship & ship);
	void giveShipShield(Ship & ship);
};

typedef Pool<Powerup> PowerupPool;


#endif
