#pragma once
#include "Map.h"

#include <SFML/Graphics.hpp>
class BasicMap : public Map {
	sf::Sprite m_spriteBg;
	sf::Sprite m_spriteFg;
public:
	BasicMap();

	// Inherited via Map
	virtual void drawBackground() override;
	virtual void drawForeground() override;
};