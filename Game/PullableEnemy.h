#pragma once
#include "GameObject.h"
class PullableEnemy : public GameObject {
public:
	virtual void pull(sf::Vector2f _pullVector) = 0;
};