#pragma once
#include "GameState.h"
#include "PhysicsEngine.h"
#include "Map.h"

//#define DEBUG_MODE

class PlayingState : public GameState {
	std::vector<std::vector<GameObject*>> m_gameObjects;

	GameObject * m_centeredObject; // Object to be "followed" by the view

	sf::View m_view;
	sf::Vector2f m_viewCenter;
	sf::Vector2f m_viewSize;
	const float m_lerpSpeed = .5f;

	// level
	Map * m_map;

	bool m_gameStarted;

	// DEBUG
	sf::Vector2f VIEW_OFFSET;

	const float VERTICAL_VIEW_OFFSET = 200.f;
public:
	PlayingState();
	~PlayingState();

	// Inherited via GameState
	virtual void update(float _dt) override;
	virtual void draw() override;

	// Inherited via GameState
	virtual GameObject *  instantiateObject(GameObject * _gameObject) override;
	virtual void destroyObject(GameObject * _gameObject) override;

private:
	void startGame();
	void updateView(float _dt);
};

