#include "core.h"

#ifndef PSP

int initGraphics(const char * name) {
	
	glfwInit(); 
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if ( !glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 0,0,0,0,0,0, GLFW_WINDOW) ) { 
		glfwTerminate(); 
		std::cerr <<"glfwOpenWindow failed" <<std::endl;
		return 1; 
	}
	
	glfwSetWindowPos(100, 100);
	glfwSetWindowTitle(name);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0, ASPECT, 0, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();							// reset the model view matrix

	// timing information
    startTime = currentTime = glfwGetTime();

	return 0;		// success
	
}

int deinitGraphics() {
	glfwTerminate();
	return 0;		// success
}

void drawCircle(const Vector2f c, float r) {
	glPushMatrix();
	glTranslatef(c.x, c.y, 0);
	glBegin(GL_LINE_LOOP);
	for(int k=0; k<100; ++k) {
		float rad = 2*PI*k/100;
		glVertex3f(r*cos(rad), r*sin(rad), 0);
	}
	glEnd();
	glPopMatrix();
}

void drawRectangle(Vector2f position, float width, float height){
	glPushMatrix();
	glTranslatef(position.x,position.y,0);
	glScalef(width,height,1);
	glBegin(GL_QUADS);      
   		glVertex3f(0.0, 0.0, 0.0);
    	glVertex3f(1.0, 0.0, 0.0);
    	glVertex3f(1.0, 1.0, 0.0);
    	glVertex3f(0.0, 1.0, 0.0);
    glEnd();
	glPopMatrix();
}



#endif
