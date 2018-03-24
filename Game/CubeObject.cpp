#include "CubeObject.h"

CubeObject::CubeObject(sf::Vector2f _size, sf::Vector2f _position, bool _static, bool _gravity, sf::Color _color) : m_isStatic{ _static } {
	m_shape.setFillColor(_color);
	m_shape.setSize(_size);

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(m_shape.getSize());
	m_shape.setOrigin(m_shape.getSize() / 2.f);

	collider->setStatic(_static);

	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(_gravity);
	collider->setTrigger(false, m_rigidBody);

	setPosition(_position);
}

CubeObject::~CubeObject() {
}

void CubeObject::update(float _dt) {
}

void CubeObject::draw() {
	//Display::draw(m_shape);
}

void CubeObject::onCollision(Collider * _other) {
}

void CubeObject::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}
}

GameObject * CubeObject::clone() {
	return new CubeObject(m_shape.getSize(), m_position, m_isStatic, getRigidBody()->hasGravity(), m_shape.getFillColor());
}