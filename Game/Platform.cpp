#include "Platform.h"
#include "ResourceManager.h"
#include "Display.h"
#include "PhysicsEngine.h"

Platform::Platform(const sf::Vector2f & _position) :
	m_state{ PLATFORM_STATE::ACTIVE }, m_alpha{ 255 } {

	sf::Texture * tex = ResourceManager::getInstance().getTexture("platform");
	tex->setSmooth(true);

	sf::Vector2f size{ 200, 40 };

	// Sprite
	m_sprite.setTexture(*tex);
	m_sprite.setOrigin(200, 195);

	// Colliders
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(size);

	collider->setStatic(true);

	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(false);
	collider->setTrigger(false, m_rigidBody);

	setPosition(_position);

	setObjectTag("Floor");
	setObjectLayer("Platform");
}

Platform::~Platform() {
}

void Platform::enable() {
	m_state = PLATFORM_STATE::ENABLING;
	setActive(true);
}

void Platform::disable() {
	m_state = PLATFORM_STATE::DISABLING;
}

bool Platform::isEnabled() {
	return m_state == PLATFORM_STATE::ACTIVE;
}

void Platform::update(float _dt) {
	if (m_state == PLATFORM_STATE::ENABLING) {
		m_alpha += _dt * m_fadeSpeed;

		int alpha = (int)m_alpha;
		if (alpha >= 255) {
			m_alpha = 255.f;
			m_state = PLATFORM_STATE::ACTIVE;

			// Disable collision
			setActive(true);
		}

		m_sprite.setColor(sf::Color{ 255, 255, 255, (sf::Uint8) m_alpha });
	}

	if (m_state == PLATFORM_STATE::DISABLING) {
		m_alpha -= _dt * m_fadeSpeed;

		int alpha = (int)m_alpha;
		if (alpha <= 0) {
			m_alpha = 0.f;
			m_state = PLATFORM_STATE::INACTIVE;

			// Disable collision
			setActive(false);
		}

		m_sprite.setColor(sf::Color{ 255, 255, 255, (sf::Uint8) m_alpha });
	}
}

void Platform::draw() {
	Display::draw(m_sprite);
}

void Platform::onCollision(Collider * _other) {
}

GameObject * Platform::clone() {
	return new Platform(m_position);
}

void Platform::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_sprite.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}
