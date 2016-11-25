#ifndef CORE_H
#define CORE_H

// ===============================================
// Headers
// ===============================================
#ifdef PSP								// system specific headers
#else 									  
	#ifdef _WIN32   						// Windows system specific
		#include <GL/glfw.h>
	#else
	    #ifdef __APPLE__                // OS X
    		#include <GL/gl.h>
	    	#include <GL/glu.h>
	    	#include <GL/freeglut.h>
	    	#include <GL/glfw.h>
	    #else				            // linux
		    #include <GL/gl.h>
	    	#include <GL/glu.h>
		    #include <GL/freeglut.h>
		    #include <GL/glfw.h>
	    #endif
	#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

#include <string>
#include <iostream>

#include "Vector2f.h"

// ===============================================
// Global identifiers
// ===============================================

// screen 
extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
extern const float SCALE, ASPECT;

// state for main game loop
enum GameState {GAME_INTRO, GAME_START, LEVEL_START, LEVEL_PLAY, LEVEL_OVER, GAME_OVER, GAME_QUIT};
extern GameState gameState;

extern const char * GAME_STATE_NAMES[];

// frame timing information
extern double startTime, currentTime, previousTime, dt;

// ===============================================
// Function prototypes
// ===============================================
void changeGameState(GameState newState);

int initGraphics(const char * name);
int deinitGraphics();
void render();
void update();
void getInput();

void drawCircle(const Vector2f c = Vector2f::ZERO, float r=1.0f);
#endif