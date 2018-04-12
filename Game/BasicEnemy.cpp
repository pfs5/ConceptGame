#include "BasicEnemy.h"
#include "Debug.h"
#include "GameStateManager.h"
#include "Explosion.h"
#include "FloatOperations.h"
#include "VectorOperations.h"
#include "GameSettings.h"

BasicEnemy::BasicEnemy(ENEMY_TYPE _type, float _speed) :
	m_type {_type},
	m_movementSpeed{_speed},
	m_player{ nullptr },
	m_state{ ENEMY_STATE::ATTACKING },
	m_numberOfHits{0},
	m_died{ false },
	m_jumpReady{ true } {

	setObjectTag("Enemy");
	setObjectLayer("Enemy");

	m_controller.load("basic_enemy");

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(sf::Vector2f{ 50.f, 50.f });

	collider->setStatic(false);

	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(true);
	collider->setTrigger(false, m_rigidBody);

	setPosition(sf::Vector2f{ 0, 0 });

	setActive(false);

	// Init enemy
	switch (m_type) {
	case ENEMY_TYPE::CHASER:
		m_controller.setColor(sf::Color::White);
		break;
	case ENEMY_TYPE::JUMPER:
		m_controller.setColor(sf::Color::Cyan);
		break;
	case ENEMY_TYPE::SPLITTER:
		m_controller.setColor(sf::Color::Yellow);
		break;
	}
}

BasicEnemy::~BasicEnemy() {
}

void BasicEnemy::update(float _dt) {
	m_controller.update(_dt);

	if (m_state == ENEMY_STATE::ATTACKING) {
		// Move towards player - AI
		if (m_player != nullptr) {
			switch (m_type) {
				case ENEMY_TYPE::CHASER:
					chaserAIUpdate();
					break;
				case ENEMY_TYPE::JUMPER:
					jumperAIUpdate();
					break;
				case ENEMY_TYPE::SPLITTER:
					chaserAIUpdate();
					break;
			}
		}
	}

	if (m_state == ENEMY_STATE::HIT) {
		// Recoil
		sf::Vector2f vel = m_rigidBody->getVelocity();
		vel.x *= m_recoilSlowdown;
		m_rigidBody->setVelocity(vel);

		if (fabsf(vel.x) < m_recoilMinSpeed) {
			m_state = ENEMY_STATE::ATTACKING;
		}
	}
}

void BasicEnemy::draw() {
	//Display::draw(m_shape);
	m_controller.draw();
}

void BasicEnemy::onCollision(Collider * _this, Collider * _other) {
	// Reset jump
	if (_other->getGameObject()->getObjectTag() == "BottomFloor") {
		m_jumpReady = true;
	}

	// Hit by arrow
	if (_other->getGameObject()->getObjectTag() == "Arrow") {
		sf::Vector2f vel = m_rigidBody->getVelocity();
		vel.x = _other->getGameObject()->getRigidBody()->getVelocity().x;
		m_rigidBody->setVelocity(vel);

		if (++m_numberOfHits >= m_maxHits) {
			death();
		}

		m_state = ENEMY_STATE::HIT;
	}
}

GameObject * BasicEnemy::clone() {
	return new BasicEnemy(m_type, m_movementSpeed);
}

void BasicEnemy::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_controller.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}

void BasicEnemy::pull(sf::Vector2f _pullVector) {
	getRigidBody()->setVelocity(_pullVector * 1000.f);

	m_state = ENEMY_STATE::HIT;
}

void BasicEnemy::chaserAIUpdate() {
	if (FloatOperations::compare(m_player->getPosition().y, getPosition().y) < 0) {
		sf::Vector2f dir = m_player->getPosition() - getPosition();

		sf::Vector2f vel = m_rigidBody->getVelocity();
		vel.x = dir.x / fabsf(dir.x) * m_movementSpeed;

		m_rigidBody->setVelocity(vel);
	}
	else if (FloatOperations::compare(m_rigidBody->getVelocity().x, 0.f) == 0) {
		m_rigidBody->setVelocity(sf::Vector2f{ m_movementSpeed, 0.f });
	}
}

void BasicEnemy::jumperAIUpdate() {
	float distanceToPlayer = fabsf(m_player->getPosition().y - m_position.y);

	if (distanceToPlayer < 200.f) {
		sf::Vector2f dir = m_player->getPosition() - getPosition();

		sf::Vector2f vel = m_rigidBody->getVelocity();
		vel.x = dir.x / fabsf(dir.x) * m_movementSpeed;

		m_rigidBody->setVelocity(vel);
	} else if (FloatOperations::compare(m_player->getPosition().y, getPosition().y) > 0) {
		
		if (FloatOperations::compare(m_rigidBody->getVelocity().x, 0.f) == 0) {
			m_rigidBody->setVelocity(sf::Vector2f{ m_movementSpeed, 0.f });
		}
	}
	else {
		sf::Vector2f hitPoint = PhysicsEngine::getInstance().raycast(m_position + sf::Vector2f{ 0, -50 }, sf::Vector2f{ 0.f, -1.f }, { "Floor" });

		if (hitPoint.y < m_position.y) {

			float distanceToPlatform = fabsf(hitPoint.y - m_position.y);

			if (distanceToPlayer < distanceToPlatform && m_jumpReady) {
				m_jumpReady = false;

				// jump

				auto vel = m_rigidBody->getVelocity();
				vel.y = sqrtf(2 * GameSettings::GRAVITY * (distanceToPlayer + 100));
				m_rigidBody->setVelocity(vel);
			}
		}
	}
}

void BasicEnemy::death() {
	if (m_type == ENEMY_TYPE::SPLITTER) {
		std::cout << "death" << std::endl;
		GameStateManager::instantiate(&Explosion(m_position));

		// Spawn two new enemies
		auto enemy1 = GameStateManager::instantiate(&BasicEnemy(BasicEnemy::ENEMY_TYPE::CHASER, m_movementSpeed));
		enemy1->setPosition(m_position);
		enemy1->setActive(true);
		dynamic_cast<BasicEnemy *>(enemy1)->setPlayerRef(m_player);
		dynamic_cast<BasicEnemy *>(enemy1)->pull(sf::Vector2f{0.5f, 1.f});

		auto enemy2 = GameStateManager::instantiate(&BasicEnemy(BasicEnemy::ENEMY_TYPE::CHASER, m_movementSpeed));
		enemy2->setPosition(m_position);
		enemy2->setActive(true);
		dynamic_cast<BasicEnemy *>(enemy2)->setPlayerRef(m_player);
		dynamic_cast<BasicEnemy *>(enemy2)->pull(sf::Vector2f{ -0.5f, 1.f });


		// Destoy this enemy
		GameStateManager::destroyObject(this);
	} else {
		GameStateManager::instantiate(&Explosion(m_position));
		GameStateManager::destroyObject(this);
	}

	return;
}
