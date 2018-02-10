#include "PlayingState.h"
#include "Debug.h"
#include "Input.h"
#include "MainCharacter.h"

#include <SFML/Window.hpp>

PlayingState::PlayingState() {
	// Create main character
	GameObject * mainChar = new MainCharacter();
	m_gameObjects.push_back(mainChar);
}


PlayingState::~PlayingState() {
	// Destroy game objects
	for (GameObject * g : m_gameObjects) {
		delete g;
	}
}

void PlayingState::update(float _dt) {
	PhysicsEngine::getInstance().update(_dt);
	
	for (GameObject * g : m_gameObjects) {
		g->update(_dt);
	}
}

void PlayingState::draw() {
	for (GameObject * g : m_gameObjects) {
		g->draw();
	}

	PhysicsEngine::getInstance().draw();
}
