#pragma once
#include "GameObject.h"
#include "PullableEnemy.h"
#include "CubeObject.h"
class BasicEnemy : public PullableEnemy {
	enum ENEMY_STATE {
		ATTACKING,
		HIT
	};

	// Visuals
	sf::RectangleShape m_shape;
	const sf::Color m_baseColor{51, 204, 255};
	const sf::Color m_hitColor{ 255, 153, 0 };

	GameObject * m_player;

	// State
	ENEMY_STATE m_state;
	int m_numberOfHits;
	bool m_died;

	// Parameters
	const float m_movementSpeed = 100.f;

	const float m_recoilSlowdown = 0.9f;
	const float m_recoilMinSpeed = 20.f;

	const int m_maxHits = 2;
public:
	BasicEnemy();
	~BasicEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

	// Inherited via PullableEnemy
	virtual void pull(sf::Vector2f _pullVector) override;

#pragma region Getters and setters
	inline void setPlayerRef(GameObject *_player) { m_player = _player; };
#pragma endregion

};

