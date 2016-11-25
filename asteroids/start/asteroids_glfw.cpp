#include "asteroids.h"

void render() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);
    
	ship.render();
	
	for (int k=0; k<bullets.size(); ++k) bullets[k].render();

	for (int k=0; k<asteroids.size(); ++k) asteroids[k].render();
	
	glfwSwapBuffers(); 

	// update frame timer
	previousTime = currentTime;
	currentTime = glfwGetTime();
	dt = clamp(currentTime - previousTime, 0.01, 0.1);

}

void Ship::render() {

    glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glScalef(0.004, 0.003, 1);
	glRotatef(angle, 0,0,1);
	//glColor3ub(0,200, 0);	
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
}

void Bullet::render() {

    glColor3f(1,0,0);
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glRotatef(angle, 0,0,1);
	glScalef(0.04, 0.04, 1);
	printf("angle = %f\n", angle);

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

	drawCircle();

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
	
    ship.acceleration = Vector2f::ZERO;
	if (glfwGetKey(GLFW_KEY_UP)) {
		float rad = degToRad(ship.angle);
		ship.acceleration = SHIP_MAX_ACCELERATION*Vector2f(cos(rad),sin(rad));
    } else if (glfwGetKey(GLFW_KEY_DOWN)) {
		ship.velocity *= 0.5f;
	}
	
    if (glfwGetKey(GLFW_KEY_LEFT)) {
		ship.angularVelocity = SHIP_MAX_ANGULAR_VELOCITY;
    } else if (glfwGetKey(GLFW_KEY_RIGHT)) {
		ship.angularVelocity = -SHIP_MAX_ANGULAR_VELOCITY;
    } else {
		ship.angularVelocity = 0;
	}
 
	ship.fire = glfwGetKey(GLFW_KEY_SPACE);
	
}
