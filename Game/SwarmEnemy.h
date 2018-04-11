#pragma once
#include "GameObject.h"
class SwarmEnemy : public GameObject {
	sf::CircleShape m_shape;
	sf::CircleShape m_rangeShape;

	bool m_activated;

	// Chain
	SwarmEnemy * m_previous;
	SwarmEnemy * m_next;
public:
	SwarmEnemy(sf::Color _color = sf::Color::Yellow);
	~SwarmEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

#pragma region Getters and setters
public:
	inline void setPrevious(SwarmEnemy * _prev) { m_previous = _prev; };
	inline void setNext(SwarmEnemy * _next) { m_next = _next; };
#pragma endregion
};