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

	static std::vector<std::stack<GameObject*>> m_newObjectsStacks;
public:
	static const int objectLayers = 2;

	// Static methods
	/**
		Instantiate a new GameObject inside the active game state
	**/
	static GameObject * instantiate(GameObject *_gameObject, int _layer = 0);

	static GameObject * popNewGameObject(int _layer = 0);

	static void pushGameState(GameState *_state);
	static void popGameState();
	static GameState * activeGameState();
};