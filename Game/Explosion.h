#pragma once
#include "GameObject.h"
#include "AnimationController.h"

class Explosion : public GameObject {
	
	AnimationController m_controller;
	
	sf::Vector2f m_position;
	float m_size;
	std::string m_name;
public:
	Explosion(sf::Vector2f _position, float _size, std::string _name);
	~Explosion();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

