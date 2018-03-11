#include "RangedEnemy.h"
#include "PhysicsEngine.h"
#include "Display.h"
#include "Input.h"
#include "GameStateManager.h"
#include "Debug.h"

RangedEnemy::RangedEnemy() :
	m_player{ nullptr },
	m_numberOfHits{ 0 },
	m_died{ false } {

	setObjectTag("Enemy");
	setObjectLayer("Enemy");

	m_shape.setFillColor(sf::Color::Magenta);
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(5.f);
	m_shape.setSize(sf::Vector2f{ 50, 50 });

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(m_shape.getSize() + sf::Vector2f{ 10.f, 10.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	collider->setStatic(false);

	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(true);
	collider->setTrigger(false, m_rigidBody);

	setPosition(sf::Vector2f{ 0, 0 });

	setActive(false);
}


RangedEnemy::~RangedEnemy() {
}

void RangedEnemy::update(float _dt) {
	if (Input::getKeyDown(Input::O)) {
		// Shoot
		auto gunshot = dynamic_cast<Gunshot*> (GameStateManager::instantiate(m_gunshotPrefab));
		sf::Vector2f end = PhysicsEngine::getInstance().raycast(m_position, m_player->getPosition() - m_position, std::vector<std::string>{"Floor"});
		Debug::log(end);
		gunshot->setPositions(m_position, end);
	}
}

void RangedEnemy::draw() {
	Display::draw(m_shape);
}

void RangedEnemy::onCollision(Collider * _other) {
	if (_other->getGameObject()->getObjectTag() == "Arrow") {
		if (m_numberOfHits++ >= m_maxHits) {
			GameStateManager::destroyObject(this);
		}
	}
}

GameObject * RangedEnemy::clone() {
	auto enemy = new RangedEnemy();
	enemy->setGunshotPrefab(m_gunshotPrefab);
	return enemy;
}

void RangedEnemy::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}
