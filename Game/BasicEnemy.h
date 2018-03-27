#pragma once
#include "GameObject.h"
#include "PullableEnemy.h"
#include "CubeObject.h"
#include "AnimationController.h"

class BasicEnemy : public PullableEnemy {
public:
	enum ENEMY_TYPE {
		CHASER,			// chases player, cant jump
		JUMPER,			// chases player, can jump
		SPLITTER		// chaser that splits into two in death
	};

private:
	enum ENEMY_STATE {
		ATTACKING,
		HIT
	};

	// Visuals
	const sf::Color m_baseColor{51, 204, 255};
	const sf::Color m_hitColor{ 255, 153, 0 };

	AnimationController m_controller;

	GameObject * m_player;

	// State
	ENEMY_STATE m_state;
	int m_numberOfHits;
	bool m_died;
	bool m_jumpReady;

	float m_movementSpeed;
	ENEMY_TYPE m_type;

	// Parameters
	const float m_recoilSlowdown = 0.9f;
	const float m_recoilMinSpeed = 20.f;

	const int m_maxHits = 2;
public:
	BasicEnemy(ENEMY_TYPE _type, float _speed);
	~BasicEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

	// Inherited via PullableEnemy
	virtual void pull(sf::Vector2f _pullVector) override;

private:
	void chaserAIUpdate();
	void jumperAIUpdate();

	void death();
#pragma region Getters and setters
public:
	inline void setPlayerRef(GameObject *_player) { m_player = _player; };
#pragma endregion

};

