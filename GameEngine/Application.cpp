#include "Application.h"
#include "Debug.h"
#include "Display.h"
#include "GameSettings.h"
#include "Input.h"
#include "GameStateManager.h"
#include "ResourceManager.h"
#include "Util.h"

#include <SFML/System/Clock.hpp>

Application::Application() :
	m_fpsText{"fps: ", *ResourceManager::getInstance().getFont("couriernew1"), 15} {
	Display::init();

	// Debug text init
	m_fpsText.setFillColor(sf::Color::Black);
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
		Display::clear(sf::Color{200, 200, 200});

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

		// Debug text 
		sf::Vector2f viewCenter = Display::getWindow().getView().getCenter();
		sf::Vector2u windowSize = Display::getWindow().getSize();
		sf::Vector2f debugTextPos{viewCenter.x - windowSize.x / 2.f + 10.f, viewCenter.y - windowSize.y / 2.f};
		m_fpsText.setPosition(debugTextPos);

		Display::draw(m_fpsText);

		calculateFPS(GameSettings::PRINT_FPS);
		Display::display();
	}
}

void Application::addGameState(GameState * _gameState) {
	GameStateManager::pushGameState(_gameState);
}

void Application::popGameState() {
	GameStateManager::popGameState();
}

void Application::calculateFPS(bool _printFPS) {
	static sf::Clock timer;
	static sf::Clock printTimer;
	static auto numFrames = 0;

	numFrames++;

	if (printTimer.getElapsedTime().asSeconds() >= 1.0f) {
		auto fps = (float)numFrames / timer.getElapsedTime().asSeconds();
		printTimer.restart();
		if (_printFPS) {
			m_fpsText.setString("fps: " + Util::floatToString(fps, 2));
		}

		numFrames = 0;
		timer.restart();
	}
}
