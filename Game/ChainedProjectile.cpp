#include "ChainedProjectile.h"
#include "PhysicsEngine.h"
#include "Display.h"
#include "GameStateManager.h"
#include "BasicEnemy.h"
#include "RangedEnemy.h"
#include "Debug.h"

ChainedProjectile::ChainedProjectile() : 
	m_playerRef{ nullptr },
	m_hitEnemy {nullptr},
	m_chain{ nullptr } {

	// Init chain
	m_chain = dynamic_cast<Trail*>(GameStateManager::instantiate(&Trail(), 2));

	m_objectTag = "ChainedArrow";
	setObjectLayer("Arrow");

	m_shape.setSize(sf::Vector2f{ 20, 20 });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setFillColor(sf::Color{0, 153, 0});

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


ChainedProjectile::~ChainedProjectile() {
}

void ChainedProjectile::destroyChain() {
	GameStateManager::destroyObject(m_chain);
	m_chain = nullptr;
}

void ChainedProjectile::pullChain(sf::Vector2f _pullVector) {
	auto pullableEnemy = dynamic_cast<PullableEnemy*>(m_hitEnemy);

	if (pullableEnemy != nullptr) {
		pullableEnemy->pull(_pullVector);
	}

	destroyChain();
}

void ChainedProjectile::update(float _dt) {
	if (m_hitEnemy != nullptr) {
		setPosition(m_hitEnemy->getPosition());
	}
	
	// Update trail
	if (m_chain != nullptr) {
		m_chain->setPositions(m_playerRef->getPosition(), getPosition());
	}
}

void ChainedProjectile::draw() {
	Display::draw(m_shape);
}

void ChainedProjectile::onCollision(Collider * _other) {
	// Stick into everything but the player character or other arrows
	if (_other->getGameObject()->getObjectTag() != "Main" && _other->getGameObject()->getObjectTag() != getObjectTag()) {
		// Stop
		m_rigidBody->setVelocity(sf::Vector2f{ 0.f, 0.f });

		m_isStatic = true;
	}

	if (_other->getGameObject()->getObjectLayer() == "Enemy") {
		for (auto &c : m_colliders) {
			c->setTrigger(true);
		}

		m_rigidBody->setVelocity(sf::Vector2f{ 0, 0 });

		m_hitEnemy = _other->getGameObject();
	}
}

GameObject * ChainedProjectile::clone() {
	return new ChainedProjectile();
}

void ChainedProjectile::setPosition(sf::Vector2f _pos) {
	m_position = _pos;

	m_shape.setPosition(m_position);
	for (Collider * c : m_colliders) {
		c->setPosition(m_position);
	}
}
