#include "ChainedProjectile.h"
#include "PhysicsEngine.h"
#include "Display.h"
#include "GameStateManager.h"
#include "BasicEnemy.h"
#include "RangedEnemy.h"
#include "Debug.h"

ChainedProjectile::ChainedProjectile(int _direction, bool _instantiateChain) :
	m_controller(90),
	m_direction{ _direction },
	m_isStatic{false},
	m_playerRef{ nullptr },
	m_hitEnemy {nullptr},
	m_chain{ nullptr } {

	// Init chain
	if (_instantiateChain) {
		m_chain = dynamic_cast<Trail*>(GameStateManager::instantiate(&Trail("chain"), 2));
		m_chain->setOffsets(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ 20.f, 0.f });
	}

	m_objectTag = "ChainedArrow";
	setObjectLayer("Arrow");

	m_controller.load("arrow");
	std::string animation =  "idle_left";
	m_controller.playAnimation(animation);

	Collider * c = PhysicsEngine::getInstance().createCollider(this);
	c->setSize(sf::Vector2f{ 15, 50 });
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
	if (m_chain != nullptr) {
		GameStateManager::destroyObject(m_chain);
		m_chain = nullptr;
	}
}

void ChainedProjectile::pullChain(sf::Vector2f _pullVector) {
	m_isPulled = true;

	auto pullableEnemy = dynamic_cast<PullableEnemy*>(m_hitEnemy);

	if (pullableEnemy != nullptr) {
		pullableEnemy->pull(_pullVector);
	}

	destroyChain();
	destroyProjectile();
}

void ChainedProjectile::update(float _dt) {
	m_controller.update(_dt);

	if (m_isDestroyed && !m_controller.isPlaying()) {
		destroyObject();
	}

	if (m_hitEnemy != nullptr) {
		setPosition(m_hitEnemy->getPosition());
	}
	else if ((m_destructionDelay -= _dt) < 0 && m_isPulled) {
		destroyProjectile();
	}
	
	// Update trail
	if (m_chain != nullptr) {
		m_chain->setPositions(m_playerRef->getPosition(), getPosition());
	}
}

void ChainedProjectile::draw() {
	m_controller.draw();
}

void ChainedProjectile::onCollision(Collider * _this, Collider * _other) {
	// Sticking arrows get destroyed by other arrows
	if ((_other->getGameObject()->getObjectTag() == getObjectTag() || _other->getGameObject()->getObjectLayer() == getObjectLayer()) && m_isStatic) {
		GameStateManager::destroyObject(this);
	}
	
	// Stick into everything but the player character or other arrows
	if (_other->getGameObject()->getObjectTag() != "Main" && _other->getGameObject()->getObjectLayer() != getObjectLayer()) {
		// Stop
		m_rigidBody->setVelocity(sf::Vector2f{ 0.f, 0.f });

		m_controller.setTrigger("hit");

		m_isStatic = true;

		if (m_chain != nullptr) {
			m_chain->setHit(true);
		}
	}

	if (_other->getGameObject()->getObjectLayer() == "Enemy") {
		for (auto &c : m_colliders) {
			c->setTrigger(true);
		}

		m_rigidBody->setVelocity(sf::Vector2f{ 0, 0 });

		m_hitEnemy = _other->getGameObject();
	
		if (m_chain != nullptr) {
			m_chain->setHit(true);
		}
	}
}

GameObject * ChainedProjectile::clone() {
	return new ChainedProjectile(m_direction, true);
}

void ChainedProjectile::setPosition(sf::Vector2f _pos) {
	m_position = _pos;

	m_controller.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(m_position);
	}
}

void ChainedProjectile::destroyProjectile() {
	m_isDestroyed = true;
	m_controller.setTrigger("destroy");
}

void ChainedProjectile::destroyObject() {
	destroyChain();
	GameStateManager::destroyObject(this);
}
