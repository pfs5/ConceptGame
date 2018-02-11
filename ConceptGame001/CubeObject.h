#pragma once
#include "GameObject.h"
#include "PhysicsEngine.h"
#include "Display.h"

class CubeObject : public GameObject{
	sf::RectangleShape m_shape;
public:
	CubeObject(sf::Vector2f _size, sf::Vector2f _position, bool _static = false, bool _gravity = false);
	~CubeObject();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

