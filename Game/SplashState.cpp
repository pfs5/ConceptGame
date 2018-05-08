#include "SplashState.h"
#include "ResourceManager.h"
#include "Display.h"
#include "Debug.h"
#include "GameStateManager.h"
#include "MenuState.h"

SplashState::SplashState() : 
	m_timer{ 0.f }, 
	m_fadeTimer {0.f},
	m_currentSplash{ 0 },
	m_state {SPLASH_STATE::FADE_IN},
	m_currentAlpha {0.f} {
	
	// Preload game
	m_gameState = new MenuState();

	// Start menu music
	ResourceManager::getInstance().getMusic("forest_background")->play();

	// Load splash screens
	for (int i = 1; i <= SPLASH_SCREENS; ++i) {
		std::string name = SPLASH_SCREEN_PREFIX + std::to_string(i);

		auto tex = ResourceManager::getInstance().getTexture(name);
		tex->setSmooth(true);

		m_splashScreens.push_back(tex);
	}

	m_splashSprite.setOrigin(SPLASH_SIZE / 2.f);
	m_splashSprite.setPosition(Display::getWindow().getSize().x / 2, Display::getWindow().getSize().y / 2);
	m_splashSprite.setScale(sf::Vector2f{ 0.5f, 0.5f });

	m_splashSprite.setColor(sf::Color{ 255, 255, 255, 0 });

	// Init first splash
	m_splashSprite.setTexture(*m_splashScreens[0]);
}

void SplashState::update(float _dt) {
	m_timer += _dt;
	switch (m_state) {
		case SPLASH_STATE::FADE_IN:
			fadeInState(_dt);
			break;
		case SPLASH_STATE::HOLD:
			holdState(_dt);
			break;
		case SPLASH_STATE::FADE_OUT:
			fadeOutState(_dt);
			break;
	}
}

void SplashState::draw() {
	Display::draw(m_splashSprite);
}

GameObject * SplashState::instantiateObject(GameObject * _gameObject) {
	return nullptr;
}

void SplashState::destroyObject(GameObject * _gameObject) {
}

void SplashState::fadeInState(float _dt) {
	m_splashSprite.setColor(sf::Color{ 255, 255, 255, (sf::Uint8) m_currentAlpha });
	m_currentAlpha = (m_timer / FADE_TIME) * 255.f;

	if (m_timer > FADE_TIME) {
		m_timer = 0.f;
		m_state = SPLASH_STATE::HOLD;
	}
}

void SplashState::fadeOutState(float _dt) {
	m_splashSprite.setColor(sf::Color{ 255, 255, 255, (sf::Uint8) m_currentAlpha });
	m_currentAlpha = 255.f - (m_timer / FADE_TIME) * 255.f;

	if (m_timer > FADE_TIME) {
		m_timer = 0.f;
		m_currentAlpha = 0.f;
		
		if (m_currentSplash >= SPLASH_SCREENS) {
			// START GAME
			std::cout << "START GAME" << std::endl;
			GameStateManager::pushGameState(m_gameState);
		}
		else {
			m_splashSprite.setTexture(*m_splashScreens[m_currentSplash]);
			m_state = SPLASH_STATE::FADE_IN;
		}
	}
}

void SplashState::holdState(float _dt) {
	if (m_timer > TIME_PER_SPLASH) {
		m_timer = 0;
		m_currentSplash++;

		// Next splash
		m_currentAlpha = 255.f;
		m_state = SPLASH_STATE::FADE_OUT;
	}
}
