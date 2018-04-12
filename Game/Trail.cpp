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

	sf::Texture *textureIdle = ResourceManager::getInstance().getTexture("chain_idle");
	textureIdle->setRepeated(true);
	textureIdle->setSmooth(true);

	m_spriteIdle.setTexture(*textureIdle);

	sf::Texture *textureHit = ResourceManager::getInstance().getTexture("chain_hit");
	textureHit->setRepeated(true);
	textureHit->setSmooth(true);

	m_spriteHit.setTexture(*textureHit);

	m_currentSprite = &m_spriteIdle;

	updateVisual();
}

Trail::~Trail() {
}

void Trail::setHit(bool _hit) {
	m_currentSprite = _hit ? &m_spriteHit : &m_spriteIdle;
}

void Trail::update(float _dt) {
}

void Trail::draw() {

	//m_controller.draw();
	Display::draw(*m_currentSprite);
}

void Trail::onCollision(Collider * _this, Collider * _other) {
}

GameObject * Trail::clone() {
	return new Trail(m_name);
}

void Trail::setPosition(sf::Vector2f _pos) {
}

void Trail::updateVisual() {

	sf::Vector2u trailSize = m_currentSprite->getTexture()->getSize();

	sf::Vector2f distance = m_end - m_start;
	m_currentSprite->setTextureRect(sf::IntRect(0, 0, (int)VectorOperations::norm(distance), trailSize.y));

	m_currentSprite->setOrigin(VectorOperations::norm(distance), trailSize.y / 2);

	float angle = Util::radianToDegree(atan2f(distance.y, distance.x));
	m_currentSprite->setRotation(angle);

	m_currentSprite->setPosition(m_end);
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
