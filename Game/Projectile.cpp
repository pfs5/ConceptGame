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
	c->setSize(sf::Vector2f{50, 10});
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

	if (m_isDestroyed && !m_controller.isPlaying()) {
		GameStateManager::destroyObject(this);
	}
}

void Projectile::draw() {
	m_controller.draw();
}

void Projectile::onCollision(Collider * _this, Collider * _other) {
	// Sticking arrows get destroyed by other arrows
	if ((_other->getGameObject()->getObjectTag() == getObjectTag() || _other->getGameObject()->getObjectLayer() == getObjectLayer()) && m_isStatic) {
		destroyObject();
	}
	
	// Stick into everything but the player character or other arrows
	if (_other->getGameObject()->getObjectTag() != "Main" 
		&& _other->getGameObject()->getObjectLayer() != getObjectLayer()) {
		// Stop
		m_rigidBody->setVelocity(sf::Vector2f{ 0.f, 0.f });

		m_controller.setTrigger("hit");

		m_isStatic = true;
	}

	// Destroy if hit enemy
	if (_other->getGameObject()->getObjectTag() == "Enemy") {
		//destroyObject();
	}
}

GameObject * Projectile::clone() {
	return new Projectile(m_direction);
}

void Projectile::setPosition(sf::Vector2f _pos) {
	m_position = m_attachedObject == nullptr ? _pos : m_attachedObject->getPosition() + m_attachedOffset;

	m_controller.setPosition(m_position);

	for (Collider * c : m_colliders) {
		c->setPosition(m_position);
	}
}

void Projectile::destroyProjectile() {
	m_isDestroyed = true;

	m_controller.setTrigger("destroy");
}

void Projectile::destroyObject() {
	GameStateManager::destroyObject(this);
}

void Projectile::breakArrow() {
	setObjectLayer("DestroyedArrow");
	destroyProjectile();
}

void Projectile::attachArrow(GameObject * _object) {
	for (auto col : m_colliders) {
		PhysicsEngine::getInstance().deleteCollider(col);
	}
	m_colliders.clear();

	m_attachedOffset = getPosition() - _object->getPosition();
	m_attachedObject = _object;
}

void Projectile::destroyArrow() {
	// Destroy colliders
	for (auto col : m_colliders) {
		PhysicsEngine::getInstance().deleteCollider(col);
	}

	m_colliders.clear();

	GameStateManager::destroyObject(this);
}
