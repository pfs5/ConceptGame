#include "EnemyManager.h"
#include "Input.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "Util.h"
#include "BasicEnemy.h"
#include "RangedEnemy.h"

EnemyManager::EnemyManager(GameObject * _player) :
	m_player{ _player } {

	// Init shape
	m_spawnPositionVisual.setSize(sf::Vector2f{25, 25});
	m_spawnPositionVisual.setOrigin(m_spawnPositionVisual.getSize() / 2.f);
	m_spawnPositionVisual.setFillColor(sf::Color::Blue);
}


EnemyManager::~EnemyManager() {
}

void EnemyManager::update(float _dt) {
	if (Input::getKeyDown(Input::K)) {

		Debug::log("Spawning enemy");

		int position = Util::randomInt(0, m_spawnPositions.size() - 1);

		std::cout << "position = " << position << std::endl;

		GameObject * newEnemy = GameStateManager::instantiate(&BasicEnemy());
		newEnemy->setPosition(m_spawnPositions[position]);
		newEnemy->setActive(true);
		dynamic_cast<BasicEnemy *>(newEnemy)->setPlayerRef(m_player);
	}

	if (Input::getKeyDown(Input::L)) {

		Debug::log("Spawning ranged enemy");

		GameObject * newEnemy = GameStateManager::instantiate(&RangedEnemy());
		newEnemy->setPosition(sf::Vector2f{ -450, 50 });
		newEnemy->setActive(true);
		dynamic_cast<RangedEnemy *>(newEnemy)->setPlayerRef(m_player);
	}
}

void EnemyManager::draw() {
	if (m_showSpawnPositions) {
		for (auto pos : m_spawnPositions) {
			m_spawnPositionVisual.setPosition(pos);
			Display::draw(m_spawnPositionVisual);
		}
	}
}

void EnemyManager::onCollision(Collider * _other) {
}

GameObject * EnemyManager::clone() {
	return nullptr;
}

void EnemyManager::setPosition(sf::Vector2f _pos) {
}
