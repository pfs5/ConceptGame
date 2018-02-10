#include "PhysicsEngine.h"
#include "GameSettings.h"
#include "Display.h"
#include "Debug.h"

PhysicsEngine::PhysicsEngine() {
}


PhysicsEngine::~PhysicsEngine() {
}

void PhysicsEngine::update(float _dt) {

	// Move rigid bodies
	for (RigidBody * rb : m_rigidBodies) {
		sf::Vector2f gravity = { 0.f, rb->hasGravity() ? GameSettings::GRAVITY : 0.f};

		sf::Vector2f movement = rb->getVelocity() * _dt + 0.5f * (rb->getAcceleration() + gravity) * powf(_dt, 2);
		rb->getGameObject()->move(movement);

		rb->setVelocity(rb->getVelocity() + rb->getAcceleration() * _dt);
	}
}

void PhysicsEngine::draw() {
	// Draw colliders
	if (GameSettings::SHOW_COLLIDERS) {
		for (Collider * c : m_colliders) {
			Display::draw(c->getDrawable());
		}
	}
}

Collider * PhysicsEngine::createCollider(GameObject * _gameObject) {
	Collider * newCol = new Collider(_gameObject);
	m_colliders.push_back(newCol);

	return newCol;
}

RigidBody * PhysicsEngine::createRigidBody(Collider * _collider) {
	RigidBody * newRb = new RigidBody(_collider->getGameObject());
	_collider->setRigidBody(newRb);

	m_rigidBodies.push_back(newRb);

	return newRb;
}
