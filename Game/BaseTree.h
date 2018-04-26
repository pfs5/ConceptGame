#pragma once
#include "GameObject.h"
class BaseTree : public GameObject {
	// Visuals
	sf::RectangleShape m_shape;
	
	// Base animation
	float m_targetHeight;
	float m_currentHeight;

	// Parameters
	const float INIT_HEIGHT = -1600.f;
public:
	BaseTree();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};