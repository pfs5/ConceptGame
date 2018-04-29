#pragma once
#include "GameObject.h"
#include "Display.h"
#include "AnimationController.h"
#include "ChainedProjectile.h"
#include <SFML/Audio.hpp>

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

	enum AMMO_STATE {
		NO_AMMO,
		YES_AMMO
	};

#pragma region Parameters
	const float m_speed = 2000.f / 4.f;	//500
	const float m_jumpVelocity = 650.f;
	const float m_landingGravityMultiplier = 1.5f;
	const float m_maxLandSpeed = 1200.f;

	const float m_shootingChargeSpeed = 2500.f;
	const float m_minShootingSpeed = 100.f; // 500
	const float m_maxShootingSpeed = 1500.f;

	const float m_shootingChainSpeed = 1000.f;

	const float m_pullSpeed = 800.f;
	const float m_pullSpeedDecay = 0.99f;

	const float m_bowReleaseSpeed = 20.f;	// percent of full shot time per second

	const int m_maxArrows = 5;
	const int m_initalArrows = 1;

	const float m_blinkingFrequency = 4.f;	// how often does the character blink in secs
	const float m_blinkDuraction = 0.25f;	// duration of a blink in secs
#pragma endregion

	// Visuals
	sf::RectangleShape m_shape;
	AnimationController m_bodyController;
	AnimationController m_bowController;
	AnimationController m_arrowsController;
	AnimationController m_eyesController;

	// Audio
	sf::Sound m_jumpSound;
	sf::Sound m_bowDrawSound;
	sf::Sound m_bowShootSound;

	// Movement
	int m_direction;

	// State
	CHARACTER_STATE m_characterState;
	float m_additionalGravityMultiplier;

	CHAIN_STATE m_chainState;

	SHOOTING_STATE m_shootingState;
	AMMO_STATE m_ammoState;
	float m_currentShootingPower;
	int m_numberOfArrows;

	sf::Vector2f m_currentPullSpeed;

	bool m_eyesOpen;
	float m_eyeCounter;

	// Breaking arrows
	GameObject * m_arrowInCollision;

	ChainedProjectile * m_chain;

	// Particle system
	GameObject * m_particleSystem = nullptr;
public:
	MainCharacter();
	~MainCharacter();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;

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
	void eyeControll(float _dt);
};

