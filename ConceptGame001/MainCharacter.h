#pragma once
#include "GameObject.h"
#include "Display.h"
#include "AnimationController.h"

class MainCharacter : public GameObject {
	// Visuals
	sf::RectangleShape m_shape;
	AnimationController m_animationController;

	GameObject * m_arrow;

	int m_direction = 0;

	// Parameters
	float m_speed;
public:
	MainCharacter(GameObject * arrow);
	~MainCharacter();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;

	// Inherited via GameObject
	virtual void setPosition(sf::Vector2f _pos) override;

	// Inherited via GameObject
	virtual GameObject * clone() override;

private:
	void shoot(int _direction);
};

