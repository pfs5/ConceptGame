#pragma once

#include "Collider.h"
#include "RigidBody.h"

class PhysicsEngine {
	std::vector<Collider*> m_colliders;
	std::vector<RigidBody*> m_rigidBodies;

private:
	PhysicsEngine();
	~PhysicsEngine();
public:
	static PhysicsEngine & getInstance() {
		static PhysicsEngine instance;
		return instance;
	}

	void update(float _dt);
	void draw();

	// Collider factory
	Collider * createCollider(GameObject * _gameObject);
	RigidBody * createRigidBody(Collider * _collider);

private:
	void collisionDetection();
};

