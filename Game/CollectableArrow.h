#pragma once
#include "GameObject.h"
class CollectableArrow : public GameObject {
public:
	enum ARROW_DIRECTION {LEFT, RIGHT};
private:
	// Visual
	sf::RectangleShape m_shape;

	// State
	ARROW_DIRECTION m_direction;
public:
	CollectableArrow(ARROW_DIRECTION _dir);

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};