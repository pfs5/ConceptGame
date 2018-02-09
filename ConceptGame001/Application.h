#pragma once

#include <stack>

#include "GameState.h"

class Application {
	std::stack<GameState*> m_gameStates;
public:
	Application();
	~Application();

	/**
	Runs the main game loop
	**/
	void runMainLoop();

	/**
	Adds a game state to the application
	@param _gameState pointer to gamestate allocated on dynamic storage.
	Application handles memory deallocation.
	**/
	void addGameState(GameState *_gameState);
};