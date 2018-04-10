#include "WalkerEnemy.h"
#include "ResourceManager.h"
#include "Display.h"
#include "PhysicsEngine.h"
#include "VectorOperations.h"
#include "Debug.h"

WalkerEnemy::WalkerEnemy() : m_walkState{WALK_STATE::STEP_ONE} {
	setObjectLayer("WalkerEnemy");

	//auto tex = ResourceManager::getInstance().getTexture("walker_enemy");
	//tex->setSmooth(true);
	//m_sprite.setTexture(*tex);
	//m_sprite.setOrigin(VectorOperations::utof(tex->getSize()) / 2.f);

	auto collider = PhysicsEngine::getInstance().createCollider(this);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);

	collider->setSize(sf::Vector2f{ 100, 240 });
	collider->setTrigger(false, m_rigidBody);
	m_colliders.push_back(collider);

	// Init animator
	m_bodyController.load("walker_enemy");
}

WalkerEnemy::~WalkerEnemy() {
}

void WalkerEnemy::update(float _dt) {
	m_bodyController.update(_dt);
	m_counter += _dt;

	float speed = .4f * 2.f;
	int scale = 10;

	switch (m_walkState) {
		case WALK_STATE::STEP_ONE:
			move(sf::Vector2f{speed, 0.f});
			if (m_counter > 7.f / 60.f * scale) {
				m_walkState = WALK_STATE::HOLD_ONE;
			}
			break;
		case WALK_STATE::HOLD_ONE:
			if (m_counter > 11.f / 60.f * scale) {
				m_walkState = WALK_STATE::STEP_TWO;
			}
			break;
		case WALK_STATE::STEP_TWO:
			move(sf::Vector2f{ speed, 0.f });
			if (m_counter > 18.f / 60.f * scale) {
				m_walkState = WALK_STATE::HOLD_TWO;
			}
			break;
		case WALK_STATE::HOLD_TWO:
			if (!m_bodyController.isPlaying()) {
				m_walkState = WALK_STATE::STEP_ONE;
				m_counter = 0.f;
				m_bodyController.playAnimation("walk_right");
			}
			break;
	}

	//if (m_stepFirst) {
	//	m_counter += _dt;
	//	//float delta = fabsf(0.5f * sinf(2 * m_counter));
	//	move(sf::Vector2f{ .4f, 0.f });

	//	std::cout << m_counter << std::endl;
	//	if (m_counter > 9.f / 60.f * 20.f) {
	//		m_stepFirst = false;
	//		m_stepSecond = true;
	//	}
	//}
	//else if (m_stepSecond) {

	//}
	//else {
	//	if (!m_bodyController.isPlaying()) {
	//		m_step = true;
	//		m_counter = 0;
	//		m_bodyController.playAnimation("walk_right");
	//	}
	//}
}

void WalkerEnemy::draw() {
	//Display::draw(m_sprite);
	m_bodyController.draw();
}

void WalkerEnemy::onCollision(Collider * _other) {
}

GameObject * WalkerEnemy::clone() {
	return nullptr;
}

void WalkerEnemy::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_sprite.setPosition(_pos);
	m_bodyController.setPosition(_pos);
	for (auto col : m_colliders) {
		col->setPosition(_pos);
	}
}
