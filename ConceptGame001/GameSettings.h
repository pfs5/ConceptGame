#pragma once
namespace GameSettings {
	// Debug outputs
	const bool PRINT_FPS = true;
	const bool SHOW_COLLIDERS = true;

	// Physics
	const float GLOBAL_SCALE = 5 * 1e3;	// how many meters is one unit in the game (screen)
	const float GRAVITY = 9.81f * GLOBAL_SCALE;
}