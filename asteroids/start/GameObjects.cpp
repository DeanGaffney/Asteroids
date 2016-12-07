#include "asteroids.h"
#include "GameObjects.h"
#include <cmath>
// ======================================
// BaseGameObject
// ======================================
 
void BaseGameObject::update(float dt) {
	// linear movement
	velocity += dt*acceleration;
	position += dt*velocity;
	velocity *= pow(damping, dt);
	
	//anglular movement
	angle += dt*angularVelocity;
}

void BaseGameObject::reset() {
	state = BaseGameObject::ALIVE;
	velocity = Vector2f::ZERO;
	position = Vector2f::ZERO;
	acceleration = Vector2f::ZERO;
	angle = 0;
	angularVelocity = 0;
	damping = 1;
	radius = 1;
	spawnInvincibilityTime = SPAWN_INVINCIBILITY_TIME;
}

void BaseGameObject::wrap(){
	//see if need to wrap game object
	if(position.x > ASPECT)position.x = 0.1;
	else if(position.x < 0) position.x = ASPECT - 0.1;
	else if(position.y > 1)position.y = 0.1;
	else if(position.y < 0)position.y = 0.9;
}


// ======================================
// Ship
// ======================================

void Ship::reset() {
	BaseGameObject::reset();
	
	autoNavigation = true;
	activity = Ship::FIGHT;
	
	hasTarget = false;
	
	position = Vector2f(ASPECT/2,0.5);
	damping = 0.8;
	
	timeToFire = 0;
	
	health = SHIP_MAX_HEALTH;
	bulletsRemaining = SHIP_MAX_BULLETS;
	
	//set up shield
	shieldTimer = SHIP_SHIELD_TIME;
	isShieldActive = false;
	shieldSize = SHIP_SHIELD_SIZE;
	
	damageRecoveryTimer = 0;
}

void Ship::update(float dt) {
	// TODO - update position (using base class)
	BaseGameObject::update(dt);

	if(autoNavigation){
		ship.fire = true;
		
		//FIGHT ASTEROIDS
		if(activity == Ship::FIGHT && !asteroids.isEmpty()){
			//printf("Ship is fighting\n");
		//the reason i use index 0 is becasue the Pool class will always replace a dead index so 0 will always be used unless all asteroids are destroyed
			float angleToRotate = atan2f(asteroids[0].position.y - position.y,asteroids[0].position.x - position.x);
			angle = radToDeg(angleToRotate);
			if(isAllowedFire())fireBullet();
			else timeToFire -= dt;
			
			if(bulletsRemaining <= 5 && !powerups.isEmpty())activity = Ship::AMMO;
			else if(health <= SHIP_MAX_HEALTH / 2 && !powerups.isEmpty())activity = Ship::HEALTH;
			
			//SCAVENGE AMMO
		}else if(activity == Ship::AMMO){
			printf("Ship is searching for ammo\n");
			printf("Bullets remaining: %d\n",bulletsRemaining);
			angle = getAngleToPowerup(Ship::AMMO);
			printf("Angle to rotate to ammo is : %f\n",angle);
			if(isAllowedFire())fireBullet();
			else timeToFire -= dt;
			if(bulletsRemaining > 5)activity = Ship::FIGHT;
			else if(health <= SHIP_MAX_HEALTH / 2 && !powerups.isEmpty())activity = Ship::HEALTH;
			
			//SCAVENGE HEALTH
		}else if(activity == Ship::HEALTH){
			printf("Ship is searching for health\n");
			angle = getAngleToPowerup(Ship::HEALTH);
			if(isAllowedFire())fireBullet();
			else timeToFire -= dt;
			if(health > SHIP_MAX_HEALTH / 2)activity = Ship::FIGHT;
			else if(bulletsRemaining <= 5 && !powerups.isEmpty())activity = Ship::AMMO;			
		}
		
	}else{
	//deals with manual firing
		if(isAllowedFire())fireBullet();
		else timeToFire -= dt;
	}
	
	//wrap game object
	wrap();
	
	//check if shield is active
	if(isShieldActive && shieldTimer > 0){
		shieldTimer -= dt;
	}else if(isShieldActive && shieldTimer <=0){
		isShieldActive = false;
		shieldTimer = SHIP_SHIELD_TIME;
	}
	if(damageRecoveryTimer > 0 )damageRecoveryTimer -= dt;
}

/*
	returns the closest distance for a player to the nearset powerup type
*/
float Ship::getAngleToPowerup(const int type){
	float angleToRotate = 0;
	for(int k = 0; k < powerups.size();k++){
		if(type == powerups[k].type){
			angleToRotate = atan2f(powerups[k].position.y - position.y,powerups[k].position.x - position.x);
		}
	}
	return radToDeg(angleToRotate);
}

