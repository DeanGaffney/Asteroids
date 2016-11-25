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

const float SPEED = 1.0f;
const float SHIP_MAX_ANGULAR_VELOCITY = 120.0f*SPEED;
const float SHIP_MAX_ACCELERATION = 5.0f*SPEED;
const float SHIP_MAX_SPEED = 1.5f*SPEED;
const float SHIP_FIRE_DELAY = 0.2f;

const float BULLET_DIE_DELAY = 1.0f;
const float BULLET_SPEED = 3.0f*SPEED;

const float ASTEROID_MAX_SPEED = 0.5f*SPEED;
const float ASTEROID_MIN_SPEED = 0.1f*SPEED;

extern Ship ship;
extern BulletPool bullets;
extern AsteroidPool asteroids;

bool checkBulletAsteroidCollision(Bullet & bullet, Asteroid & asteroid);

#endif