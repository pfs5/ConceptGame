#pragma once
#include "GameObject.h"
#include "AnimationController.h"

#include <SFML/Audio.hpp>
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

	// Audio
	sf::Sound m_hitSound;
	sf::Sound m_shootSound;

	// State
	ARROW_DIRECTION m_direction;
	bool m_isStuck;
	bool m_wasShot;

	// Observers
	std::vector<CollectableArrowObserver*> m_observers;

	// Parameters
	const float MAX_PITCH_OFFSET = 0.1f;
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