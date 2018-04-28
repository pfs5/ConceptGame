#include "GameManager.h"
#include "Input.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "GameSettings.h"
#include "Util.h"

GameManager::GameManager() : 
	m_isInitialized {false},
	m_activeCollectableArrows{ 0 },
	m_healthPoints{ GameSettings::MAX_HEALTH_POINTS } {
}

void GameManager::spawnArrow(sf::Vector2f _pos, CollectableArrow::ARROW_DIRECTION _dir) {
	auto newArrow = GameStateManager::instantiate(&CollectableArrow(_dir), 2);
	dynamic_cast<CollectableArrow*>(newArrow)->attachObserver(this);

	_pos.x += Util::randomFloat() * MAX_ARROW_OFFSET + MAX_ARROW_OFFSET / 2.f; 
	newArrow->setPosition(_pos);
	newArrow->setActive(true);

	m_activeCollectableArrows++;
}

void GameManager::spawnArrows(int _numberOfArrows) {
	while (m_activeCollectableArrows < _numberOfArrows) {
		// Spawn random arrow
		CollectableArrow::ARROW_DIRECTION direction = Util::randomFloat() < 0.5f ?
			CollectableArrow::ARROW_DIRECTION::LEFT : CollectableArrow::ARROW_DIRECTION::RIGHT;
		sf::Vector2f spawnPosition;

		switch (direction) {
		case CollectableArrow::ARROW_DIRECTION::LEFT: {
			int spawnPositionIndex = Util::randomInt(0, SPAWN_POSITIONS_LEFT.size() - 1);
			spawnPosition = SPAWN_POSITIONS_LEFT[spawnPositionIndex];
			break;
		}
		case CollectableArrow::ARROW_DIRECTION::RIGHT: {
			int spawnPositionIndex = Util::randomInt(0, SPAWN_POSITIONS_RIGHT.size() - 1);
			spawnPosition = SPAWN_POSITIONS_RIGHT[spawnPositionIndex];
			break;
		}
		}

		spawnArrow(spawnPosition, direction);
	}
}

void GameManager::notify() {
	m_activeCollectableArrows--;
}

void GameManager::update(float _dt) {
	if (!m_isInitialized) {
		m_isInitialized = true;
		spawnArrows(INITIAL_ARROWS_IN_SCENE);
	}

	// Arrow spawning
	spawnArrows(MIN_ARROWS_IN_SCENE);

	// DEBUG CONTROLLS
	if (Input::getKeyDown(Input::Numpad1)) {
		spawnArrow(SPAWN_POSITIONS_RIGHT[0], CollectableArrow::ARROW_DIRECTION::RIGHT);
	}
}

void GameManager::draw() {
}

void GameManager::onCollision(Collider * _this, Collider * _other) {
}

GameObject * GameManager::clone() {
	return new GameManager();
}

void GameManager::setPosition(sf::Vector2f _pos) {
}
