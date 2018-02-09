#pragma once
#include "GameState.h"
class PlayingState : public GameState {
public:
	PlayingState();
	~PlayingState();

	// Inherited via GameState
	virtual void update(float _dt) override;
	virtual void draw() override;
};

