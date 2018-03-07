#pragma once
#include "CubeObject.h"
class TexturedCubeObject : public CubeObject {
	sf::Sprite m_sprite;
public:
	TexturedCubeObject(sf::Vector2f _size, sf::Vector2f _position, bool _static = false, bool _gravity = false, sf::Color _color = sf::Color::Red);
	~TexturedCubeObject();

	virtual void draw() override;
};