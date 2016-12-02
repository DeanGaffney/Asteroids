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
const float SHIP_FIRE_DELAY = 2.0f;

const float BULLET_DIE_DELAY = 1.0f;
const float BULLET_SPEED = 3.0f*SPEED;

const float ASTEROID_MAX_SPEED = 0.5f*SPEED;
const float ASTEROID_MIN_SPEED = 0.1f*SPEED;

const int MAX_ENUM_TYPE = 4;
const float sizes [] = {1.0,0.75,0.5,0.25};
extern Ship ship;
extern BulletPool bullets;
extern AsteroidPool asteroids;

bool checkBulletAsteroidCollision(const Vector2f point,const Asteroid & asteroid);
bool isPointInsideCircle(const Vector2f point,const Vector2f center,const float radius);
void cullObjects();
void checkCollisions();
void destroyAsteroid(Asteroid & asteroid,const int index);
void createAsteroid(const Vector2f position,const int type);
#endif
