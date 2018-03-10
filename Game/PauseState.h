#pragma once
#include "GameState.h"

#include <SFML/Graphics.hpp>
#include <string>

class PauseState : public GameState{
	const std::string m_pauseText = "Paused";
	sf::Text m_textObject;

	sf::View m_view;
public:
	PauseState();
	~PauseState();

	// Inherited via GameState
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual GameObject * instantiateObject(GameObject * _gameObject) override;
	virtual void destroyObject(GameObject * _gameObject) override;
};

