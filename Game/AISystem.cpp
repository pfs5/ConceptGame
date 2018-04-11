#include "AISystem.h"
#include "GameStateManager.h"

void AISystem::init(GameObject * _playerReference) {
	m_playerRef = _playerReference;

	// Init grid visual
	m_gridRect.setFillColor(sf::Color{0, 0, 0, 0});
	m_gridRect.setOutlineColor(sf::Color{0, 0, 0, 100});
	m_gridRect.setOutlineThickness(0.5f);

	m_gridRect.setSize(sf::Vector2f{GRID_WIDTH, GRID_HEIGHT});
}

void AISystem::update(float _dt) {
}

void AISystem::draw() {
	//// Draw grid
	//auto winSize = Display::getWindow().getSize();
	//for (int x = 0; x < winSize.x; x += GRID_WIDTH) {
	//	for (int y = 0; y < winSize.y; y += GRID_HEIGHT) {
	//		m_gridRect.setPosition(x, y);
	//		Display::draw(m_gridRect);
	//	}
	//}
}
