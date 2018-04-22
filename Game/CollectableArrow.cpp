#include "CollectableArrow.h"
#include "Display.h"
#include "PhysicsEngine.h"
#include "GameStateManager.h"
#include "Debug.h"

CollectableArrow::CollectableArrow(ARROW_DIRECTION _dir) : m_direction{ _dir } {
	setObjectTag("CollectableArrow");

	// Init shape
	m_shape.setSize(sf::Vector2f{10.f, 50.f});
	m_shape.setOrigin(sf::Vector2f{ 5.f, 25.f });
	m_shape.setRotation(_dir == ARROW_DIRECTION::LEFT ? 30 : -30);

	Collider * c = PhysicsEngine::getInstance().createCollider(this);
	c->setSize(sf::Vector2f{ 25.f, 20.f });
	c->setOffset(sf::Vector2f{ 0.f, 15.f });
	c->setStatic(true);
	m_colliders.push_back(c);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(c);
	m_rigidBody->setGravity(false);
	m_rigidBody->setBounceFactor(.4f);
	m_rigidBody->setVelocity(sf::Vector2f{ _dir == ARROW_DIRECTION::LEFT ? -500.f : 500.f, 500.f * 2});

	c->setTrigger(true, m_rigidBody);

	setActive(false);
}

void CollectableArrow::update(float _dt) {
	;
}

void CollectableArrow::draw() {
	Display::draw(m_shape);
}

void CollectableArrow::onCollision(Collider * _this, Collider * _other) {
	// Stop on collision
	if (_other->getGameObject()->isObjectTag("Floor") || 
		_other->getGameObject()->isObjectTag("Platform") ||
		_other->getGameObject()->isObjectTag("Wall")) {

		m_rigidBody->setVelocity(sf::Vector2f{0.f, 0.f});
		for (auto &col : m_colliders) {
			col->setStatic(true);
			col->setTrigger(true);
		}
	}

	// Destroy on player collision
	if (_other->getGameObject()->isObjectTag("Main")) {
		GameStateManager::destroyObject(this);
	}
}

GameObject * CollectableArrow::clone() {
	return new CollectableArrow(m_direction);
}

void CollectableArrow::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);

	for (auto &collider : m_colliders) {
		collider->setPosition(_pos);
	}
}
