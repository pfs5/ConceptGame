#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "AnimationController.h"

class WalkerEnemy : public GameObject, public Enemy {
	const int EYE_COLLIDER_ID =		0;
	const int WHEEL_COLLIDER_ID =	1;
	const int BODY_COLLIDER_ID =	2;
	const int LEG_COLLIDER_ID =		3;
	const int BASE_COLLIDER_ID =	4;

	enum WALK_STATE {
		STEP_ONE,
		HOLD_ONE,
		STEP_TWO,
		HOLD_TWO,
		DESTROYED,
		DRIVE,
		STATIC
	};

	enum DESTRUCTION_STATE {
		START,
		EXPLOSION_ONE,
		EXPLOSION_TWO,
		EXPLOSION_THREE,
		END
	};

	std::vector<EnemyObserver *> m_observers;

	AnimationController m_bodyController;

	sf::Sprite m_sprite;

	WALK_STATE m_walkState;
	DESTRUCTION_STATE m_destructionState;
	float m_counter = 0.f;
	
	const float DRIVE_SPEED = 500.f;
	const sf::Vector2f EYE_COL_OFFSET_1 = sf::Vector2f{ 10.f, -30.f };
	const sf::Vector2f EYE_COL_OFFSET_2 = sf::Vector2f{ 10.f, -20.f };

	const sf::Vector2f WHEEL_COL_OFFSET_1 = sf::Vector2f{ -20.f, -15.f };
	const sf::Vector2f WHEEL_COL_OFFSET_2 = sf::Vector2f{ -20.f, -5.f };
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

	void notifyObservers();

	// Inherited via Enemy
	virtual void attachObserver(EnemyObserver * _o) override;
};