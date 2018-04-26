#include "BaseTree.h"
#include "Input.h"
#include "Display.h"
#include "PhysicsEngine.h"
#include "GameManager.h"
#include "GameSettings.h"
#include "Debug.h"

BaseTree::BaseTree() {
	setObjectTag("BaseTree");

	m_shape.setFillColor(sf::Color{ 100, 100, 100, 150 });
	m_shape.setSize(sf::Vector2f{ 200.f, 1600.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	auto collider = PhysicsEngine::getInstance().createCollider(this);
	auto colSize = m_shape.getSize();
	colSize.y *= 2.f;

	collider->setSize(colSize);
	collider->setTrigger(true);
	m_colliders.push_back(collider);

	m_targetHeight = INIT_HEIGHT;
	m_currentHeight = INIT_HEIGHT;
}

void BaseTree::update(float _dt) {
	if (Input::getKeyDown(Input::J)) m_targetHeight += 160.f;

	// Animate movement
	float difference = m_targetHeight - m_currentHeight;
	float delta = difference * _dt;
	m_currentHeight += delta;

	move(sf::Vector2f{ 0.f, delta });
}

void BaseTree::draw() {
	Display::draw(m_shape);
}

void BaseTree::onCollision(Collider * _this, Collider * _other) {
	if (_other->getGameObject()->isObjectTag("Enemy")) {
		// DAMAGE
		float damage = 10.f;
		float hp = GameManager::getInstance()->getHealthPoints();
		hp -= damage;

		GameManager::getInstance()->setHealthPoints(hp);
		m_targetHeight = hp / GameSettings::MAX_HEALTH_POINTS * INIT_HEIGHT;
	
		std::cout << "HP = " << hp << std::endl;
	}
}

GameObject * BaseTree::clone() {
	return nullptr;
}

void BaseTree::setPosition(sf::Vector2f _pos) {
	sf::Vector2f basePos = _pos + sf::Vector2f{ 0.f, m_currentHeight };
	
	m_position = _pos;
	m_shape.setPosition(basePos);

	for (auto col : m_colliders) {
		col->setPosition(_pos);
	}
}
