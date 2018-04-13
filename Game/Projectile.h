#pragma once
#include "GameObject.h"
#include "AnimationController.h"
class Projectile : public GameObject{
	// Visuals
	AnimationController m_controller;

	// Game
	bool m_isStatic = false;
	bool m_isDestroyed = false;

	GameObject *m_attachedObject = nullptr;
	sf::Vector2f m_attachedOffset;

	// Parameters
	float m_destructionDelay = 10.f;

	int m_direction;
public:
	Projectile(int _direction = 1);
	~Projectile();

	void breakArrow();
	void attachArrow(GameObject *_object);
	void destroyArrow();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

#pragma region Getters and Setters
	inline bool isStatic() { return m_isStatic; };
#pragma endregion
private:
	void destroyProjectile();
	void destroyObject();
};

