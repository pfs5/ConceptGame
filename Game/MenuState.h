#pragma once
#include "GameState.h"
#include "PlayingState.h"

#include <SFML/Graphics.hpp>
class MenuState : public GameState {
	sf::Sprite m_sprite;
	sf::Sprite m_selectorSprite;

	PlayingState * m_playscene;

	int m_currentSelection;

	// Parameters
	const sf::Uint8 SELECTOR_OPACITY = 50;
	const float SELECTOR_HEIGHT = 155.f;
	const float SELECTOR_DELTA = 74.f;

	const int MENU_ITEMS = 3;
public:
	MenuState();
	~MenuState();

	// Inherited via GameState
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual GameObject * instantiateObject(GameObject * _gameObject) override;
	virtual void destroyObject(GameObject * _gameObject) override;

private:
	void selectMenuItem();
	void exitGame();
};

