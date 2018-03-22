#include "Explosion.h"
#include "GameStateManager.h"

Explosion::Explosion(sf::Vector2f _position) : m_position{ _position } {
	m_controller.load("explosion_one");
	setPosition(m_position);
}

Explosion::~Explosion() {
}

void Explosion::update(float _dt) {
	m_controller.update(_dt);

	if (!m_controller.isPlaying()) {
		GameStateManager::destroyObject(this);
	}
}

void Explosion::draw() {
	m_controller.draw();
}

void Explosion::onCollision(Collider * _other) {
}

GameObject * Explosion::clone() {
	return new Explosion(m_position);
}

void Explosion::setPosition(sf::Vector2f _pos) {
	m_controller.setPosition(_pos);
}
