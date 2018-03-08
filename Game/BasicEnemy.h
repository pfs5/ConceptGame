#pragma once
#include "GameObject.h"
#include "CubeObject.h"
class BasicEnemy : public GameObject {
	CubeObject m_cube;

	GameObject * m_player;

	// Parameters
	const float m_movementSpeed = 100.f;
public:
	BasicEnemy();
	~BasicEnemy();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
	inline void setActive(bool _value) override { m_isActive = _value; m_cube.setActive(_value); };

#pragma region Getters and setters
	inline void setPlayerRef(GameObject *_player) { m_player = _player; };
#pragma endregion
};

