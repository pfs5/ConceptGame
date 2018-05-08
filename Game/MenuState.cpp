#include "MenuState.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "ResourceManager.h"
#include "Display.h"
#include "Input.h"

MenuState::MenuState() : m_currentSelection{ 0 } {
	m_sprite.setTexture(*ResourceManager::getInstance().getTexture("menu"));
	m_selectorSprite.setTexture(*ResourceManager::getInstance().getTexture("menu_selector"));

	m_selectorSprite.setColor(sf::Color{ 255, 255, 255, SELECTOR_OPACITY });

	m_playscene = new PlayingState;
}


MenuState::~MenuState() {
}

void MenuState::update(float _dt) {
	m_selectorSprite.setPosition(sf::Vector2f{0.f, SELECTOR_HEIGHT + SELECTOR_DELTA * m_currentSelection});

	// Inputs
	if (Input::getKeyDown(Input::UARROW)) {
		m_currentSelection = (m_currentSelection - 1 + MENU_ITEMS) % MENU_ITEMS;
	}

	if (Input::getKeyDown(Input::DARROW)) {
		m_currentSelection = (m_currentSelection + 1) % MENU_ITEMS;
	}

	if (Input::getKeyDown(Input::ENTER)) {
		selectMenuItem();
	}
}

void MenuState::draw() {
	Display::draw(m_sprite);
	Display::draw(m_selectorSprite);
}

GameObject * MenuState::instantiateObject(GameObject * _gameObject) {
	return nullptr;
}

void MenuState::destroyObject(GameObject * _gameObject) {
}

void MenuState::selectMenuItem() {
	switch (m_currentSelection) {
	case 0:
		// Start game
		GameStateManager::pushGameState(m_playscene);
		break;

	case 1:
		// Do nothing :D
		break;

	case 2:
		// Exit game
		exitGame();
		break;
	}
}

void MenuState::exitGame() {
	exit(0);
}
