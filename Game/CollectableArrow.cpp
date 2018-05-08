#include "CollectableArrow.h"
#include "Display.h"
#include "PhysicsEngine.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "ResourceManager.h"
#include "Util.h"

CollectableArrow::CollectableArrow(ARROW_DIRECTION _dir) : m_direction{ _dir }, m_isStuck{ false }, m_wasShot{ false } {
	setObjectTag("CollectableArrow");

	// Init controller
	m_controller.load("collectable_arrow");
	m_controller.setRotation(_dir == ARROW_DIRECTION::LEFT ? -60 : 180 + 60);

	// Init shape
	m_shape.setSize(sf::Vector2f{10.f, 50.f});
	m_shape.setOrigin(sf::Vector2f{ 5.f, 25.f });
	m_shape.setRotation(_dir == ARROW_DIRECTION::LEFT ? 30 : -30);

	// Init audio
	m_hitSound.setBuffer(*ResourceManager::getInstance().getSound("arrow_hit"));
	m_shootSound.setBuffer(*ResourceManager::getInstance().getSound("arrow_shoot"));

	float pitchOffset = (Util::randomFloat() * MAX_PITCH_OFFSET * 2) - MAX_PITCH_OFFSET;
	m_hitSound.setPitch(1.f + pitchOffset);

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

void CollectableArrow::attachObserver(CollectableArrowObserver * _o) {
	m_observers.push_back(_o);
}

void CollectableArrow::update(float _dt) {
	if (!m_wasShot) {
		m_wasShot = true;
		m_shootSound.play();
	}

	m_controller.update(_dt);
}

void CollectableArrow::draw() {
	//Display::draw(m_shape);
	m_controller.draw();
}

void CollectableArrow::onCollision(Collider * _this, Collider * _other) {
	// Stop on collision
	if ((_other->getGameObject()->isObjectTag("Floor") || 
		_other->getGameObject()->isObjectTag("Platform") ||
		_other->getGameObject()->isObjectTag("Wall")) &&
		!m_isStuck) {
		m_isStuck = true;

		m_rigidBody->setVelocity(sf::Vector2f{0.f, 0.f});
		for (auto &col : m_colliders) {
			col->setStatic(true);
			col->setTrigger(true);
		}

		// play audio
		m_hitSound.play();
	}

	// Destroy on player collision
	if (_other->getGameObject()->isObjectTag("Main")) {
		notifyObservers();
		GameStateManager::destroyObject(this);
	}
}

GameObject * CollectableArrow::clone() {
	return new CollectableArrow(m_direction);
}

void CollectableArrow::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);
	m_controller.setPosition(_pos);

	for (auto &collider : m_colliders) {
		collider->setPosition(_pos);
	}
}

void CollectableArrow::notifyObservers() {
	for (auto &o : m_observers) {
		o->notify();
	}
}
