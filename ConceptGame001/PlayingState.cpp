#include "PlayingState.h"
#include "Debug.h"
#include "Input.h"
#include "MainCharacter.h"
#include "CubeObject.h"
#include "Arrow.h"
#include "GameStateManager.h"
#include "PauseState.h"

#include <SFML/Window.hpp>

void createCube(sf::Vector2i _pos, std::vector<GameObject*> &_gameObjects) {
	GameObject * cube = new CubeObject(sf::Vector2f{ 50, 50 }, sf::Vector2f{ static_cast<float>(_pos.x - 25), static_cast<float>(_pos.y - 25) }, false, true);
	_gameObjects.push_back(cube);
}

PlayingState::PlayingState() {
	// ### View setup ###
	m_view.reset(sf::FloatRect(0.f, 0.f, Display::getWindow().getSize().x, Display::getWindow().getSize().y));

	// ### Create main character ###
	GameObject * arrow = new Arrow();
	arrow->setActive(false);

	GameObject * mainChar = new MainCharacter(arrow);
	m_gameObjects.push_back(mainChar);
	m_centeredObject = mainChar;

	m_viewOffset = sf::Vector2f{ 0.f, -1.f * Display::getWindow().getSize().y / 2.f + VERTICAL_VIEW_OFFSET};

	// Dummy objects
	//GameObject * cube = new CubeObject(sf::Vector2f{ 100, 100 }, sf::Vector2f{ 200, 200 }, false, true);
	//m_gameObjects.push_back(cube);

	GameObject * wallL = new CubeObject(sf::Vector2f{ 100, 400 }, sf::Vector2f{ 500, 300 }, true);
	m_gameObjects.push_back(wallL);

	GameObject * wallR = new CubeObject(sf::Vector2f{ 100, 400 }, sf::Vector2f{ 1500, 300 }, true);
	m_gameObjects.push_back(wallR);

	// Floor
	GameObject * floor = new CubeObject(sf::Vector2f{ 2000, 50 }, sf::Vector2f{ 500, 500 }, true);
	m_gameObjects.push_back(floor);
}


PlayingState::~PlayingState() {
	// Destroy game objects
	for (GameObject * g : m_gameObjects) {
		delete g;
	}
}

void PlayingState::update(float _dt) {
	for (GameObject * g : m_gameObjects) {
		if (g->isActive()) {
			g->update(_dt);
		}
	}

	PhysicsEngine::getInstance().update(_dt);

	// Make view follow the centered object
	m_view.setCenter(m_centeredObject->getPosition() + m_viewOffset);

	// Add new objects
	GameObject * newObj = nullptr;
	while (newObj = GameStateManager::popNewGameObject()) {
		m_gameObjects.push_back(newObj);
	}

	// Pause game
	if (Input::getKeyDown(Input::P)) {
		GameStateManager::pushGameState(new PauseState());
	}
}

void PlayingState::draw() {
	Display::getWindow().setView(m_view);

	for (GameObject * g : m_gameObjects) {
		if (g->isActive()) {
			g->draw();
		}
	}

	PhysicsEngine::getInstance().draw();
}

GameObject * PlayingState::instantiateObject(GameObject * _gameObject) {
	GameObject * newInstance = _gameObject->clone();

	return newInstance;
}
