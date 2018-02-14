#include "PauseState.h"
#include "Display.h"
#include "ResourceManager.h"
#include "Input.h"
#include "GameStateManager.h"

PauseState::PauseState() {
	m_textObject.setString(m_pauseText);
	m_textObject.setFillColor(sf::Color::White);
	m_textObject.setFont(*ResourceManager::getInstance().getFont("atwriter"));

	m_textObject.setOrigin(m_textObject.getGlobalBounds().width / 2.f, m_textObject.getGlobalBounds().height / 2.f);
	m_textObject.setPosition(Display::getWindow().getSize().x / 2.f, Display::getWindow().getSize().y / 2.f);
}


PauseState::~PauseState() {
}

void PauseState::update(float _dt) {
	if (Input::getKeyDown(Input::P)) {
		// Resume game (exit pause state)
		GameStateManager::popGameState();
	}
}

void PauseState::draw() {
	Display::draw(m_textObject);
}

GameObject * PauseState::instantiateObject(GameObject * _gameObject) {
	return nullptr;
}
