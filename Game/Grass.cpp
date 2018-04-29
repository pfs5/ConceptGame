#include "Grass.h"
#include "PhysicsEngine.h"
#include "Util.h"
#include "ResourceManager.h"
#include "Debug.h"

Grass::Grass() {
	setObjectTag("Grass");

	// Load
	m_controller.load("grass", false);
	m_grassSound.setBuffer(*ResourceManager::getInstance().getSound("grass_1"));

	// Collider
	auto collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(sf::Vector2f{ 100.f, 80.f });
	collider->setOffset(sf::Vector2f{ 10.f, 0.f });
	collider->setTrigger(true);
	m_colliders.push_back(collider);
}

void Grass::update(float _dt) {
	m_controller.update(_dt);
}

void Grass::draw() {
	m_controller.draw();
}

void Grass::onCollision(Collider * _this, Collider * _other) {
	if (_other->getGameObject()->isObjectTag("Main")) {
		auto pos = _other->getGameObject()->getPosition();
		if (fabsf(pos.x - m_lastTriggeredPosition) > TRIGGER_PRECISION && !m_controller.isPlaying()) {
			m_lastTriggeredPosition = pos.x;

			// Pick random animation
			int anim = Util::randomInt(0, 1);
			std::string animationName = anim == 0 ? "idle1" : "idle2";
			m_controller.playAnimation(animationName);

			// Play audio
			m_grassSound.play();
		}
	}
}

GameObject * Grass::clone() {
	return nullptr;
}

void Grass::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_controller.setPosition(_pos);

	for (auto &col : m_colliders) {
		col->setPosition(_pos);
	}
}
