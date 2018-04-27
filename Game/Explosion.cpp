#include "Explosion.h"
#include "GameStateManager.h"
#include "Debug.h"

Explosion::Explosion(sf::Vector2f _position, float _size, std::string _name) :
	m_size{ _size }, m_name{ _name } {
	m_controller.load("explosion");
	m_controller.playAnimation(_name);
	setPosition(_position);
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

void Explosion::onCollision(Collider * _this, Collider * _other) {
}

GameObject * Explosion::clone() {
	return new Explosion(m_position, m_size, m_name);
}

void Explosion::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_controller.setPosition(_pos);
}
