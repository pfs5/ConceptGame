#pragma once
#include "GameObject.h"
#include "Display.h"
#include "AnimationController.h"
#include "ChainedProjectile.h"

class MainCharacter : public GameObject {
	// Character state
	enum CHARACTER_STATE {
		IDLE,
		JUMPING
	};

	enum CHAIN_STATE {
		UNCHAINED,
		CHAINED
	};

	enum SHOOTING_STATE {
		NOTHING,
		CHARGING_NORMAL,
		CHARGING_CHAINED,
		BOW_RELEASE,
		BOW_RELOAD
	};

	// Visuals
	sf::RectangleShape m_shape;
	AnimationController m_bodyController;
	AnimationController m_bowController;

	// Movement
	int m_direction;

	// State
	CHARACTER_STATE m_characterState;
	float m_additionalGravityMultiplier;

	CHAIN_STATE m_chainState;

	SHOOTING_STATE m_shootingState;
	float m_currentShootingPower;

	sf::Vector2f m_currentPullSpeed;

	// Breaking arrows
	GameObject * m_arrowInCollision;

	ChainedProjectile * m_chain;

	// Parameters
	const float m_speed = 1000.f / 4.f;	//500
	const float m_jumpVelocity = 600.f;
	const float m_landingGravityMultiplier = 1.5f;

	const float m_shootingChargeSpeed = 1000.f;
	const float m_minShootingSpeed = 100.f; // 500
	const float m_maxShootingSpeed = 1500.f;

	const float m_pullSpeed = 1000.f;
	const float m_pullSpeedDecay = 0.95f;

	const float m_bowReleaseSpeed = 20.f;	// percent of full shot time per second

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
	void shootCharge(float _dt);
	void shoot(int _direction, float _velocity = 0.f);
	void shootChain(int _direction, float _velocity = 0.f);
	void pullChain();
	void breakChain();
};

