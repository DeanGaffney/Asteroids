// ===============================================
// @file   asteroids.h
// @author kmurphy
// @practical asteroids
// @brief  Main header file for PSP+GLFW asteroids game
// ===============================================

#ifndef ASTEROIDS_H
#define ASTEROIDS_H


#include "platform.h"

#include "../../common/core.h"

#include "GameObjects.h"

const float SPEED = 0.1f;
const float SHIP_MAX_ANGULAR_VELOCITY = 120.0f*SPEED;
const float SHIP_MAX_ACCELERATION = 2.0f*SPEED;
const float SHIP_MAX_SPEED = 1.5f*SPEED;
const float SHIP_FIRE_DELAY = 5.0f;
const int SHIP_MAX_HEALTH = 100;
const int SHIP_MAX_BULLETS = 20;
const float SHIP_SHIELD_TIME = 60;
const float SHIP_SHIELD_SCALE = 0.1;
const float SHIP_SHIELD_SIZE = 1.0;
const float SHIP_RECOVERY_TIME = 5.0f;

const float BULLET_DIE_DELAY = 1.0f;
const float BULLET_SPEED = 3.0f*SPEED;

const float ASTEROID_MAX_SPEED = 0.5f*SPEED;
const float ASTEROID_MIN_SPEED = 0.1f*SPEED;
const int MAX_ASTEROIDS_SPAWNABLE = 4;
const int MIN_ASTEROIDS_SPAWNABLE = 1;
const float ASTEROID_SPAWN_TIME = 60;

const float POWERUP_MAX_SPEED = 0.3f*SPEED;
const float POWERUP_MIN_SPEED = 0.1f*SPEED;
const float POWERUP_SCALE = 0.1;
const float POWERUP_SIZE = 0.5;
const float POWERUP_EXPIRE_TIME = 120;
const float POWERUP_SPAWN_TIME = 240;
const int MAX_POWERUP_TYPES = 4;
const float SPAWN_INVINCIBILITY_TIME = 1.0f;

const float HEALTH_BAR_WIDTH = 0.5;


const int MAX_ENUM_TYPE = 4;
const float sizes [] = {1.0,0.75,0.5,0.25};
extern Ship ship;
extern BulletPool bullets;
extern AsteroidPool asteroids;
extern PowerupPool powerups;
extern float powerupSpawnTime;
extern float asteroidSpawnTime;

bool checkBulletAsteroidCollision(const Vector2f point,const Asteroid & asteroid);
bool isPointInsideCircle(const Vector2f point,const Vector2f center,const float radius);
bool circleCollision(const float distance, const float radius1, const float radius2);
bool isMovingTowardsPoint(const Vector2f point, const Vector2f objectPos, const Vector2f objectVelocity);
void cullObjects();
void checkCollisions();
void destroyAsteroid(Asteroid & asteroid,const int index);
void spawnAsteroid(const Vector2f position,const int type);
void spawnAsteroid();
void setPowerupColor(const Powerup::Type type);
bool canSpawnPowerup(const int chance);
void spawnPowerup();
void triggerPowerup(Powerup & powerup);

#endif
