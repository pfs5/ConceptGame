#include "MainCharacter.h"
#include "Debug.h"
#include "PhysicsEngine.h"
#include "Input.h"

MainCharacter::MainCharacter() {
	m_objectTag = "Main";

	// Init shape
	m_shape.setSize(sf::Vector2f{ 50.f, 50.f });
	m_shape.setFillColor(sf::Color::Blue);

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(m_shape.getSize());
	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(true);
	m_rigidBody->setBounceFactor(.2f);
	collider->setTrigger(false, m_rigidBody);

	// Init transform
	setPosition(sf::Vector2f{ 10.f, 20.f });
}


MainCharacter::~MainCharacter() {
}

void MainCharacter::update(float _dt) {
	// Movement
	float speed = 5.f;
	float dx = 0.f;
	dx += Input::getKey(Input::A) ? -speed : 0.f;
	dx += Input::getKey(Input::D) ? speed : 0.f;
	move(sf::Vector2f{ dx, 0.f });

	// Jump
	float jumpPower = 8 * 1e2;
	if (Input::getKeyDown(Input::SPACE)) {
		m_rigidBody->setVelocity(sf::Vector2f{ 0.f, -jumpPower });
	}
}

void MainCharacter::draw() {
	Display::draw(m_shape);
}

void MainCharacter::onCollision() {
}

void MainCharacter::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}
