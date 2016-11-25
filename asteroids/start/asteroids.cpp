// ===============================================
// @file   asteroids.cpp
// @author kmurphy
// @practical asteroids
// @brief  Main file for PSP+GLFW asteroids game
// ===============================================

#include "asteroids.h"

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
				asteroid.size = 1.0f;
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

bool wrapGameObject(BaseGameObject & o) {

	// TODO - check if a game object is outside screen area and wrap it if needed.
	// TODO - return true if wraping was performed.
}

void update() {

	// TODO - update ship
	
	// TODO - update bullets

	// TODO - check collisions bullets-asteroids

	// TODO - check collisions ship-asteroids

	
	// TODO - update asteroids
	// If asteroids hit (state=dead) then generate two (or better random) number of smaller asteroids
	// new asteroids move off at random direction and rotation
	
	wrapGameObject(ship);
	
	//printf("Number of asteroids %d\n", asteroids.size());
	//printf("position %f %f\n", asteroids[0].position.x, asteroids[0].position.y);
}

bool checkBulletAsteroidCollision(Bullet & bullet, Asteroid & asteroid) {
	
	bool result = false;

	// TODO - check bullet-asteroid collision
	// basic implementation = ignore DEAD objects and rough test = point<->circle
	
	return result;
}

