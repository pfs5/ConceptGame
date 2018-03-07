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

RigidBody * GameObject::getRigidBody() {
	return m_rigidBody;
}

void GameObject::addCollider(Collider * _c) {
	m_colliders.push_back(_c);
}

void GameObject::move(sf::Vector2f _delta) {
	setPosition(getPosition() + _delta);
}

void GameObject::setObjectLayer(std::string layer) {
	int layerNumber = PhysicsLayers::layerNumber(layer);
	m_physicsLayer = layerNumber >= 0 ? layerNumber : m_physicsLayer;
}

std::string GameObject::getObjectLayer() {
	return PhysicsLayers::layerName(m_physicsLayer);
}

int GameObject::getLayerNumber() {
	return m_physicsLayer;
}
