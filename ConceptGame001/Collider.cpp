#include "Collider.h"

Collider::Collider(GameObject * _gameObject, sf::Vector2f _position, sf::Vector2f _size) : m_gameObject (_gameObject), m_position (_position), m_size (_size){
	// Init shape
	m_shape.setOutlineColor(COLLIDER_COLOR);
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineThickness(m_lineThickness);

	updateShape();
}

Collider::~Collider() {
}

const sf::Drawable & Collider::getDrawable() {
	return m_shape;
}

void Collider::setTrigger(bool _trigger, RigidBody * _rb) {
	if (!_trigger && !_rb) {
		throw new std::exception("Not trigger colliders require rigid bodies");
	}
	
	m_isTrigger = _trigger;
	m_rigidBody = _rb;
}

void Collider::updateShape() {
	m_shape.setPosition(m_position + sf::Vector2f(m_lineThickness, m_lineThickness));
	m_shape.setSize(m_size - sf::Vector2f(m_lineThickness, m_lineThickness) * 2.f);
	m_shape.setOrigin(m_shape.getSize() / 2.f);
}
