#include "stdafx.h"
#include "BasicEnemy.h"
#include "Debug.h"

BasicEnemy::BasicEnemy() :
	m_player{ nullptr },
	m_state{ ENEMY_STATE::ATTACKING },
	m_numberOfHits{0},
	m_died{ false } {

	setObjectTag("Enemy");
	setObjectLayer("Enemy");

	m_shape.setFillColor(sf::Color::Cyan);
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(5.f);
	m_shape.setSize(sf::Vector2f{ 50, 50 });

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(m_shape.getSize() + sf::Vector2f{ 10.f, 10.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	collider->setStatic(false);

	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(true);
	collider->setTrigger(false, m_rigidBody);

	setPosition(sf::Vector2f{ 0, 0 });

	setActive(false);
}

BasicEnemy::~BasicEnemy() {
}

void BasicEnemy::update(float _dt) {
	if (m_state == ENEMY_STATE::ATTACKING) {
		if (m_died) {
			// Die
			setActive(false);
			return;
		}

		// Move towards player
		if (m_player != nullptr) {
			sf::Vector2f dir = m_player->getPosition() - getPosition();

			sf::Vector2f vel = m_rigidBody->getVelocity();
			vel.x = dir.x / fabsf(dir.x) * m_movementSpeed;

			m_rigidBody->setVelocity(vel);
		}
	}

	if (m_state == ENEMY_STATE::HIT) {
		// Recoil
		sf::Vector2f vel = m_rigidBody->getVelocity();
		vel.x *= m_recoilSlowdown;
		m_rigidBody->setVelocity(vel);

		if (vel.x < m_recoilMinSpeed) {
			m_state = ENEMY_STATE::ATTACKING;
		}
	}
}

void BasicEnemy::draw() {
	Display::draw(m_shape);
}

void BasicEnemy::onCollision(Collider * _other) {
	// Hit by arrow
	if (_other->getGameObject()->getObjectTag() == "Arrow") {
		sf::Vector2f vel = m_rigidBody->getVelocity();
		vel.x = _other->getGameObject()->getRigidBody()->getVelocity().x;
		m_rigidBody->setVelocity(vel);

		if (++m_numberOfHits >= m_maxHits) {
			// Die after delay
			m_died = true;
		}

		m_state = ENEMY_STATE::HIT;
	}
}

GameObject * BasicEnemy::clone() {
	return new BasicEnemy();
}

void BasicEnemy::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}
