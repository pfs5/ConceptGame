#pragma once
#include "GameObject.h"
#include "AnimationController.h"
#include <SFML/Audio.hpp>

class Grass : public GameObject {
	// Visuals
	AnimationController m_controller;

	// Audio
	sf::Sound m_grassSound;

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