#pragma once
#include "GameState.h"
#include "PhysicsEngine.h"

class PlayingState : public GameState {

	std::vector<GameObject*> m_gameObjects;

public:
	PlayingState();
	~PlayingState();

	// Inherited via GameState
	virtual void update(float _dt) override;
	virtual void draw() override;
};

