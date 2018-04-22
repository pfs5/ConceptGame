#pragma once
#include "GameObject.h"
class Platform : public GameObject {
	enum PLATFORM_STATE {
		ACTIVE,
		INACTIVE,
		TRIGGERED,
		ENABLING,
		DISABLING
	};
	
	PLATFORM_STATE m_state;
	float m_alpha;

	sf::Sprite m_sprite;

	// Spring physics
	float m_velocity;
	float m_baseHeight;

	float m_disableCounter;
	float m_disableDelay;
	float m_enableCounter;

	// Parameters
	const float m_fadeSpeed = 500;
	const float m_playerDisableDelay = 0.5f;
	const float m_enableDelay = 1.f;

	const float m_responseVelocity = 200.f;
	const float m_responseDamping = 200.f;

	// parameters for responding to player jump
	const float m_jumpResponseWidth = 110.f;
	const float m_jumpResponseHeight = -60.f;

public:
	Platform(const sf::Vector2f &_position);
	~Platform();

	void enable();
	void disable(float _delay = 0.f);

	bool isEnabled();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

