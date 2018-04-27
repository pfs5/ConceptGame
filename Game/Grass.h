#pragma once
#include "GameObject.h"
#include "AnimationController.h"

class Grass : public GameObject {
	// Visuals
	AnimationController m_controller;

	// State
	float m_lastTriggeredPosition;

	// Parameters
	const float TRIGGER_PRECISION = 10.f;
public:
	Grass();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};