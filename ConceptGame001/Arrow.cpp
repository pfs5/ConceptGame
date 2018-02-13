#include "Arrow.h"

Arrow::Arrow() {
	m_objectTag = "Arrow";

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
}

void Arrow::draw() {
	Display::draw(m_shape);
}

void Arrow::onCollision() {
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
