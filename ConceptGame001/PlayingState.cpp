#include "PlayingState.h"
#include "Debug.h"
#include "Input.h"
#include "MainCharacter.h"
#include "CubeObject.h"

#include <SFML/Window.hpp>

void createCube(sf::Vector2i _pos, std::vector<GameObject*> &_gameObjects) {
	GameObject * cube = new CubeObject(sf::Vector2f{ 50, 50 }, sf::Vector2f{ static_cast<float>(_pos.x - 25), static_cast<float>(_pos.y - 25) }, false, true);
	_gameObjects.push_back(cube);
}

PlayingState::PlayingState() {
	// Create main character
	GameObject * mainChar = new MainCharacter();
	m_gameObjects.push_back(mainChar);

	// Dummy objects
	//GameObject * cube = new CubeObject(sf::Vector2f{ 100, 100 }, sf::Vector2f{ 200, 200 }, false, true);
	//m_gameObjects.push_back(cube);

	GameObject * wallR = new CubeObject(sf::Vector2f{ 100, 400 }, sf::Vector2f{ 500, 100 }, true);
	m_gameObjects.push_back(wallR);

	// Floor
	GameObject * floor = new CubeObject(sf::Vector2f{ 1000, 50 }, sf::Vector2f{ 0, 500 }, true);
	m_gameObjects.push_back(floor);
}


PlayingState::~PlayingState() {
	// Destroy game objects
	for (GameObject * g : m_gameObjects) {
		delete g;
	}
}

void PlayingState::update(float _dt) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		}
		createCube(sf::Mouse::getPosition(Display::getWindow()), m_gameObjects);

	}
	for (GameObject * g : m_gameObjects) {
		g->update(_dt);
	}

	PhysicsEngine::getInstance().update(_dt);
}

void PlayingState::draw() {
	for (GameObject * g : m_gameObjects) {
		g->draw();
	}

	PhysicsEngine::getInstance().draw();
}