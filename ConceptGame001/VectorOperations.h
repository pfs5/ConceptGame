#pragma once
#include <SFML/Graphics.hpp>
namespace VectorOperations {
	sf::Vector2f memberwiseMultiplication(const sf::Vector2f &_v1, const sf::Vector2f &_v2) {
		return sf::Vector2f{ _v1.x * _v2.x, _v1.y * _v2.y };
	}
}