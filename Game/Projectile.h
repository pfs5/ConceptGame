#pragma once
#include "GameObject.h"
class Projectile : public GameObject{
	// Visuals
	sf::RectangleShape m_shape;

	// Game
	bool m_isStatic = false;

	// Parameters
	float m_destructionDelay = 15.f;
public:
	Projectile();
	~Projectile();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void destroyProjectile();
};

