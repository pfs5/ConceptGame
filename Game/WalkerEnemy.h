#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "AnimationController.h"

class WalkerEnemy : public GameObject, public Enemy {
	enum WALK_STATE {
		STEP_ONE,
		HOLD_ONE,
		STEP_TWO,
		HOLD_TWO
	};

	AnimationController m_bodyController;

	sf::Sprite m_sprite;

	WALK_STATE m_walkState;
	float m_counter = 0.f;
public:
	WalkerEnemy();
	~WalkerEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};