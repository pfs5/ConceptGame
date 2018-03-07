#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class GameObject;

/**
	Implements the rigid body concept and enables physics to be applied to objects
	including gravity, applying forces, velocity and acceleration concepts and collision response (bounce, ...)
	
	Added to game objects to enable phyics.
**/
class RigidBody {
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	bool m_hasGravity = true;
	float m_bounceFactor = .3f;

	GameObject * m_gameObject = nullptr;
public:
	RigidBody(GameObject * _g);
	~RigidBody();

#pragma region Getters and setters
	inline sf::Vector2f getVelocity() { return m_velocity; };
	inline void setVelocity(sf::Vector2f _v) { m_velocity = _v; };

	inline sf::Vector2f getAcceleration() { return m_acceleration; };
	inline void setAcceleration(sf::Vector2f _a) { m_acceleration = _a; };

	inline bool hasGravity() { return m_hasGravity; };
	inline void setGravity(bool _grav) { m_hasGravity = _grav; };

	inline float getBounceFactor() { return m_bounceFactor; };
	inline void setBounceFactor(float _b) { m_bounceFactor = _b; };

	inline GameObject * getGameObject() { return m_gameObject; };
#pragma endregion
};

