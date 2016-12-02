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
				asteroid.type = Asteroid::LARGE;				// FOR TESTING REMOVE THIS LINE WHEN DONE
				asteroid.reset();
				asteroid.position = Vector2f(ASPECT/1.5,0.5f);
				asteroid.size = sizes[asteroid.type];
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

	// TODO - update asteroids
	// If asteroids hit (state=dead) then generate two (or better random) number of smaller asteroids
	// new asteroids move off at random direction and rotation
	for(int k = 0; k < asteroids.size();k++) asteroids[k].update(dt);
	wrapGameObject(ship);
	
	//check collisions
	checkCollisions();
	
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
	return isPointInsideCircle(point,asteroid.position,asteroid.radius * ASTEROID_SCALE);
}

bool isPointInsideCircle(const Vector2f point,const Vector2f center,const float radius){
	//printf("X Distance from circle: %.2f\n",sqr(point.x - center.x));
	//printf("Y Distance from circle: %.2f\n",sqr(point.y - center.y));
	// printf("Radius squared: %.2f\n",sqr(radius));
	return sqr(point.x - center.x) + sqr(point.y - center.y) < sqr(radius);
}

void checkCollisions(){
	//check ship collision with asteroids
	for(int k = 0; k < asteroids.size();k++){
		if(isPointInsideCircle(ship.position,asteroids[k].position,asteroids[k].radius * ASTEROID_SCALE)){printf("Collision occured, Ship with Asteroid\n");}
	}
	
	// check collisions bullets-asteroids
	for(int j = 0; j < bullets.size();j++){
		for(int k = 0; k < asteroids.size();k++){
			if(checkBulletAsteroidCollision(bullets[j].position,asteroids[k]) ){
				printf("Collision occured, Bullet with Asteroid\n");
				bullets[j].state = BaseGameObject::DEAD;
				destroyAsteroid(asteroids[k],k);         
			}
		}
	}
}

void destroyAsteroid(Asteroid & asteroid,const int index){
	if(asteroid.type == Asteroid::TINY){
		asteroids.free(index);										//free index no more types left for this asteroid (fully destroyed)
	}else{
		asteroid.state = Asteroid::DEAD;							//set state to dead
		Asteroid tempAsteroid = asteroid;							//make temp asteroid to set values for new asteroids
		asteroids.free(index);
		createAsteroid(tempAsteroid.position,tempAsteroid.type+1);	//create an asteroid at this position
		createAsteroid(tempAsteroid.position,tempAsteroid.type+1);	
	}
}

void createAsteroid(const Vector2f position,const int type){
	printf("Type is going to be: %d\n",type);
	Asteroid & asteroid = asteroids.allocate();
	asteroid.reset();
	asteroid.position = position;
	asteroid.type = static_cast<Asteroid::Type>(type);
	asteroid.size = sizes[asteroid.type];
	
	printf("Spawned new asteroid at position %.1f,%.1f\nOf size: %.2f\n",asteroid.position.x,asteroid.position.y,asteroid.size);
}
