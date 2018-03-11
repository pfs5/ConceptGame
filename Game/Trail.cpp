#include "Trail.h"
#include "VectorOperations.h"
#include "Display.h"
#include "Debug.h"
#include "Util.h"
#include "GameStateManager.h"

Trail::Trail(const sf::Vector2f & _start, const sf::Vector2f & _end) :
	m_start{ _start },
	m_end{ _end },
	m_timer{} {

	initShape();
}

Trail::~Trail() {
}

void Trail::update(float _dt) {
	
}

void Trail::draw() {
	Display::draw(m_shape);
}

void Trail::onCollision(Collider * _other) {
}

GameObject * Trail::clone() {
	return new Trail();
}

void Trail::setPosition(sf::Vector2f _pos) {
}

void Trail::initShape() {
	m_shape.setFillColor(sf::Color::Red);

	sf::Vector2f distance = m_end - m_start;
	m_shape.setSize(sf::Vector2f{ VectorOperations::norm(distance), 5.f });

	m_shape.setOrigin(0.f, 2.5f);

	float angle = Util::radianToDegree(atan2f(distance.y, distance.x));
	m_shape.setRotation(angle);

	m_shape.setPosition(m_start);
}