#pragma once
#include "EnemyObserver.h"
class Enemy {
public:
	virtual void attachObserver(EnemyObserver * _o) = 0;
};