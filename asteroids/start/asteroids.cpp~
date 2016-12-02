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

	// TODO - check collisions ship-asteroids
	/*if(lineSegmentsIntersect(Vector2f(0,1),Vector2f(0,-1),Vector2f(-1,0),Vector2f(1,0))){
		printf("Checking basic T shape graph");
	}
	if(lineSegmentsIntersect(Vector2f(-5,5),Vector2f(10,5),Vector2f(5,-5),Vector2f(5,10))){
		printf("Checking basic T shape graph");
	}*/
/*for(int j = 0; j < bullets.size(); j++){
	for(int k = 0; k < asteroids.size();k++){
		if(checkBulletAsteroidCollision(bullets[j].position,asteroids[k])){printf("Bullet hit asteroid\n");}
	}
}*/
	for(int k = 0; k < asteroids.size();k++){
		if(checkBulletAsteroidCollision(ship.position,asteroids[k])){printf("Ship hit asteroid with ship position: %f,%f\n and asteroid position:%f,%f\n",ship.position.x,ship.position.y,asteroids[k].position.x,asteroids[k].position.y);}
	}

	
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

bool lineSegmentsIntersect(const Vector2f p, const Vector2f a,const Vector2f u, const Vector2f v){
	/*
		MAKE SIMPLE TEST (lineSegemntInterSect(point(0,1), point(0,-1), point (-1,0), point(1,0))) t = half and s = half
						 also try ()
		return true iff line segments a-p and u-v intersect
		
		calculate t
			float t = (p.y-a.y) * (v.x-a.x) - (p.x-a.x) * (v.y-a.y)/ (p.y-a.y) * (v.x - u.x) - (p.x - a.x) * (v.y - u.y);
			print (t)
			
			if(t < 0 || t > 1)return false;
			
		calculate s iff t is between 0 and 1
			float s = (abs(p.x-a.x) > abs(p.y-a.y)) ? (v.x-a.x)-(v.x-u.x)/p.x-a.x) : ((v.y-a.y - a.y-v.y) * t)/(p.y-a.y)
			print (s)
			return (0<=s && s<=1);
	
	*/
	float t = ((p.y-a.y) * (v.x-a.x) - (p.x-a.x) * (v.y-a.y)) / ((p.y-a.y) * (v.x - u.x) - (p.x - a.x) * (v.y - u.y));
	//printf("Printing t from lineSeg method : %.2f\n",t);
	if(t < 0 || t > 1)return false;
	float s = (std::abs(p.x-a.x) > std::abs(p.y-a.y)) ? ((v.x-a.x)-(v.x-u.x) / (p.x-a.x)) : ((v.y-a.y - a.y-v.y) * t)/(p.y-a.y);
	//printf("Printing s from lineSeg method : %.2f\n",s);
	return (s >= 0 && s <= 1);
}

