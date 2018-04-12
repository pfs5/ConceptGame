#pragma once
#include "GameObject.h"
#include "Trail.h"
#include "PullableEnemy.h"
class RangedEnemy : public PullableEnemy{
	// Visuals
	sf::RectangleShape m_shape;
	const sf::Color m_baseColor{ 0, 102, 255 };
	const sf::Color m_hitColor{ 255, 153, 0 };

	GameObject * m_player;

	sf::Clock m_hitTimer;

	// State
	int m_numberOfHits;
	bool m_died;

	const float m_stunDuration = 2.f;
	const float m_moveDrag = 0.99f;
	const int m_maxHits = 2;
public:
	RangedEnemy();
	~RangedEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

	// Inherited via PullableEnemy
	virtual void pull(sf::Vector2f _pullVector) override;

#pragma region Getters and setters
	inline void setPlayerRef(GameObject *_player) { m_player = _player; };
#pragma endregion
};

