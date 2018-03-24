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
#include "Trail.h"
#include "BasicMap.h"
#include "Platform.h"
#include "PlatformManager.h"
#include "VectorOperations.h"

#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>

void createCube(sf::Vector2i _pos, std::vector<GameObject*> &_gameObjects) {
	GameObject * cube = new CubeObject(sf::Vector2f{ 50, 50 }, sf::Vector2f{ static_cast<float>(_pos.x - 25), static_cast<float>(_pos.y - 25) }, false, true);
	_gameObjects.push_back(cube);
}

PlayingState::PlayingState() {
	// ### Game objects setup ###
	for (int i = 0; i < GameStateManager::objectLayers; ++i) {
		m_gameObjects.push_back(std::vector<GameObject*>());
	}

	// ### Map setup ###
	m_map = new BasicMap();

	// ### View setup ###
	m_view.reset(sf::FloatRect(0.f, 0.f, Display::getWindow().getSize().x, Display::getWindow().getSize().y));

	// ### Create main character ###
	GameObject * mainChar = new MainCharacter();
	m_gameObjects[0].push_back(mainChar);
	m_centeredObject = mainChar;

	// ### Environment ###
	sf::Vector2f winSize = VectorOperations::utof(Display::getWindow().getSize());

	// Floor
	GameObject * floor = new CubeObject(sf::Vector2f{ 2000, 50 }, sf::Vector2f{ winSize.x / 2, 826 }, true, false, sf::Color::Black);
	floor->setObjectTag("Floor");
	m_gameObjects[0].push_back(floor);

	// Ceiling
	GameObject * ceil = new CubeObject(sf::Vector2f{ 2000, 50 }, sf::Vector2f{ winSize.x / 2, -1000 }, true, false, sf::Color::Black);
	ceil->setObjectTag("Wall");
	m_gameObjects[0].push_back(ceil);

	// Platforms
	m_gameObjects[0].push_back(new PlatformManager());
	
	// Walls
	GameObject * wall1 = new TexturedCubeObject(sf::Vector2f{ 500, 2000 }, sf::Vector2f{ 1650, winSize.y / 2 }, true, false, sf::Color{});
	wall1->setObjectTag("Wall");
	m_gameObjects[0].push_back(wall1);

	GameObject * wall2 = new TexturedCubeObject(sf::Vector2f{ 500, 2000 }, sf::Vector2f{ -215, winSize.y / 2 }, true, false, sf::Color{});
	wall2->setObjectTag("Wall");
	m_gameObjects[0].push_back(wall2);

	// ### Enemies ###
	m_gameObjects[0].push_back(new EnemyManager(mainChar));
}


PlayingState::~PlayingState() {
	// Destroy game objects
	for (auto layer : m_gameObjects) {
		for (GameObject * g : layer) {
			delete g;
		}
	}

	// Delete map
	delete m_map;
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

	updateView(_dt);

	// Add new objects
	GameObject * newObj = nullptr;
	for (int i = m_gameObjects.size() - 1; i >= 0; --i) {
		while (newObj = GameStateManager::popNewGameObject(i)) {
			m_gameObjects[i].push_back(newObj);
		}
	}

	// Destroy objects
	GameObject * destrObj = nullptr;
	while (destrObj = GameStateManager::popDestroyedGameObject()) {
		for (auto &layer : m_gameObjects) {
			layer.erase(std::remove(layer.begin(), layer.end(), destrObj), layer.end());
		}
		delete destrObj;
	}

	// Pause game
	if (Input::getKeyDown(Input::P)) {
		GameStateManager::pushGameState(new PauseState());
	}
}

void PlayingState::draw() {
	// Level background
	m_map->drawBackground();

	// Objects
	Display::getWindow().setView(m_view);
	for (int i = m_gameObjects.size() - 1; i >= 0; --i) {
		for (GameObject * g : m_gameObjects[i]) {
			if (g->isActive()) {
				g->draw();
			}
		}
	}

	// Level foreground
	m_map->drawForeground();

	// Engine debug
	PhysicsEngine::getInstance().draw();
}

GameObject * PlayingState::instantiateObject(GameObject * _gameObject) {
	GameObject * newInstance = _gameObject->clone();

	return newInstance;
}

void PlayingState::destroyObject(GameObject * _gameObject) {
	_gameObject->setActive(false);
}

void PlayingState::updateView(float _dt) {
	// Set new center
	auto winSize = Display::getWindow().getSize();
	float minHeight = Display::getWindow().getSize().y / 2.f + 100;
	float floorDistance = minHeight * 2 - m_centeredObject->getPosition().y;
	
	float height = fmaxf(floorDistance - minHeight, 0);

	// Camera movement function
	float cameraHeight = height / 2.f;
	float scaling = cameraHeight / minHeight + 1;

	auto center = m_view.getCenter();
	center.y = minHeight - cameraHeight;

	auto size = sf::Vector2f{ static_cast<float>(winSize.x), static_cast<float>(winSize.y)} *scaling;

	// Lerp towards target
	auto centerDelta = (center - m_view.getCenter()) * _dt * m_lerpSpeed;
	m_view.setCenter(m_view.getCenter() + centerDelta);

	auto sizeDelta = (size - m_view.getSize()) * _dt * m_lerpSpeed;
	m_view.setSize(m_view.getSize() + sizeDelta);
}
