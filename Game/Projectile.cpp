#include "Projectile.h"
#include "PhysicsEngine.h"
#include "Display.h"
#include "Debug.h"

Projectile::Projectile() {
	m_objectTag = "Arrow";
	setObjectLayer("Arrow");

	m_shape.setSize(sf::Vector2f{ 20, 20 });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setFillColor(sf::Color::Red);

	Collider * c = PhysicsEngine::getInstance().createCollider(this);
	c->setSize(m_shape.getSize());
	c->setStatic(true);
	m_colliders.push_back(c);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(c);
	m_rigidBody->setGravity(false);
	m_rigidBody->setBounceFactor(.4f);

	c->setTrigger(false, m_rigidBody);

	setActive(false);
}


Projectile::~Projectile() {
}

void Projectile::update(float _dt) {
	if ((m_destructionDelay -= _dt) < 0) {
		destroyProjectile();
	} 
}

void Projectile::draw() {
	Display::draw(m_shape);
}

void Projectile::onCollision(Collider * _other) {
	// Stick into everything but the player character or other arrows
	if (_other->getGameObject()->getObjectTag() != "Main" && _other->getGameObject()->getObjectTag() != getObjectTag()) {
		// Stop
		m_rigidBody->setVelocity(sf::Vector2f{ 0.f, 0.f });

		m_isStatic = true;
	}

	// Sticking arrows get destroyed by other arrows
	if (_other->getGameObject()->getObjectTag() == getObjectTag() && m_isStatic) {
		destroyProjectile();
	}

	// Destroy if hit enemy
	if (_other->getGameObject()->getObjectTag() == "Enemy") {
		destroyProjectile();
	}
}

GameObject * Projectile::clone() {
	return new Projectile();
}

void Projectile::setPosition(sf::Vector2f _pos) {
	m_position = _pos;

	m_shape.setPosition(m_position);
	for (Collider * c : m_colliders) {
		c->setPosition(m_position);
	}
}

void Projectile::destroyProjectile() {
	setActive(false);
}
