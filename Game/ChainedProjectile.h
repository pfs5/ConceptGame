#pragma once
#include "GameObject.h"
#include "Trail.h"

class ChainedProjectile : public GameObject {
	// Visuals
	sf::RectangleShape m_shape;

	// References
	GameObject * m_playerRef;
	GameObject * m_hitEnemy;

	// Chain
	Trail * m_chain;

	// Game
	bool m_isStatic = false;

	// Parameters
	float m_destructionDelay = 15.f;
public:
	ChainedProjectile();
	~ChainedProjectile();

	void destroyChain();
	void pullChain(sf::Vector2f _pullVector);

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

#pragma region Getters and setters
	inline void setPlayerRef(GameObject * _p) { m_playerRef = _p; };
	inline bool isStatic() { return m_isStatic; };
#pragma endregion
};

