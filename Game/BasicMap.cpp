#include "BasicMap.h"
#include "ResourceManager.h"
#include "Display.h"
#include "VectorOperations.h"
#include "Debug.h"

void initSprite(sf::Sprite &_sprite, std::string _name) {
	auto tex = ResourceManager::getInstance().getTexture(_name);
	tex->setSmooth(true);
	_sprite.setTexture(*tex);

	sf::Vector2f size = VectorOperations::utof(_sprite.getTexture()->getSize());
	_sprite.setOrigin(size.x / 2, size.y);

	_sprite.setPosition((float)Display::getWindow().getSize().x / 2, (float)Display::getWindow().getSize().y);
}

BasicMap::BasicMap() {
	initSprite(m_spriteBg, "flat_level_bg");
	initSprite(m_spriteFg, "flat_level_fg");
}

void BasicMap::drawBackground() {
	Display::draw(m_spriteBg);
}

void BasicMap::drawForeground() {
	Display::draw(m_spriteFg);
}

