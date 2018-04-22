#include "Platform.h"
#include "ResourceManager.h"
#include "Display.h"
#include "PhysicsEngine.h"
#include "FloatOperations.h"
#include "Debug.h"

Platform::Platform(const sf::Vector2f & _position) :
	m_state{ PLATFORM_STATE::ACTIVE }, m_alpha{ 255 }, m_velocity{ 0.f }, m_disableCounter{ 0.f } {

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

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(false);
	collider->setTrigger(false, m_rigidBody);

	m_colliders.push_back(collider);

	setPosition(_position);
	m_baseHeight = getPosition().y;

	setObjectTag("Floor");
	setObjectLayer("Platform");
}

Platform::~Platform() {
}

void Platform::enable() {
	m_state = PLATFORM_STATE::ENABLING;
	
	// enable colliders
	for (auto &col : m_colliders) {
		col->setTrigger(false, m_rigidBody);
	}
}

void Platform::disable(float _delay) {
	m_disableCounter = 0.f;
	m_disableDelay = _delay;
	m_enableCounter = 0.f;
	m_state = PLATFORM_STATE::DISABLING;
}

bool Platform::isEnabled() {
	return m_state == PLATFORM_STATE::ACTIVE;
}

void Platform::update(float _dt) {
	if (m_state == PLATFORM_STATE::TRIGGERED) {
		// Apply spring physics
		move(sf::Vector2f{ 0.f, m_velocity * _dt });

		float heightOffset = getPosition().y - m_baseHeight;
		m_velocity -= heightOffset *  m_responseDamping * _dt;

		if (heightOffset < 0.f) {
			disable(m_playerDisableDelay);
		}
	}
	else if (m_state == PLATFORM_STATE::ENABLING) {
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
	else if (m_state == PLATFORM_STATE::DISABLING) {
		if ((m_disableCounter += _dt) > m_disableDelay) {
			m_alpha -= _dt * m_fadeSpeed;

			int alpha = (int)m_alpha;
			if (alpha <= 0) {
				m_alpha = 0.f;
				m_state = PLATFORM_STATE::INACTIVE;

				// Disable collision
				for (auto &col : m_colliders) {
					col->setTrigger(true);
				}
			}

			m_sprite.setColor(sf::Color{ 255, 255, 255, (sf::Uint8) m_alpha });
		}
	}
	else if (m_state == PLATFORM_STATE::INACTIVE) {
		// enable after delay
		if ((m_enableCounter += _dt) > m_enableDelay) {
			enable();
		}
	}
}

void Platform::draw() {
	Display::draw(m_sprite);
}

void Platform::onCollision(Collider * _this, Collider * _other) {
	if (_other->getGameObject()->isObjectTag("Main") && m_state == PLATFORM_STATE::ACTIVE) {
		sf::Vector2f playerDistance = _other->getGameObject()->getPosition() - getPosition();
		if (FloatOperations::compare(playerDistance.y, m_jumpResponseHeight) == 0 && fabsf(playerDistance.x) <= m_jumpResponseWidth) {
			m_state = PLATFORM_STATE::TRIGGERED;
			m_velocity = m_responseVelocity;
		}
	}
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
