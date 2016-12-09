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
PowerupPool powerups(200);
float powerupSpawnTime = POWERUP_SPAWN_TIME;
float asteroidSpawnTime = ASTEROID_SPAWN_TIME;

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
				ship.isShieldActive = true;				//FOR DEBUGGING REMOVE WHEN DONE
				spawnAsteroid();
				//for(int k=randomInt(1,20); k; --k)spawnAsteroid();
				spawnPowerup();
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
	for(int k = 0; k < asteroids.size();k++) asteroids[k].update(dt);
	
	//update powerups
	for(int k = 0; k < powerups.size();k++)powerups[k].update(dt);
	wrapGameObject(ship);
	
	//check collisions
	checkCollisions();
	
	//cull game objects
	cullObjects();
	
	//have a timer to spawn asteroids if there are none left to keep the game ongoing if the player is alive
	asteroidSpawnTime -= dt;
	if(asteroidSpawnTime <= 0 && asteroids.isEmpty()){
		spawnAsteroid();
		asteroidSpawnTime = ASTEROID_SPAWN_TIME;
	}else if(asteroidSpawnTime <= 0){
		asteroidSpawnTime = ASTEROID_SPAWN_TIME;
	}
	
	//have a timer to calculate have a chance in spawning powerup as player may be out of bullets
	powerupSpawnTime -= dt;
	if(powerupSpawnTime <= 0){
		spawnPowerup();
		powerupSpawnTime = POWERUP_SPAWN_TIME;
	}else if(powerupSpawnTime <= 0){
		powerupSpawnTime = POWERUP_SPAWN_TIME;
	}
	
}

void cullObjects(){
	//cull ship bullets
	for(int k = bullets.size();--k >= 0;){
		if(bullets[k].state == BaseGameObject::DEAD)bullets.free(k);
		else if(wrapGameObject(bullets[k])){
			bullets[k].state = BaseGameObject::DEAD;
		}
	}
	
	//cull powerups that have died due to time expiring
	for(int k = 0; k < powerups.size(); k++){
		if(powerups[k].state == BaseGameObject::DEAD)powerups.free(k);
	}
}

bool checkBulletAsteroidCollision(const Vector2f point,const Asteroid & asteroid) {
	return isPointInsideCircle(point,asteroid.position,asteroid.radius * ASTEROID_SCALE);
}

bool isPointInsideCircle(const Vector2f point,const Vector2f center,const float radius){
	return sqr(point.x - center.x) + sqr(point.y - center.y) < sqr(radius);
}

bool circleCollision(const float distance, const float radius1, const float radius2){
	return (radius1 + radius2 > distance) ? true : false;
}

bool isMovingTowardsPoint(const Vector2f point, const Vector2f objectPos, const Vector2f objectVelocity){
	Vector2f toPoint = point - objectPos; 			//a vector going from obect to the point
    return dot(toPoint, objectVelocity) > 0;
}

void checkCollisions(){

	//check ship collision with asteroids
	for(int k = 0; k < asteroids.size();k++){
		if(isPointInsideCircle(ship.position,asteroids[k].position,asteroids[k].radius * ASTEROID_SCALE) && !ship.isTakingDamage()){
			printf("Collision occured, Ship with Asteroid\n");
			ship.damageRecoveryTimer = SHIP_RECOVERY_TIME;
			ship.health -= 10;
			destroyAsteroid(asteroids[k],k);
		}
	}
	
	//check ship bullets collision with powerups
	for(int j =0; j < bullets.size();j++){
		for(int k=0; k < powerups.size();k++){
			if(isPointInsideCircle(bullets[j].position,powerups[k].position,powerups[k].radius * POWERUP_SCALE)){
				printf("Collision occured, Bullet with Powerup\n");
				triggerPowerup(powerups[k]);
				powerups[k].state = BaseGameObject::DEAD;
			}
		}
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
	
	//deal with asteroids hititng ship shield
	if(ship.isShieldActive){
		//check circle on circle collision
		for(int k = 0; k < asteroids.size(); k++){
			if(circleCollision((ship.position - asteroids[k].position).length(),ship.shieldSize * SHIP_SHIELD_SCALE,asteroids[k].size * ASTEROID_SCALE)
								&& isMovingTowardsPoint(ship.position,asteroids[k].position,asteroids[k].velocity)){
				printf("Asteroid collidied with ship shield\n");
				asteroids[k].velocity = (asteroids[k].position - ship.position).normal() * ASTEROID_MAX_SPEED;
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
		const int randomNumOfAsteroids = randomInt(MIN_ASTEROIDS_SPAWNABLE,MAX_ASTEROIDS_SPAWNABLE);
		for(int k = 0; k < randomNumOfAsteroids; k++){
			spawnAsteroid(tempAsteroid.position,tempAsteroid.type+1);	//create an asteroid at this position *CHANGE THIS TO RANDOM NUMBER*
		}
	}
	//calculate chance of spawning a powerup
	if(canSpawnPowerup(10))spawnPowerup();
}

void spawnAsteroid(const Vector2f position,const int type){
	Asteroid & asteroid = asteroids.allocate();
	asteroid.reset();
	asteroid.position = position;
	asteroid.type = static_cast<Asteroid::Type>(type);
	asteroid.size = sizes[asteroid.type];
}

void spawnAsteroid(){
	Asteroid & asteroid = asteroids.allocate();
	asteroid.type = Asteroid::LARGE;				// FOR TESTING REMOVE THIS LINE WHEN DONE
	asteroid.reset();
	asteroid.position = Vector2f(randomFloat(ASPECT - ASPECT + 0.2,ASPECT - 0.2),randomFloat(0.1,0.9));
	asteroid.size = sizes[asteroid.type];
}

bool canSpawnPowerup(const int chance){
	return (randomInt(0,chance) > chance - 2);			//TWEAK THIS FOR CHANCE OF SPAWNING POWERUP
}

void spawnPowerup(){
	Powerup & powerup = powerups.allocate();
	powerup.reset();
	powerup.position = Vector2f(randomFloat(ASPECT - ASPECT + 0.2,ASPECT - 0.2),randomFloat(0.1,0.9));
	const int typeIndex = randomInt(0,MAX_POWERUP_TYPES);
	powerup.type = static_cast<Powerup::Type>(typeIndex);
}

void triggerPowerup(Powerup & powerup){
	if(powerup.type == Powerup::HEALTH)powerup.giveShipHealth(ship);
	else if(powerup.type == Powerup::AMMO)powerup.giveShipBullets(ship);
	else if(powerup.type == Powerup::REPEL)powerup.repelAsteroids(ship);
	else if(powerup.type == Powerup::SHIELD)powerup.giveShipShield(ship);
}
