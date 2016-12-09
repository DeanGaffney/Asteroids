#include "asteroids.h"

void render() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);
    
	ship.render();
	
	for (int k=0; k<bullets.size(); ++k)bullets[k].render();

	for (int k=0; k<asteroids.size(); ++k)asteroids[k].render();
	
	for(int k=0; k<powerups.size();++k)powerups[k].render();
	
	drawHealthBar();
	glfwSwapBuffers(); 
	
	// update frame timer
	previousTime = currentTime;
	currentTime = glfwGetTime();
	dt = clamp(currentTime - previousTime, 0.01, 0.1);

}


void drawHealthBar(){
	glPushMatrix();
	glColor3ub(255,0, 0);
	drawRectangle(Vector2f(0,0.0),HEALTH_BAR_WIDTH,0.05);

	glColor3ub(0,255, 0);
	drawRectangle(Vector2f(0,0.0),(HEALTH_BAR_WIDTH * ship.health) / 100,0.05);
	glPopMatrix();
}

void Powerup::render(){
	setPowerupColor(type);
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glScalef(POWERUP_SCALE*size, POWERUP_SCALE*size, 1);
	glRotatef(angle, 0,0,1);
		drawCircle(Vector2f::ZERO,size);
	glPopMatrix();
}

void setPowerupColor(const Powerup::Type type){
	if(type == Powerup::HEALTH)glColor3f(0,1,0);			//health is green
	else if(type == Powerup::AMMO)glColor3f(1,1,0);		//ammo is yellow
	else if(type == Powerup::REPEL)glColor3f(1,0,0);	//repel is red
	else if(type == Powerup::SHIELD)glColor3f(0,0,1);	//teleport is blue
}

void Ship::render() {
    glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glScalef(0.004, 0.003, 1);
	glRotatef(angle, 0,0,1);

	glBegin(GL_QUADS);		
		glVertex3f(12, 0, 0);
		glVertex3f(-5, 5, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(12, 0, 0);
		glVertex3f(-5, -5, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 0);
    glEnd();	
	glPopMatrix();
	
	//draw shield relative to ship position
	if(isShieldActive){
		glPushMatrix();
			glTranslatef(position.x, position.y, 0);
			glScalef(SHIP_SHIELD_SCALE * shieldSize, SHIP_SHIELD_SCALE * shieldSize, 1);
    		glColor3ub(255,153, 51);	
    		drawCircle(Vector2f::ZERO,shieldSize);
		glPopMatrix();
	}
}

void Bullet::render() {
    glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glRotatef(angle, 0,0,1);
	glScalef(0.04, 0.04, 1);

	glBegin(GL_QUADS);		
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, .1, 0);
		glVertex3f(0, .1, 0);
    glEnd();	
	glPopMatrix();
}

void Asteroid::render () {
    glColor3f(1,1,1);
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glScalef(ASTEROID_SCALE*size, ASTEROID_SCALE*size, 1);
	glRotatef(angle, 0,0,1);
	glBegin(GL_TRIANGLE_FAN);	
		for (int k=0; k<ASTEROID_GRANULARITY; ++k) {
			glVertex3f(vertices[k].x,vertices[k].y, 0);
		}
    glEnd();

	drawCircle(Vector2f::ZERO,size);

	glPopMatrix();	
}
void getInput() {

	if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED)) {
		gameState = GAME_QUIT;
		return;
	}

    if (glfwGetKey('R')) {
		ship.reset();
    }
	
	if(!ship.autoNavigation){
    	ship.acceleration = Vector2f::ZERO;
		if (glfwGetKey(GLFW_KEY_UP)) {
			float rad = degToRad(ship.angle);
			ship.acceleration = SHIP_MAX_ACCELERATION*Vector2f(cos(rad),sin(rad));
    	} else if (glfwGetKey(GLFW_KEY_DOWN)) {
			ship.velocity *= 0.1f;
		}
	
    	if (glfwGetKey(GLFW_KEY_LEFT)) {
			ship.angularVelocity = SHIP_MAX_ANGULAR_VELOCITY;
    	} else if (glfwGetKey(GLFW_KEY_RIGHT)) {
			ship.angularVelocity = -SHIP_MAX_ANGULAR_VELOCITY;
    	} else{
			ship.angularVelocity = 0;
		}
 
		ship.fire = glfwGetKey(GLFW_KEY_SPACE);
	}
	//toggle auto navigation
	if(glfwGetKey('A'))ship.autoNavigation = !ship.autoNavigation;
	
}
