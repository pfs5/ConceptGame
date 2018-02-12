#pragma once
#include "GameObject.h"
#include "Display.h"
#include "PhysicsEngine.h"

class Arrow : public GameObject {
	// Visuals
	sf::RectangleShape m_shape;
public:
	Arrow();
	
	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision() override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};