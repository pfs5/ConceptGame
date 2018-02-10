#pragma once
#include "GameObject.h"
#include "Display.h"

class MainCharacter : public GameObject {
	// Visuals
	sf::RectangleShape m_shape;

public:
	MainCharacter();
	~MainCharacter();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision() override;

	// Inherited via GameObject
	virtual void setPosition(sf::Vector2f _pos) override;
};

