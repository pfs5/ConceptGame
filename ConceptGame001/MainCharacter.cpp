#include "MainCharacter.h"
#include "Debug.h"
#include "PhysicsEngine.h"
#include "Input.h"

MainCharacter::MainCharacter() {
	// Init shape
	m_shape.setSize(sf::Vector2f{ 50.f, 50.f });
	m_shape.setFillColor(sf::Color::Blue);

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(m_shape.getSize());
	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(false);

	// Init transform
	setPosition(sf::Vector2f{ 10.f, 20.f });
}


MainCharacter::~MainCharacter() {
}

void MainCharacter::update(float _dt) {
	// Move
	float dx = 0;
	float dy = 0;
	float speed = 10;

	if (Input::getKey(Input::W)) {
		dy -= speed;
	}
	if (Input::getKey(Input::A)) {
		dx -= speed;
	}
	if (Input::getKey(Input::S)) {
		dy += speed;
	}
	if (Input::getKey(Input::D)) {
		dx += speed;
	}

	sf::Vector2f velocity = m_rigidBody->getVelocity() + sf::Vector2f{ dx, dy };
	velocity = velocity * 0.98f;

	m_rigidBody->setVelocity(velocity);

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
