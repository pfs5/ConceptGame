#pragma once
#include "GameObject.h"
class BaseTree : public GameObject {
	// Visuals
	sf::Sprite m_sprite;
	
	// Base animation
	float m_targetHeight;
	float m_currentHeight;

	// Parameters
	const float MAX_HEIGHT = 800.f;
	const float ANIMATION_SPEED = 2.f;
public:
	BaseTree();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void updateHealth(float _hp);
};