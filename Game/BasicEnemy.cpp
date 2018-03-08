#include "stdafx.h"
#include "BasicEnemy.h"
#include "Debug.h"

BasicEnemy::BasicEnemy() : 
	m_cube{ sf::Vector2f{50, 50}, sf::Vector2f{0, 0}, false, true, sf::Color::Cyan },
	m_player{ nullptr } {

	setActive(false);
	m_cube.setActive(false);
}


BasicEnemy::~BasicEnemy() {
}

void BasicEnemy::update(float _dt) {
	m_cube.update(_dt);

	// Move towards player
	if (m_player != nullptr) {
		sf::Vector2f dir = m_player->getPosition() - m_cube.getPosition();

		sf::Vector2f vel = m_cube.getRigidBody()->getVelocity();
		vel.x = dir.x / fabsf(dir.x) * m_movementSpeed;

		m_cube.getRigidBody()->setVelocity(vel);
	}
}

void BasicEnemy::draw() {
	m_cube.draw();
}

void BasicEnemy::onCollision(Collider * _other) {
}

GameObject * BasicEnemy::clone() {
	return new BasicEnemy();
}

void BasicEnemy::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_cube.setPosition(_pos);
}
