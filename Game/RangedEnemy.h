#pragma once
#include "GameObject.h"
class RangedEnemy : public GameObject{

	sf::RectangleShape m_shape;

	GameObject * m_player;

	// State
	int m_numberOfHits;
	bool m_died;

	const int m_maxHits = 2;
public:
	RangedEnemy();
	~RangedEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

#pragma region Getters and setters
	inline void setPlayerRef(GameObject *_player) { m_player = _player; };
#pragma endregion

};

