#pragma once

/**
	Holds global game settings and parameters.
**/
namespace GameSettings {
	// Debug outputs
	const bool PRINT_FPS = true;
	const bool SHOW_COLLIDERS = true;

	// Physics
	const float GLOBAL_SCALE = 1e2;	// how many meters is one unit in the game (screen)
	const float GRAVITY = 9.81f * GLOBAL_SCALE;
}