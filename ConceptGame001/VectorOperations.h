#pragma once
#include <SFML/Graphics.hpp>
namespace VectorOperations {
	inline sf::Vector2f memberwiseMultiplication(const sf::Vector2f &_v1, const sf::Vector2f &_v2) {
		return sf::Vector2f{ _v1.x * _v2.x, _v1.y * _v2.y };
	}

	inline sf::Vector2f utof(sf::Vector2u _v) {
		return sf::Vector2f{ static_cast<float>(_v.x), static_cast<float>(_v.y) };
	}
}