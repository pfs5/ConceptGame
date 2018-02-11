#include "PhysicsEngine.h"
#include "GameSettings.h"
#include "Display.h"
#include "Debug.h"
#include "VectorOperations.h"

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

		rb->setVelocity(rb->getVelocity() + (rb->getAcceleration() + gravity) * _dt);
	}

	// Collision detection
	collisionDetection();
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

void PhysicsEngine::collisionDetection() {
	for (int i = 0; i < m_colliders.size(); ++i) {
		Collider * c1 = m_colliders[i];

		sf::Vector2f position1 = c1->getPosition();
		sf::Vector2f size1 = c1->getSize();

		for (int j = i + 1; j < m_colliders.size(); ++j) {
			Collider * c2 = m_colliders[j];

			sf::Vector2f position2 = c2->getPosition();
			sf::Vector2f size2 = c2->getSize();

			float topDiffX = position1.x - (position2.x + size2.x);
			float botDiffX = position2.x - (position1.x + size1.x);
			float topDiffY = position1.y - (position2.y + size2.y);
			float botDiffY = position2.y - (position1.y + size1.y);

			bool directionX = topDiffX > botDiffX;
			bool directionY = topDiffY > botDiffY;

			float diffX = fmaxf(topDiffX, botDiffX);
			float diffY = fmaxf(topDiffY, botDiffY);

			float finalDiff = fmaxf(diffX, diffY);
			int collisionAxis = diffX > diffY ? 0 : 1;	// 0 - x axis, 1 - y axis
			bool direction = diffX > diffY ? directionX : directionY;
			
			// Collision
			if (finalDiff < 0.f) {
				// Collision response - both colliders not triggers
				if (!c1->isTrigger() && !c2->isTrigger()) {
					// ## Move object out of collision ##
					sf::Vector2f axisVector{static_cast<float>(1 - collisionAxis), static_cast<float>(collisionAxis)};

					// Base movement
					float moveAmount1 = c1->isStatic() ? 0.f : finalDiff / 2.f;
					float moveAmount2 = c2->isStatic() ? 0.f : finalDiff / 2.f;

					// If one is static, move other for full amount
					moveAmount1 *= c2->isStatic() ? 2.f : 1.f;
					moveAmount2 *= c1->isStatic() ? 2.f : 1.f;

					float direction1 = direction ? -1.f : 1.f;
					float direction2 = direction ? 1.f : -1.f;

					// Move
					c1->getGameObject()->move(axisVector * moveAmount1 * direction1);
					c2->getGameObject()->move(axisVector * moveAmount2 * direction2);

					// ## Phyics collision response ##
					sf::Vector2f velocity1 = c1->getRigidBody()->getVelocity();
					sf::Vector2f velocity2 = c2->getRigidBody()->getVelocity();

					if (!c1->isStatic()) {
						float bounce = c1->getRigidBody()->getBounceFactor() / 2.f + 0.5f;
						sf::Vector2f newVelocity1 = velocity1 - VectorOperations::memberwiseMultiplication(velocity1, (axisVector * 2.f)) * bounce;
						//newVelocity1 += VectorOperations::memberwiseMultiplication(velocity2, axisVector) * c1->getRigidBody()->getBounceFactor();
						c1->getRigidBody()->setVelocity(newVelocity1);
					}

					if (!c2->isStatic()) {
						float bounce = c2->getRigidBody()->getBounceFactor() / 2.f + 0.5f;
						sf::Vector2f newVelocity2 = velocity2 - VectorOperations::memberwiseMultiplication(velocity2, (axisVector * 2.f)) * bounce;
						//newVelocity2 += VectorOperations::memberwiseMultiplication(velocity1, axisVector) * c2->getRigidBody()->getBounceFactor();
						c2->getRigidBody()->setVelocity(newVelocity2);
					}
				}

				// Callback method for collisions - called after collision response
				c1->getGameObject()->onCollision();
				c2->getGameObject()->onCollision();
			}
		}
	}
}
