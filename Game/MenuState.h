#pragma once
#include "GameState.h"

#include <SFML/Graphics.hpp>
class MenuState : public GameState {

	sf::Sprite m_sprite;

public:
	MenuState();
	~MenuState();

	// Inherited via GameState
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual GameObject * instantiateObject(GameObject * _gameObject) override;
	virtual void destroyObject(GameObject * _gameObject) override;
};

