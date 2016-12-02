// ===============================================
// @file   asteroids.cpp
// @author kmurphy
// @practical asteroids
// @brief  Main file for PSP+GLFW asteroids game
// ===============================================

#include "asteroids.h"
#include "GameObjects.h"
#include <cmath>
Ship ship;
BulletPool bullets(1000);
AsteroidPool asteroids(20);


int main() {

	bool done = false;
	
	initGraphics("Asteroids");
	
	while (!done) {

		switch (gameState) {

			case(GAME_INTRO): {
				changeGameState(GAME_START);
				break;
			}

			case(GAME_START): {
				changeGameState(LEVEL_START);
				break;
			}

			case(LEVEL_START): {
				ship.reset();
				ship.position = Vector2f(ASPECT/2,0.5f);
				ship.velocity = Vector2f::ZERO;
				Asteroid & asteroid = asteroids.allocate();
				asteroid.reset();
				asteroid.position = Vector2f(ASPECT/1.5,0.5f);
				changeGameState(LEVEL_PLAY);
				break;
			}

			case(LEVEL_PLAY): {
				update();
				render();
				getInput();
				break;
			}

			case(LEVEL_OVER): {
				changeGameState(GAME_OVER);
				break;
			}

			case(GAME_OVER): {
				changeGameState(GAME_QUIT);
				break;
			}

			case(GAME_QUIT): {
				done = true;
				break;
			}

			default: {
				printf ("Game state %d is not valid.\n", gameState);				
			}
		}
	}
	
	deinitGraphics();
}

bool wrapGameObject(BaseGameObject & baseGameObject) {
	//check if a game object is outside screen area and wrap it if needed.
	return baseGameObject.position.x > ASPECT || baseGameObject.position.x < 0 || 
	baseGameObject.position.y > 1 || baseGameObject.position.y < 0;
}

void update() {

	// TODO - update ship
	ship.update(dt);
	
	// TODO - update bullets
	for(int k = 0; k < bullets.size(); k++)bullets[k].update(dt);
	// TODO - check collisions bullets-asteroids

	// TODO - update asteroids
	// If asteroids hit (state=dead) then generate two (or better random) number of smaller asteroids
	// new asteroids move off at random direction and rotation
	for(int k = 0; k < asteroids.size();k++) asteroids[k].update(dt);
	wrapGameObject(ship);
	
	//cull game objects
	cullObjects();
}

void cullObjects(){
	//cull ship bullets
	for(int k = bullets.size();--k >= 0;){
		if(bullets[k].state == BaseGameObject::DEAD)bullets.free(k);
		else if(wrapGameObject(bullets[k])){
			bullets[k].state = BaseGameObject::DEAD;
		}
	}
}

bool checkBulletAsteroidCollision(const Vector2f point,const Asteroid & asteroid) {
	Vector2f relativePosition = point - asteroid.position;
	float theta = atan2f(relativePosition.y,relativePosition.x);
	int k;
	for(k = 1; k < ASTEROID_GRANULARITY; k++)if(asteroid.angles[k-1] < theta && asteroid.angles[k]){break;}
	Vector2f u = asteroid.vertices[k-1] - asteroid.position;
	Vector2f v = asteroid.vertices[k] - asteroid.position;
	
	return lineSegmentsIntersect(point,asteroid.position,u,v);
}

//shouldnt be in polygon branch
