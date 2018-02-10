#include "Collider.h"

Collider::Collider(GameObject * _gameObject, sf::Vector2f _position, sf::Vector2f _size) : m_gameObject (_gameObject), m_position (_position), m_size (_size){
	// Init shape
	m_shape.setOutlineColor(COLLIDER_COLOR);
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineThickness(2.f);
	updateShape();
}

Collider::~Collider() {
}

const sf::Drawable & Collider::getDrawable() {
	return m_shape;
}

void Collider::updateShape() {
	m_shape.setPosition(m_position);
	m_shape.setSize(m_size);
}
