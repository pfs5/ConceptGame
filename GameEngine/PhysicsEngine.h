#pragma once

#include "Collider.h"
#include "RigidBody.h"

/**
	Engine handling all physics in the game including collision detection and response.
**/
class PhysicsEngine {
	std::vector<Collider*> m_colliders;
	std::vector<RigidBody*> m_rigidBodies;
private:
	PhysicsEngine();
	~PhysicsEngine();
public:
	#pragma region Singleton
	static PhysicsEngine & getInstance() {
		static PhysicsEngine instance;
		return instance;
	}
	#pragma endregion

	void update(float _dt);
	void draw();

	// Collider/RigidBody factory
	Collider * createCollider(GameObject * _gameObject);
	RigidBody * createRigidBody(Collider * _collider);

	void deleteCollider(Collider * _collider);
	void deleteRigidBody(RigidBody * _rigidbody);

	// Collision settings
	bool areColliding(const Collider &_c1, const Collider &_c2);

	/**
		Cast a ray from _start in given direction. Returns point where the ray hits a collider
	**/
	sf::Vector2f raycast(const sf::Vector2f &_start, const sf::Vector2f &_direction, const std::vector<std::string> &_collisionLayers);

	bool collisionTest(const sf::Vector2f &_point, const std::vector<std::string> &_collisionLayers);
private:
	void collisionDetection();
};