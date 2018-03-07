#pragma once
#include "GameObject.h"
#include "Display.h"
#include "AnimationController.h"

class MainCharacter : public GameObject {
	// Character state
	enum CHARACTER_STATE {
		IDLE,
		JUMPING
	};

	// Visuals
	sf::RectangleShape m_shape;

	// Movement
	int m_direction = 0;

	// State
	CHARACTER_STATE m_characterState;
	float m_additionalGravityMultiplier;

	// Parameters
	const float m_speed = 500.f;
	const float m_jumpVelocity = 600.f;
	const float m_landingGravityMultiplier = 2.f;
public:
	MainCharacter();
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
	void movement(float _dt);
	void extraGravity(float _dt);
	void jump(float _dt);
	void shoot(int _direction);
};

