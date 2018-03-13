#include "BasicMap.h"
#include "ResourceManager.h"
#include "Display.h"
#include "VectorOperations.h"
#include "Debug.h"

void initSprite(sf::Sprite &_sprite, std::string _name) {
	_sprite.setTexture(*ResourceManager::getInstance().getTexture(_name));

	sf::Vector2f size = VectorOperations::utof(_sprite.getTexture()->getSize());
	_sprite.setOrigin(size / 2.f);

	_sprite.setPosition(VectorOperations::utof(Display::getWindow().getSize()) / 2.f);
}

BasicMap::BasicMap() {
	initSprite(m_spriteBg, "forest_level_bg");
	initSprite(m_spriteFg, "forest_level_fg");
}

void BasicMap::drawBackground() {
	Display::draw(m_spriteBg);
}

void BasicMap::drawForeground() {
	Display::draw(m_spriteFg);
}

