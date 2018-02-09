#include "Application.h"
#include "Debug.h"
#include "Display.h"
#include "GameSettings.h"
#include "Input.h"

#include <SFML/System/Clock.hpp>

void calculateFPS(bool _print_fps) {
	static sf::Clock timer;
	static sf::Clock printTimer;
	static auto numFrames = 0;

	numFrames++;

	if (printTimer.getElapsedTime().asSeconds() >= 1.0f) {
		auto fps = (float)numFrames / timer.getElapsedTime().asSeconds();
		printTimer.restart();
		if (_print_fps) {
			Display::getWindow().setTitle(std::to_string(fps));
		}

		numFrames = 0;
		timer.restart();
	}
}

Application::Application() {
	Display::init();
}


Application::~Application() {
	// Clear game states
	while (!m_gameStates.empty()) {
		delete m_gameStates.top();
		m_gameStates.pop();
	}
}

void Application::runMainLoop() {
	sf::Clock clock;
	sf::Time accumulator;
	sf::Time dt = sf::seconds(1.f / Display::UPS);
	sf::Time max_acc = sf::seconds(0.2f);

	while (Display::isOpen()) {
		Display::checkWindowEvents();
		Display::clear();

		// Exit if stack empty
		if (m_gameStates.empty()) {
			return;
		}

		Input::update();

		// Physics
		accumulator += clock.restart();

		while (accumulator > dt) {
			bool collision = false;
			m_gameStates.top()->update(dt.asSeconds());

			accumulator -= dt;
		}

		// Rendering
		m_gameStates.top()->draw();	

		calculateFPS(GameSettings::PRINT_FPS);
		Display::display();
	}
}

void Application::addGameState(GameState * _gameState) {
	m_gameStates.push(_gameState);
}
