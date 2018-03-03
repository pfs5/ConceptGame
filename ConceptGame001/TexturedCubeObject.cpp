#include "TexturedCubeObject.h"
#include "ResourceManager.h"

TexturedCubeObject::TexturedCubeObject(sf::Vector2f _size, sf::Vector2f _position, bool _static, bool _gravity, sf::Color _color) :
	CubeObject{_size, _position, _static, _gravity, _color} {
	// Init sprite
	sf::Texture * tex = ResourceManager::getInstance().getTexture("debug_texture");
	tex->setRepeated(true);
	m_sprite.setTexture(*tex);

	m_sprite.setOrigin(_size / 2.f);
	m_sprite.setPosition(_position);
	
	m_sprite.setTextureRect(sf::IntRect{0, 0, static_cast<int>(_size.x), static_cast<int>(_size.y)});
}

TexturedCubeObject::~TexturedCubeObject() {
}

void TexturedCubeObject::draw() {
	Display::draw(m_sprite);
}
