#include "MenuState.h"
#include "GameStateManager.h"
#include "Debug.h"
#include "ResourceManager.h"
#include "Display.h"
#include "Input.h"

MenuState::MenuState() : m_alpha{ 2 }, m_fadeSpeed{ 100 }, m_isFading { true } {
	m_sprite.setTexture(*ResourceManager::getInstance().getTexture("title2"));
	m_sprite.setColor(sf::Color{ 255, 255, 255, uint8_t(m_alpha) });

	m_playscene = new PlayingState;
}


MenuState::~MenuState() {
}

void MenuState::update(float _dt) {
	if (m_isFading) {
		if (m_alpha < 255) {
			if (m_alpha < 1) {
				GameStateManager::pushGameState(m_playscene);
				return;
			}
			
			m_alpha = fmaxf(m_alpha + _dt * m_fadeSpeed, 0);
			m_sprite.setColor(sf::Color{ 255, 255, 255, uint8_t(m_alpha) });
		} else {
			m_isFading = false;
		}
	}
	
	if (Input::getKeyDown(Input::ENTER)) {
		m_fadeSpeed *= -2;
		m_alpha = fminf(m_alpha, 254);
		m_isFading = true;
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
