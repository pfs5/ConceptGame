#include "GameObject.h"

GameObject::GameObject() {
}

GameObject::~GameObject() {
	delete m_rigidBody;
	for (Collider * c : m_colliders) {
		delete c;
	}
}

void GameObject::setRigidBody(RigidBody * _rb) {
	m_rigidBody = _rb;
}

void GameObject::addCollider(Collider * _c) {
	m_colliders.push_back(_c);
}

void GameObject::move(sf::Vector2f _delta) {
	setPosition(getPosition() + _delta);
}
