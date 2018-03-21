#include <iostream>
#include <cstdio>

#include "Application.h"
#include "PlayingState.h"
#include "MenuState.h"

#include <SFML/Graphics.hpp>

int main() {
	Application app;
	
	app.addGameState(new MenuState());

	app.runMainLoop();

	return 0;
}