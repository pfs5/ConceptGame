#include "EnemyManager.h"
#include "Input.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "Util.h"
#include "RangedEnemy.h"
#include "GameSettings.h"

EnemyManager::EnemyManager(GameObject * _player) :
	m_player{ _player } {

	// Init shape
	m_spawnPositionVisual.setSize(sf::Vector2f{25, 25});
	m_spawnPositionVisual.setOrigin(m_spawnPositionVisual.getSize() / 2.f);
	m_spawnPositionVisual.setFillColor(sf::Color::Blue);
}


EnemyManager::~EnemyManager() {
}

void EnemyManager::spawnBasicEnemy(BasicEnemy::ENEMY_TYPE _type) {
	Debug::log("Spawning enemy");

	int position = Util::randomInt(0, m_spawnPositions.size() - 1);

	std::cout << "position = " << position << std::endl;

	GameObject * newEnemy = GameStateManager::instantiate(&BasicEnemy(_type, m_basicEnemySpeeds[0]));
	newEnemy->setPosition(m_spawnPositions[position]);
	newEnemy->setActive(true);
	dynamic_cast<BasicEnemy *>(newEnemy)->setPlayerRef(m_player);
}

void EnemyManager::update(float _dt) {
	if (Input::getKeyDown(Input::Numpad0)) {
		spawnBasicEnemy(BasicEnemy::ENEMY_TYPE::CHASER);
	}
	
	if (Input::getKeyDown(Input::Numpad1)) {
		spawnBasicEnemy(BasicEnemy::ENEMY_TYPE::JUMPER);
	}
	
	if (Input::getKeyDown(Input::Numpad2)) {
		spawnBasicEnemy(BasicEnemy::ENEMY_TYPE::SPLITTER);
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
	if (GameSettings::SHOW_DEBUG_VISUALS) {
		for (auto pos : m_spawnPositions) {
			m_spawnPositionVisual.setPosition(pos);
			Display::draw(m_spawnPositionVisual);
		}
	}
}

void EnemyManager::onCollision(Collider * _this, Collider * _other) {
}

GameObject * EnemyManager::clone() {
	return nullptr;
}

void EnemyManager::setPosition(sf::Vector2f _pos) {
}
