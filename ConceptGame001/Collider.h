#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class GameObject;
class RigidBody;

/**
	Implementation of a 2d box collider
**/
class Collider {
	sf::Vector2f m_position;
	sf::Vector2f m_size;

	bool m_isTrigger = true;
	bool m_isStatic = false;

	GameObject * m_gameObject = nullptr;
	RigidBody * m_rigidBody = nullptr;

	// Visuals
	const sf::Color COLLIDER_COLOR = sf::Color{ 0, 255, 0 };
	sf::RectangleShape m_shape;
	const float m_lineThickness = 2.f;
public:
	Collider(GameObject * _gameObject, sf::Vector2f _position = sf::Vector2f{ 0.f, 0.f }, sf::Vector2f _size = sf::Vector2f{ 0.f, 0.f });
	~Collider();
	
	const sf::Drawable &getDrawable();

	inline void setPosition(const sf::Vector2f &_pos) { m_position = _pos; updateShape(); };
	inline const sf::Vector2f &getPosition() const { return m_position; }; 

	inline void setSize(const sf::Vector2f &_size) { m_size = _size; m_shape.setSize(_size); };
	inline const sf::Vector2f &getSize() const { return m_size; };

	inline bool isTrigger() const { return m_isTrigger; };
	void setTrigger(bool _trigger, RigidBody * _rb = nullptr);

	inline bool isStatic() const { return m_isStatic; };
	inline void setStatic(bool _s) { m_isStatic = _s; };

	inline void setRigidBody(RigidBody * _rb) { m_rigidBody = _rb; };
	inline RigidBody * getRigidBody() { return m_rigidBody; };

	inline GameObject * getGameObject() { return m_gameObject; };
private:
	void updateShape();
};

