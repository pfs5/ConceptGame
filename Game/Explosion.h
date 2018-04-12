#pragma once
#include "GameObject.h"
#include "AnimationController.h"

class Explosion : public GameObject {
	
	AnimationController m_controller;
	sf::Vector2f m_position;
public:
	Explosion(sf::Vector2f _position);
	~Explosion();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

