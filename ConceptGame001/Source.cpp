#include <iostream>
#include <cstdio>

#include "Application.h"
#include "PlayingState.h"

#include <SFML/Graphics.hpp>

int main() {
	Application app;
	PlayingState *playState = new PlayingState();

	app.addGameState(playState);

	app.runMainLoop();

	return 0;
}