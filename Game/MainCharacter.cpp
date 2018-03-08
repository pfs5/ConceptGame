#include "MainCharacter.h"
#include "Debug.h"
#include "PhysicsEngine.h"
#include "Input.h"
#include "GameStateManager.h"
#include "FloatOperations.h"
#include "GameSettings.h"

MainCharacter::MainCharacter(GameObject *_projectile):
	m_characterState {CHARACTER_STATE::IDLE},
	m_shootingState {SHOOTING_STATE::NOTHING},
	m_currentShootingPower{ m_minShootingSpeed },
	m_additionalGravityMultiplier { 0.f },
	m_projectile{ _projectile }  {

	m_objectTag = "Main";

	// Init shape
	m_shape.setSize(sf::Vector2f{ 30.f, 50.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setFillColor(sf::Color::Blue);

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(m_shape.getSize());
	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(true);
	m_rigidBody->setBounceFactor(0.1f);
	collider->setTrigger(false, m_rigidBody);

	// Init transform
	setPosition(sf::Vector2f{ 10.f, 20.f });
}

MainCharacter::~MainCharacter() {
}

void MainCharacter::update(float _dt) {
	movement(_dt);
	extraGravity(_dt);
	jump(_dt);
	shootCharge(_dt);
}

void MainCharacter::draw() {
	Display::draw(m_shape);
}

void MainCharacter::onCollision(Collider * _other) {
	if (_other->getGameObject()->getObjectTag() == "Floor" || _other->getGameObject()->getObjectTag() == "Arrow") {
		m_characterState = CHARACTER_STATE::IDLE;
		m_additionalGravityMultiplier = 0.f;
	}
}

void MainCharacter::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}

GameObject * MainCharacter::clone() {
	return nullptr;
}

void MainCharacter::movement(float _dt) {
	float dx = 0.f;

	if (Input::getKey(Input::A)) {
		dx += -m_speed;
		m_direction = -1;
	}

	if (Input::getKey(Input::D)) {
		dx += m_speed;
		m_direction = 1;
	}

	dx *= _dt;

	move(sf::Vector2f{ dx, 0.f });
}

void MainCharacter::extraGravity(float _dt) {
	// Apply extra gravity to character
	sf::Vector2f vel = m_rigidBody->getVelocity();
	vel.y += GameSettings::GRAVITY * m_additionalGravityMultiplier * _dt;
	m_rigidBody->setVelocity(vel);
}

void MainCharacter::jump(float _dt) {
	if (m_characterState == CHARACTER_STATE::IDLE) {
		if (Input::getKeyDown(Input::SPACE)) {
			m_rigidBody->setVelocity(sf::Vector2f{ 0.f, -m_jumpVelocity });
			m_characterState = CHARACTER_STATE::JUMPING;
		}
	}
	
	// Landing
	if (m_characterState == CHARACTER_STATE::JUMPING) {
		if (Input::getKeyUp(Input::SPACE) || m_rigidBody->getVelocity().y > 0) {
			m_additionalGravityMultiplier = m_landingGravityMultiplier;
		}
	}
}

void MainCharacter::shootCharge(float _dt) {
	if (Input::getKeyDown(Input::ENTER)) {
		m_currentShootingPower = m_minShootingSpeed;
		m_shootingState = SHOOTING_STATE::CHARGING;
	}
	
	if (Input::getKeyUp(Input::ENTER)) {
		shoot(m_direction, m_currentShootingPower);
		m_shootingState = SHOOTING_STATE::NOTHING;
	}

	if (m_shootingState == SHOOTING_STATE::CHARGING) {
		m_currentShootingPower = fminf(m_currentShootingPower + m_shootingChargeSpeed * _dt, m_maxShootingSpeed);
	}
}

void MainCharacter::shoot(int _direction, float _velocity) {
	GameObject * projectile = GameStateManager::instantiate(m_projectile, 1);
	
	sf::Vector2f projPos = m_position + sf::Vector2f{ m_shape.getSize().x * static_cast<float>(_direction), 0.f };
	projectile->setPosition(projPos);

	projectile->getRigidBody()->setVelocity(sf::Vector2f{_direction * _velocity, 0.f});

	projectile->setActive(true);
}
