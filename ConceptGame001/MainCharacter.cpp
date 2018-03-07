#include "MainCharacter.h"
#include "Debug.h"
#include "PhysicsEngine.h"
#include "Input.h"
#include "GameStateManager.h"
#include "FloatOperations.h"

MainCharacter::MainCharacter(GameObject * arrow) {
	m_objectTag = "Main";
	m_arrow = arrow;

	// Init shape
	m_shape.setSize(sf::Vector2f{ 200.f, 200.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setFillColor(sf::Color::Blue);

	// Animation controller
	m_animationController.load("mainCharacter");

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

	// Parameters
	m_speed = 600.f / 2;
}

MainCharacter::~MainCharacter() {
}

void MainCharacter::update(float _dt) {
	// Animations
	m_animationController.update(_dt);

	// Movement
	float dx = 0.f;

	if (Input::getKey(Input::A)) {
		dx += -m_speed;
		m_direction = -1;
	}

	if (Input::getKey(Input::D)) {
		dx += m_speed;
		m_direction = 1;
	}

	// Animations
	if (dx > 0.f) {
		m_animationController.setTrigger("walk_right");
	}
	
	if (dx < 0.f) {
		m_animationController.setTrigger("walk_left");
	}

	if (FloatOperations::compare(dx, 0.f) == 0) {
		m_animationController.setTrigger("idle");
	}

	dx *= _dt;

	move(sf::Vector2f{ dx, 0.f });

	// Jump
	float jumpPower = 5 * 1e2;
	if (Input::getKeyDown(Input::SPACE)) {
		m_rigidBody->setVelocity(sf::Vector2f{ 0.f, -jumpPower });
	}

	// Shoot
	if (Input::getKeyDown(Input::ENTER)) {
		shoot(m_direction);
	}
}

void MainCharacter::draw() {
	m_animationController.draw();
}

void MainCharacter::onCollision(Collider * _other) {
}

void MainCharacter::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);
	m_animationController.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}

GameObject * MainCharacter::clone() {
	return nullptr;
}

void MainCharacter::shoot(int _direction) {
	// Create arrow
	GameObject * arrow = GameStateManager::instantiate(m_arrow);
	sf::Vector2f arrowPos = m_position + sf::Vector2f{ m_shape.getSize().x * static_cast<float>(_direction), 0.f };
	arrow->setPosition(arrowPos);
	arrow->getRigidBody()->setVelocity(sf::Vector2f{ _direction * 1000.f, 0.f });

	arrow->setActive(true);
}
