#include "SwarmEnemy.h"
#include "Display.h"
#include "AISystem.h"
#include "VectorOperations.h"
#include "PhysicsEngine.h"
#include "Debug.h"
#include "GameSettings.h"
#include "FloatOperations.h"
#include "Util.h"

SwarmEnemy::SwarmEnemy(sf::Color _color) : m_activated{ true }, m_previous{ nullptr }, m_next{nullptr} {
	setObjectLayer("Swarm");

	// Init shape
	m_shape.setRadius(7.f);
	m_shape.setFillColor(_color);
	m_shape.setOutlineColor(_color);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());

	m_rangeShape.setRadius(200.f);
	m_rangeShape.setFillColor(sf::Color::Transparent);
	m_rangeShape.setOutlineThickness(2.f);
	m_rangeShape.setOutlineColor(sf::Color::Cyan);
	m_rangeShape.setOrigin(m_rangeShape.getRadius(), m_rangeShape.getRadius());

	// Init physics
	auto collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(sf::Vector2f{ 10, 10 });
	m_colliders.push_back(collider);
	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(true);

	collider->setTrigger(false, m_rigidBody);

	setPosition(sf::Vector2f{ 500, 300 });

	setActive(true);
}

SwarmEnemy::~SwarmEnemy() {
}

void SwarmEnemy::update(float _dt) {
	// First
	if (m_previous == nullptr) {
		getRigidBody()->setGravity(false);
		getRigidBody()->setVelocity(sf::Vector2f{0, 0});
	}
	else {
		// Keep offset
		float offset = 20.f;
		sf::Vector2f dir = m_previous->getPosition() - getPosition();
		float norm = VectorOperations::norm(dir);
		if (fabsf(norm) > 0.1f)  {
			move(dir * (norm - offset));
		}
	}
}

void SwarmEnemy::draw() {
	Display::draw(m_shape);
	//Display::draw(m_rangeShape);
}

void SwarmEnemy::onCollision(Collider * _other) {
	if (_other->getGameObject()->getObjectTag() == "Floor") {
		m_activated = true;
	}
}

GameObject * SwarmEnemy::clone() {
	return new SwarmEnemy();
}

void SwarmEnemy::setPosition(sf::Vector2f _pos) {
	m_position = _pos;

	m_shape.setPosition(_pos);
	m_rangeShape.setPosition(_pos);

	for (auto coll : m_colliders) {
		coll->setPosition(_pos);
	}
}
