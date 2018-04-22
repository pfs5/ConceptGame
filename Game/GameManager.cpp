#include "GameManager.h"
#include "Input.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "Util.h"

GameManager::GameManager() {
}

void GameManager::spawnArrow(sf::Vector2f _pos, CollectableArrow::ARROW_DIRECTION _dir) {
	auto newArrow = GameStateManager::instantiate(&CollectableArrow(_dir), 2);

	_pos.x += Util::randomFloat() * MAX_ARROW_OFFSET + MAX_ARROW_OFFSET / 2.f; 

	newArrow->setPosition(_pos);
	newArrow->setActive(true);
}

void GameManager::update(float _dt) {
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
