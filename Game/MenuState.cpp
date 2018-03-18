#include "MenuState.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "ResourceManager.h"
#include "Display.h"
#include "Input.h"
#include "PlayingState.h"

MenuState::MenuState() {
	m_sprite.setTexture(*ResourceManager::getInstance().getTexture("title"));
}


MenuState::~MenuState() {
}

void MenuState::update(float _dt) {
	if (Input::getKeyDown(Input::ENTER)) {
		GameStateManager::pushGameState(new PlayingState());
	}
}

void MenuState::draw() {
	Display::draw(m_sprite);
}

GameObject * MenuState::instantiateObject(GameObject * _gameObject) {
	return nullptr;
}

void MenuState::destroyObject(GameObject * _gameObject) {
}
