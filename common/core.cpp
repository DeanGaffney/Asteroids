#include "core.h"

// ===============================================
// Global identifiers
// ===============================================

// screen 
// We want same screen coordinates on both the PSP and GLFW
// Picked 2D coordinates: (0,0) on lower left to (ASPECT,1) on upper right
#ifdef PSP								
	const float SCALE = 1;
	const int WINDOW_WIDTH = SCEGU_SCR_WIDTH;  // 480
	const int WINDOW_HEIGHT = SCEGU_SCR_HEIGHT; // 272
#else
	const float SCALE = 2;
	const int WINDOW_WIDTH = int (480*SCALE);
	const int WINDOW_HEIGHT = int (272*SCALE);
#endif
const float ASPECT = float(WINDOW_WIDTH)/float(WINDOW_HEIGHT);

// state for main game loop
GameState gameState = GAME_INTRO;
const char * GAME_STATE_NAMES[7] = {"GAME_INTRO", "GAME_START", "LEVEL_START", "LEVEL_PLAY", "LEVEL_OVER", "GAME_OVER", "GAME_QUIT"};

// frame timing information
double startTime, currentTime, previousTime, dt;


// ===============================================
// platform independent functions
// ===============================================
void changeGameState(GameState newState) {
	printf ("Game state %s -> %s\n", GAME_STATE_NAMES[gameState],GAME_STATE_NAMES[newState]);
	gameState = newState;
}


