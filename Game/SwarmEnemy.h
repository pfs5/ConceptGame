#pragma once
#include "GameObject.h"
class SwarmEnemy : public GameObject {
public:
	SwarmEnemy();
	~SwarmEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};