void Ship::fireBullet(){
	timeToFire = SHIP_FIRE_DELAY;
	bulletsRemaining--;
	printf("Bullets remaining %d\n",bulletsRemaining);
	Bullet & bullet = bullets.allocate();
	bullet.reset();
	bullet.position = position;
	bullet.velocity = Vector2f(cos(degToRad(angle)),sin(degToRad(angle)));
	bullet.angle = angle;
}

bool Ship::isAllowedFire(){
	return (fire && timeToFire <= 0 && bulletsRemaining > 0);	
}

void Ship::wrap(){
	BaseGameObject::wrap();
}

bool Ship::isTakingDamage(){
	return damageRecoveryTimer > 0;
}

// ======================================
// Bullet
// ======================================

void Bullet::reset() {
	// TODO - reset start (using base class),  and reset time left to die.
	BaseGameObject::reset();
	
	timeToDie = BULLET_DIE_DELAY;
}

void Bullet::update(float dt) {
	// TODO - update position (using base class), update and check time left to die.
	BaseGameObject::update(dt);
	
}

// ======================================
// Asteroid
// ======================================

void Asteroid::reset() {
	BaseGameObject::reset();

	float vertexAngle = 360 / ASTEROID_GRANULARITY;
	// TODO - create random asteroid as outlined in class
	for(int k = 0; k < ASTEROID_GRANULARITY; ++k){
		float randomPoint = randomFloat(ASTEROID_MIN_RADIUS,ASTEROID_MAX_RADIUS);
		vertexAngle += ((360/ASTEROID_GRANULARITY) + randomFloat(-1,1) * ASTEROID_ANGLE_VARABILITY);
		angles[k] = vertexAngle;
		vertices[k].x = randomPoint * cos(vertexAngle);
		vertices[k].y = randomPoint * sin(vertexAngle);
	}
	// TODO - random rotation angle 
	angularVelocity = randomFloat(-100,100);
	
	angle = randomFloat(1,360);
	
	//random velocity based off random angle
	velocity = Vector2f(cos(degToRad(angle)),sin(degToRad(angle))).normal() * randomFloat(ASTEROID_MIN_SPEED,ASTEROID_MAX_SPEED);
}

void Asteroid::update(float dt) {
	BaseGameObject::update(dt);
	
	//wrap asteroid 
  	wrap();
}

int Asteroid::getEnumIndex(){
	for(int k = 0; k < MAX_ENUM_TYPE; k++)if(type == k){return k;}
}

void Asteroid::wrap(){
	BaseGameObject::wrap();
}

void Powerup::update(float dt){
	BaseGameObject::update(dt);
	wrap();
	
	timeToDie -= dt;
	if(timeToDie <= 0)state = BaseGameObject::DEAD;
}

void Powerup::reset(){
	BaseGameObject::reset();
	
	//reset time to die
	timeToDie = POWERUP_EXPIRE_TIME;
	
	size = POWERUP_SIZE;
	
	// random rotation angle 
	angularVelocity = randomFloat(-100,100);
	
	angle = randomFloat(1,360);
	
	//random velocity based off random angle
	velocity = Vector2f(cos(degToRad(angle)),sin(degToRad(angle))).normal() * randomFloat(POWERUP_MIN_SPEED,POWERUP_MAX_SPEED);
	
}

void Powerup::wrap(){
	BaseGameObject::wrap();
}

void Powerup::giveShipHealth(Ship & ship){
	if(ship.health == SHIP_MAX_HEALTH)return;
	ship.health += SHIP_MAX_HEALTH - ship.health;
}

void Powerup::giveShipBullets(Ship & ship){
	ship.bulletsRemaining = (ship.bulletsRemaining + 20 > SHIP_MAX_BULLETS) ? ship.bulletsRemaining += SHIP_MAX_BULLETS - ship.bulletsRemaining
																		  : ship.bulletsRemaining + 20;
}

void Powerup::repelAsteroids(Ship & ship){
	//calculate asteroid distance from ship position as velocity vector, normalised to avoid speed boosts
	for(int k=0;k<asteroids.size();k++){
		asteroids[k].velocity = (asteroids[k].position - ship.position).normal() * randomFloat(ASTEROID_MIN_SPEED,ASTEROID_MAX_SPEED);
	}
}

void Powerup::giveShipShield(Ship & ship){
	printf("Shield activated on ship\n");
	//activate shield in player
	ship.isShieldActive = true;
}

