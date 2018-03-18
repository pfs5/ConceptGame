#include "Projectile.h"
#include "PhysicsEngine.h"
#include "Display.h"
#include "Debug.h"
#include "GameStateManager.h"

Projectile::Projectile(int _direction) : m_direction(_direction) {
	m_objectTag = "Arrow";
	setObjectLayer("Arrow");

	m_controller.load("arrow");
	std::string animation = _direction > 0 ? "idle_right" : "idle_left";
	m_controller.playAnimation(animation);

	Collider * c = PhysicsEngine::getInstance().createCollider(this);
	c->setSize(sf::Vector2f{50, 20});
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
	m_controller.update(_dt);

	if ((m_destructionDelay -= _dt) < 0) {
		destroyProjectile();
	} 
}

void Projectile::draw() {
	m_controller.draw();
}

void Projectile::onCollision(Collider * _other) {
	// Sticking arrows get destroyed by other arrows
	if ((_other->getGameObject()->getObjectTag() == getObjectTag() || _other->getGameObject()->getObjectLayer() == getObjectLayer()) && m_isStatic) {
		destroyProjectile();
	}
	
	// Stick into everything but the player character or other arrows
	if (_other->getGameObject()->getObjectTag() != "Main" && _other->getGameObject()->getObjectLayer() != getObjectLayer()) {
		// Stop
		m_rigidBody->setVelocity(sf::Vector2f{ 0.f, 0.f });

		m_controller.setTrigger("hit");

		m_isStatic = true;
	}

	// Destroy if hit enemy
	if (_other->getGameObject()->getObjectTag() == "Enemy") {
		destroyProjectile();
	}
}

GameObject * Projectile::clone() {
	return new Projectile(m_direction);
}

void Projectile::setPosition(sf::Vector2f _pos) {
	m_position = _pos;

	m_controller.setPosition(m_position);

	for (Collider * c : m_colliders) {
		c->setPosition(m_position);
	}
}

void Projectile::destroyProjectile() {
	GameStateManager::destroyObject(this);
}
