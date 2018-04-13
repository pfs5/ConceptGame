#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "AnimationController.h"

class WalkerEnemy : public GameObject, public Enemy {
	const int EYE_COLLIDER_ID =		0;
	const int BODY_COLLIDER_ID =	1;
	const int LEG_COLLIDER_ID =		2;
	const int BASE_COLLIDER_ID =	3;

	enum WALK_STATE {
		STEP_ONE,
		HOLD_ONE,
		STEP_TWO,
		HOLD_TWO,
		DESTROYED,
		DRIVE
	};

	enum DESTRUCTION_STATE {
		START,
		EXPLOSION_ONE,
		EXPLOSION_TWO,
		EXPLOSION_THREE,
		END
	};

	AnimationController m_bodyController;

	sf::Sprite m_sprite;

	WALK_STATE m_walkState;
	DESTRUCTION_STATE m_destructionState;
	float m_counter = 0.f;
	
	const float DRIVE_SPEED = 100.f;
public:
	WalkerEnemy();
	~WalkerEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void destroyLegs();
	void legDestroySequence(float _dt);
	void death();
};