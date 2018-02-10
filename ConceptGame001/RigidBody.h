#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class GameObject;

class RigidBody {
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	bool m_hasGravity = true;

	GameObject * m_gameObject = nullptr;
public:
	RigidBody(GameObject * _g);
	~RigidBody();

	inline bool hasGravity() { return m_hasGravity; };
	inline void setGravity(bool _grav) { m_hasGravity = _grav; };

	inline sf::Vector2f getVelocity() { return m_velocity; };
	inline void setVelocity(sf::Vector2f _v) { m_velocity = _v; };

	inline sf::Vector2f getAcceleration() { return m_acceleration; };
	inline void setAcceleration(sf::Vector2f _a) { m_acceleration = _a; };

	inline GameObject * getGameObject() { return m_gameObject; };
};

