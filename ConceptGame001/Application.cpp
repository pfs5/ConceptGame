#include "Application.h"
#include "Debug.h"
#include "Display.h"
#include "GameSettings.h"
#include "Input.h"
#include "GameStateManager.h"

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
		if (!GameStateManager::activeGameState()) {
			return;
		}

		Input::update();

		// Physics
		accumulator += clock.restart();

		while (accumulator > dt) {
			GameStateManager::activeGameState()->update(dt.asSeconds());

			accumulator -= dt;
		}

		// Rendering
		GameStateManager::activeGameState()->draw();

		calculateFPS(GameSettings::PRINT_FPS);
		Display::display();
	}
}

void Application::addGameState(GameState * _gameState) {
	GameStateManager::pushGameState(_gameState);
}
