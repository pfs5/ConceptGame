#include "Trail.h"
#include "VectorOperations.h"
#include "Display.h"
#include "Debug.h"
#include "Util.h"
#include "GameStateManager.h"
#include "ResourceManager.h"

#include <cmath>

Trail::Trail(std::string _name, const sf::Vector2f & _start, const sf::Vector2f & _end) :
	m_name{ _name },
	m_start{ _start },
	m_end{ _end },
	m_timer{} {

	sf::Texture *texture = ResourceManager::getInstance().getTexture("chain_idle");
	texture->setRepeated(true);
	texture->setSmooth(true);

	m_sprite.setTexture(*texture);

	updateVisual();
}

Trail::~Trail() {
}

void Trail::update(float _dt) {
}

void Trail::draw() {

	//m_controller.draw();
	Display::draw(m_sprite);
}

void Trail::onCollision(Collider * _other) {
}

GameObject * Trail::clone() {
	return new Trail(m_name);
}

void Trail::setPosition(sf::Vector2f _pos) {
}

void Trail::updateVisual() {

	sf::Vector2u trailSize = m_sprite.getTexture()->getSize();

	sf::Vector2f distance = m_end - m_start;
	m_sprite.setTextureRect(sf::IntRect(0, 0, (int)VectorOperations::norm(distance), trailSize.y));

	m_sprite.setOrigin(VectorOperations::norm(distance), trailSize.y / 2);

	float angle = Util::radianToDegree(atan2f(distance.y, distance.x));
	m_sprite.setRotation(angle);

	m_sprite.setPosition(m_end);
}

void Trail::setPositions(const sf::Vector2f & _start, const sf::Vector2f & _end) {
	sf::Vector2f dir = _start - _end;
	dir /= VectorOperations::norm(dir);

	dir.x = ceilf(dir.x);
	dir.y = 0;

	m_start = _start + m_startOffset;
	m_end = _end + VectorOperations::memberwiseMultiplication(m_endOffset, dir);

	updateVisual();
};
