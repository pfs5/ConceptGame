#pragma once
#include "GameObject.h"
#include "GameState.h"

#include <stack>

/**
	Handles all game state operations including adding and removing.
	Works with a stack mechanism. Also handles object instantiation by delegating 
	to the active state.
**/
class GameStateManager {
	static std::stack<GameState *> m_gameStates;
	static std::stack<GameObject*> m_newObjectsStack;
public:
	// Static methods
	/**
		Instantiate a new GameObject inside the active game state
	**/
	static GameObject * instantiate(GameObject *_gameObject);

	static GameObject * popNewGameObject();

	static void pushGameState(GameState *_state);
	static void popGameState();
	static GameState * activeGameState();
};