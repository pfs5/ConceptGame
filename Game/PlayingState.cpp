#include "PlayingState.h"
#include "Debug.h"
#include "Input.h"
#include "MainCharacter.h"
#include "CubeObject.h"
#include "GameStateManager.h"
#include "PauseState.h"
#include "TexturedCubeObject.h"
#include "Projectile.h"
#include "EnemyManager.h"
#include "BasicEnemy.h"
#include "RangedEnemy.h"

#include <SFML/Window.hpp>

void createCube(sf::Vector2i _pos, std::vector<GameObject*> &_gameObjects) {
	GameObject * cube = new CubeObject(sf::Vector2f{ 50, 50 }, sf::Vector2f{ static_cast<float>(_pos.x - 25), static_cast<float>(_pos.y - 25) }, false, true);
	_gameObjects.push_back(cube);
}

PlayingState::PlayingState() {
	// ### Game objects setup ###
	for (int i = 0; i < GameStateManager::objectLayers; ++i) {
		m_gameObjects.push_back(std::vector<GameObject*>());
	}

	// ### View setup ###
	m_view.reset(sf::FloatRect(0.f, 0.f, Display::getWindow().getSize().x, Display::getWindow().getSize().y));

	// ### Create main character ###
	GameObject * projectile = new Projectile();
	GameObject * mainChar = new MainCharacter(projectile);
	m_gameObjects[0].push_back(mainChar);
	m_centeredObject = mainChar;

	m_viewOffset = sf::Vector2f{ 0.f, -1.f * Display::getWindow().getSize().y / 2.f + VERTICAL_VIEW_OFFSET};

	// ### Enemies ###
	GameObject *enemy = new BasicEnemy();
	GameObject *rangedEnemy = new RangedEnemy();

	m_gameObjects[0].push_back(new EnemyManager(enemy, rangedEnemy, mainChar));

	// ### Environment ###
	// Floor
	GameObject * floor = new TexturedCubeObject(sf::Vector2f{ 2000, 50 }, sf::Vector2f{ 500, 500 }, true, false, sf::Color{});
	floor->setObjectTag("Floor");
	m_gameObjects[0].push_back(floor);

	// Walls
	GameObject * wallLeft = new TexturedCubeObject(sf::Vector2f{ 200, 700 }, sf::Vector2f{ -500, 500 }, true, false, sf::Color{});
	wallLeft->setObjectTag("Wall");
	m_gameObjects[0].push_back(wallLeft);

	// Platforms
	GameObject * plat1 = new TexturedCubeObject(sf::Vector2f{ 200, 50 }, sf::Vector2f{ 500, 200 }, true, false, sf::Color{});
	plat1->setObjectTag("Floor");
	m_gameObjects[0].push_back(plat1);

	GameObject * plat2 = new TexturedCubeObject(sf::Vector2f{ 200, 50 }, sf::Vector2f{ 300, 320 }, true, false, sf::Color{});
	plat2->setObjectTag("Floor");
	m_gameObjects[0].push_back(plat2);
}


PlayingState::~PlayingState() {
	// Destroy game objects
	for (auto layer : m_gameObjects) {
		for (GameObject * g : layer) {
			delete g;
		}
	}

}

void PlayingState::update(float _dt) {
	for (int i = m_gameObjects.size() - 1; i >= 0; --i) {
		for (GameObject * g : m_gameObjects[i]) {
			if (g->isActive()) {
				g->update(_dt);
			}
		}
	}

	PhysicsEngine::getInstance().update(_dt);

	// Make view follow the centered object. freeze y coordinate
	m_view.setCenter((m_centeredObject->getPosition() + m_viewOffset).x, m_view.getCenter().y);

	// Add new objects
	GameObject * newObj = nullptr;
	for (int i = m_gameObjects.size() - 1; i >= 0; --i) {
		while (newObj = GameStateManager::popNewGameObject(i)) {
			m_gameObjects[i].push_back(newObj);
		}
	}
	// Pause game
	if (Input::getKeyDown(Input::P)) {
		GameStateManager::pushGameState(new PauseState());
	}
}

void PlayingState::draw() {
	Display::getWindow().setView(m_view);
	for (int i = m_gameObjects.size() - 1; i >= 0; --i) {
		for (GameObject * g : m_gameObjects[i]) {
			if (g->isActive()) {
				g->draw();
			}
		}
	}

	PhysicsEngine::getInstance().draw();
}

GameObject * PlayingState::instantiateObject(GameObject * _gameObject) {
	GameObject * newInstance = _gameObject->clone();

	return newInstance;
}
