#pragma once
#include "Display.h"
#include "GameObject.h"

#include <SFML/Graphics.hpp>

class AISystem {
#pragma region Singleton
public:
	static AISystem &getInstance() {
		static AISystem instance;
		return instance;
	}
#pragma endregion

private:
	// Player reference
	GameObject * m_playerRef;

	// Grid
	sf::RectangleShape m_gridRect;

	const float GRID_WIDTH = 50.f;
	const float GRID_HEIGHT = 50.f;

public:
	void init(GameObject * _playerReference);

	void update(float _dt);
	void draw();

private:
	// Navigation

#pragma region Getters and setters
public:
	inline sf::Vector2f getPlayerPosition() const { return m_playerRef->getPosition(); };
#pragma endregion
};