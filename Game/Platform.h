#pragma once
#include "GameObject.h"
class Platform : public GameObject {
	enum PLATFORM_STATE {
		ACTIVE,
		INACTIVE,
		ENABLING,
		DISABLING
	};
	
	PLATFORM_STATE m_state;
	float m_alpha;

	sf::Sprite m_sprite;

	// Parameters
	const float m_fadeSpeed = 500;

public:
	Platform(const sf::Vector2f &_position);
	~Platform();

	void enable();
	void disable();

	bool isEnabled();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

