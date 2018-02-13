#include "Arrow.h"

Arrow::Arrow() {
	m_objectTag = "Arrow";
	setObjectLayer("Arrow");

	m_shape.setSize(sf::Vector2f{ 80, 10 });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setFillColor(sf::Color::Red);

	Collider * c = PhysicsEngine::getInstance().createCollider(this);
	c->setSize(m_shape.getSize());
	m_colliders.push_back(c);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(c);
	m_rigidBody->setGravity(true);
	m_rigidBody->setBounceFactor(.4f);

	c->setTrigger(false, m_rigidBody); 
}

void Arrow::update(float _dt) {
	if (m_timeAlive > 0) {
		m_timeAlive--;
	}
}

void Arrow::draw() {
	Display::draw(m_shape);
}

void Arrow::onCollision(Collider * _other) {
	if (_other->getGameObject()->getObjectLayer() == getObjectLayer()) {
		// Ignore arrow to arrow collision
		return;
	}

	// If collision too early, delete
	if (m_timeAlive > 0) {
		setActive(false);
	}


	// Freeze
	m_rigidBody->setGravity(false);
	m_rigidBody->setVelocity(sf::Vector2f{ 0.f, 0.f });

	for (Collider * c : m_colliders) {
		c->setStatic(true);
	}
}

GameObject * Arrow::clone() {
	return new Arrow();
}

void Arrow::setPosition(sf::Vector2f _pos) {
	m_position = _pos;

	m_shape.setPosition(m_position);
	for (Collider * c : m_colliders) {
		c->setPosition(m_position);
	}
}
