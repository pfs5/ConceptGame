#include "GameStateManager.h"

std::stack<GameState *> GameStateManager::m_gameStates;
std::stack<GameObject*> GameStateManager::m_newObjectsStack;


GameObject * GameStateManager::instantiate(GameObject * _gameObject) {
	GameObject * o =  activeGameState()->instantiateObject(_gameObject);
	m_newObjectsStack.push(o);

	return o;
}

GameObject * GameStateManager::popNewGameObject() {
	if (m_newObjectsStack.empty()) {
		return nullptr;
	}

	GameObject * o = m_newObjectsStack.top();
	m_newObjectsStack.pop();
	return o;
}

void GameStateManager::pushGameState(GameState * _state) {
	m_gameStates.push(_state);
}

GameState * GameStateManager::popGameState() {
	return m_gameStates.top();
	m_gameStates.pop();
}

GameState * GameStateManager::activeGameState() {
	if (m_gameStates.empty()) {
		return nullptr;
	}
	return m_gameStates.top();
}
