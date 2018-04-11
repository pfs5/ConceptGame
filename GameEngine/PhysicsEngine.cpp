#include "PhysicsEngine.h"
#include "PhysicsLayers.h"
#include "GameSettings.h"
#include "Display.h"
#include "Debug.h"
#include "VectorOperations.h"
#include "VectorOperations.h"

PhysicsEngine::PhysicsEngine() {
}


PhysicsEngine::~PhysicsEngine() {
}

void PhysicsEngine::update(float _dt) {
	// Move rigid bodies
	for (RigidBody * rb : m_rigidBodies) {
		if (!rb->getGameObject()->isActive()) {
			continue;
		}

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
			if (c->getGameObject()->isActive()) {
				Display::draw(c->getDrawable());
			}
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

void PhysicsEngine::deleteCollider(Collider * _collider) {
	auto colliderPos = std::find(m_colliders.begin(), m_colliders.end(), _collider);

	if (colliderPos != m_colliders.end()) {
		m_colliders.erase(colliderPos);
	}
}

void PhysicsEngine::deleteRigidBody(RigidBody * _rigidbody) {
	auto rbPos = std::find(m_rigidBodies.begin(), m_rigidBodies.end(), _rigidbody);
	if (rbPos != m_rigidBodies.end()) {
		m_rigidBodies.erase(rbPos);
	}
}

bool PhysicsEngine::areColliding(const Collider & _c1, const Collider & _c2) {
	//std::pair<std::string, std::string> pair = std::make_pair<std::string, std::string>(_c1.getGameObject()->getObjectTag(), _c2.getGameObject()->getObjectTag());
	return true;
	//return COLLISION_IGNORE_MAP.find(pair) == COLLISION_IGNORE_MAP.end();
}

inline float calculateT(const sf::Vector2f &_v0, const sf::Vector2f &_v10, const sf::Vector2f &_start, const sf::Vector2f &_direction) {
	return (_v0.y * _direction.x - _start.y * _direction.x - _v0.x * _direction.y + _start.x * _direction.y) /
		(_v10.x * _direction.y - _v10.y * _direction.x);
}

inline sf::Vector2f calculatePoint(const sf::Vector2f _v0, const sf::Vector2f &_v10, float &_t) {
	return _v0 + _v10 * _t;
}

sf::Vector2f PhysicsEngine::raycast(const sf::Vector2f & _start, const sf::Vector2f & _direction, const std::vector<std::string> &_collisionLayers) {
	sf::Vector2f collisionPoint;
	float currentDistance = std::numeric_limits<float>::max();

	int directionX = _direction.x > 0 ? 1 : -1;		// 1 = positive, -1 = negative
	int directionY = _direction.y > 0 ? 1 : -1;		// 1 = positive, -1 = negative

	for (auto &c : m_colliders) {
		if (c->getGameObject()->isActive()) {
			bool colliderInLayer = false;
			for (auto layer : _collisionLayers) {
				if (c->getGameObject()->getObjectTag() == layer) {
					colliderInLayer = true;
					break;
				}
			}

			if (!colliderInLayer) {
				continue;
			}

			// ## Find collision points with collider ##
			sf::Vector2f v0;
			sf::Vector2f v10;
			for (int i = 0; i < 4; ++i) {
				switch (i) {
				case 0:
					v0 = c->getPosition() - c->getSize() / 2.f;
					v10 = sf::Vector2f{ 0.f, c->getSize().y };
					break;
				case 1:
					v10 = sf::Vector2f{ c->getSize().x, 0.f };
					break;
				case 2:
					v0 = c->getPosition() - c->getSize() / 2.f;
					v10 = sf::Vector2f{ 0.f, c->getSize().y };
					break;
				case 3: 
					v10 = sf::Vector2f{ c->getSize().x, 0.f };
					break;
				}

				float t = calculateT(v0, v10, _start, _direction);
				if (t >= 0 && t <= 1) {
					// check if the hit point is in the given direction
					sf::Vector2f hitDir = v10 - v0;
					if ((hitDir.x * directionX > 0) && (hitDir.y * directionY > 0)) {
						sf::Vector2f point = calculatePoint(v0, v10, t);
						float distance = VectorOperations::squaredNorm(point - _start);
						if (distance < currentDistance) {
							currentDistance = distance;
							collisionPoint = point;
						}
					}
				}
			}
		}
	}
	
	return collisionPoint;
}

bool PhysicsEngine::collisionTest(const sf::Vector2f & _point, const std::vector<std::string>& _collisionLayers) {
	for (auto collider : m_colliders) {
		std::string layer = collider->getGameObject()->getObjectTag();
		for (auto colLayer : _collisionLayers) {
			if (layer == colLayer) {
				// Check collision with collider
				sf::Vector2f colliderPos = collider->getPosition();
				sf::Vector2f colliderHalfSize = collider->getSize() / 2.f;
				if (_point.x > colliderPos.x - colliderHalfSize.x && _point.x < colliderPos.x + colliderHalfSize.x &&
					_point.y > colliderPos.y - colliderHalfSize.y && _point.y < colliderPos.y + colliderHalfSize.y) {
					return true;
				}
			}
		}
	}

	return false;
}

void PhysicsEngine::collisionDetection() {
	for (int i = 0; i < m_colliders.size(); ++i) {
		Collider * c1 = m_colliders[i];

		sf::Vector2f position1 = c1->getPosition();
		sf::Vector2f halfSize1 = c1->getSize() / 2.f;

		for (int j = i + 1; j < m_colliders.size(); ++j) {
			Collider * c2 = m_colliders[j];

			// Check if any object is inactive
			if (!c1->getGameObject()->isActive() || !c2->getGameObject()->isActive()) {
				continue;
			}

			sf::Vector2f position2 = c2->getPosition();
			sf::Vector2f halfSize2 = c2->getSize() / 2.f;

			float topDiffX = position1.x - halfSize1.x - (position2.x + halfSize2.x);
			float botDiffX = position2.x - halfSize2.x - (position1.x + halfSize1.x);
			float topDiffY = position1.y - halfSize1.y - (position2.y + halfSize2.y);
			float botDiffY = position2.y - halfSize2.y - (position1.y + halfSize1.y);

			bool directionX = topDiffX > botDiffX;
			bool directionY = topDiffY > botDiffY;

			float diffX = fmaxf(topDiffX, botDiffX);
			float diffY = fmaxf(topDiffY, botDiffY);

			float finalDiff = fmaxf(diffX, diffY);
			
			// Collision
			if (finalDiff < 0.f) {
				int collisionAxis = diffX > diffY ? 0 : 1;	// 0 - x axis, 1 - y axis
				bool direction = diffX > diffY ? directionX : directionY;

				// Collision response - both colliders not triggers
				if (!c1->isTrigger() && !c2->isTrigger() && !PhysicsLayers::layerIgnoreMatrix[c1->getGameObject()->getLayerNumber()][c2->getGameObject()->getLayerNumber()]) {				
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

						float generalDirection = VectorOperations::dotProduct(axisVector, velocity1) > 0.f ? 1 : -1;

						if (generalDirection == direction1) {
							c1->getRigidBody()->setVelocity(newVelocity1);
						}
					}

					if (!c2->isStatic()) {
						float bounce = c2->getRigidBody()->getBounceFactor() / 2.f + 0.5f;
						sf::Vector2f newVelocity2 = velocity2 - VectorOperations::memberwiseMultiplication(velocity2, (axisVector * 2.f)) * bounce;
						//newVelocity2 += VectorOperations::memberwiseMultiplication(velocity1, axisVector) * c2->getRigidBody()->getBounceFactor();

						float generalDirection = VectorOperations::dotProduct(axisVector, velocity2) > 0.f ? 1 : -1;

						if (generalDirection == direction2) {
							c2->getRigidBody()->setVelocity(newVelocity2);
						}
					}
				}

				// Callback method for collisions - called after collision response
				c1->getGameObject()->onCollision(c2);
				c2->getGameObject()->onCollision(c1);
			}
		}
	}
}
