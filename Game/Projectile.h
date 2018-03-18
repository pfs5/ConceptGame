#pragma once
#include "GameObject.h"
#include "AnimationController.h"
class Projectile : public GameObject{
	// Visuals
	AnimationController m_controller;

	// Game
	bool m_isStatic = false;
	bool m_isDestroyed = false;

	// Parameters
	float m_destructionDelay = 10.f;

	int m_direction;
public:
	Projectile(int _direction = 1);
	~Projectile();

	void breakArrow();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void destroyProjectile();
	void destroyObject();
};

