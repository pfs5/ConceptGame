#include "EnemyManager.h"
#include "Input.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "Util.h"
#include "BasicEnemy.h"
#include "RangedEnemy.h"

EnemyManager::EnemyManager(GameObject * _enemy, GameObject * _rangedEnemy, GameObject * _player) :
	m_enemy{ _enemy },
	m_rangedEnemy {_rangedEnemy},
	m_player{ _player } {

}


EnemyManager::~EnemyManager() {
}

void EnemyManager::update(float _dt) {
	if (Input::getKeyDown(Input::K)) {

		Debug::log("Spawning enemy");

		int position = Util::randomInt(0, m_spawnPositions.size() - 1);

		std::cout << "position = " << position << std::endl;

		GameObject * newEnemy = GameStateManager::instantiate(m_enemy);
		newEnemy->setPosition(m_spawnPositions[position]);
		newEnemy->setActive(true);
		dynamic_cast<BasicEnemy *>(newEnemy)->setPlayerRef(m_player);
	}

	if (Input::getKeyDown(Input::L)) {

		Debug::log("Spawning ranged enemy");

		GameObject * newEnemy = GameStateManager::instantiate(m_rangedEnemy);
		newEnemy->setPosition(sf::Vector2f{ -450, 50 });
		newEnemy->setActive(true);
		dynamic_cast<RangedEnemy *>(newEnemy)->setPlayerRef(m_player);
	}
}

void EnemyManager::draw() {
}

void EnemyManager::onCollision(Collider * _other) {
}

GameObject * EnemyManager::clone() {
	return nullptr;
}

void EnemyManager::setPosition(sf::Vector2f _pos) {
}
