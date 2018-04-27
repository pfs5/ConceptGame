#include "BaseTree.h"
#include "Input.h"
#include "Display.h"
#include "PhysicsEngine.h"
#include "GameManager.h"
#include "GameSettings.h"
#include "ResourceManager.h"
#include "VectorOperations.h"
#include "Debug.h"

BaseTree::BaseTree() {
	setObjectTag("BaseTree");

	auto tex = ResourceManager::getInstance().getTexture("flat_level_base");
	//m_sprite.setOrigin(VectorOperations::utof(tex->getSize()));
	m_sprite.setOrigin(sf::Vector2f{ static_cast<float>(tex->getSize().x) / 2.f, static_cast<float>(tex->getSize().y) * 1.5f});
	m_sprite.setTexture(*tex);

	auto collider = PhysicsEngine::getInstance().createCollider(this);
	auto colSize = VectorOperations::utof(tex->getSize());
	colSize.y *= 2.f;

	collider->setSize(colSize);
	collider->setTrigger(true);
	m_colliders.push_back(collider);

	m_targetHeight = 0.f;
	m_currentHeight = 0.f;
}

void BaseTree::update(float _dt) {
	if (Input::getKeyDown(Input::K)) {
		float damage = GameSettings::WALKER_DAMAGE;
		float hp = GameManager::getInstance()->getHealthPoints();
		hp -= damage;

		updateHealth(hp);
	}
	if (Input::getKeyDown(Input::I)) {
		float damage = GameSettings::WALKER_DAMAGE;
		float hp = GameManager::getInstance()->getHealthPoints();
		hp += damage;

		updateHealth(hp);
	}

	// Animate movement
	float difference = m_targetHeight - m_currentHeight;
	float delta = difference * _dt * ANIMATION_SPEED;
	m_currentHeight += delta;

	move(sf::Vector2f{ 0.f, delta });
}

void BaseTree::draw() {
	Display::draw(m_sprite);
}

void BaseTree::onCollision(Collider * _this, Collider * _other) {
	if (_other->getGameObject()->isObjectTag("Enemy")) {
		// DAMAGE
		float damage = GameSettings::WALKER_DAMAGE;
		float hp = GameManager::getInstance()->getHealthPoints();
		hp -= damage;

		updateHealth(hp);
	}
}

GameObject * BaseTree::clone() {
	return nullptr;
}

void BaseTree::setPosition(sf::Vector2f _pos) {
	sf::Vector2f basePos = _pos + sf::Vector2f{ 0.f, m_currentHeight };
	
	m_position = _pos;
	m_sprite.setPosition(basePos);

	for (auto col : m_colliders) {
		col->setPosition(_pos);
	}
}

void BaseTree::updateHealth(float _hp) {
	GameManager::getInstance()->setHealthPoints(_hp);
	m_targetHeight = (1.f -_hp / GameSettings::MAX_HEALTH_POINTS) * MAX_HEIGHT;

	std::cout << _hp / GameSettings::MAX_HEALTH_POINTS << std::endl;
	std::cout << "HP = " << _hp << std::endl;
}
