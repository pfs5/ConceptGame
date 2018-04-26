#pragma once
#include "GameObject.h"
#include "AnimationController.h"
class CollectableArrowObserver {
public:
	virtual void notify() = 0;
};

class CollectableArrow : public GameObject {
public:
	enum ARROW_DIRECTION {LEFT, RIGHT};
private:
	// Visual
	sf::RectangleShape m_shape;
	AnimationController m_controller;

	// State
	ARROW_DIRECTION m_direction;

	// Observers
	std::vector<CollectableArrowObserver*> m_observers;
public:
	CollectableArrow(ARROW_DIRECTION _dir);

	// Observer methods
	void attachObserver(CollectableArrowObserver * _o);

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void notifyObservers();
};