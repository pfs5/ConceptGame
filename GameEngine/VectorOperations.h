#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

/**
	Basic vector (linear algebra) operations required in the engine.
**/
namespace VectorOperations {
	inline sf::Vector2f memberwiseMultiplication(const sf::Vector2f &_v1, const sf::Vector2f &_v2) {
		return sf::Vector2f{ _v1.x * _v2.x, _v1.y * _v2.y };
	}

	inline float dotProduct(const sf::Vector2f &_v1, const sf::Vector2f &_v2) {
		return  _v1.x * _v2.x + _v1.y * _v2.y;
	}

	inline sf::Vector2f utof(const sf::Vector2u &_v) {
		return sf::Vector2f{ static_cast<float>(_v.x), static_cast<float>(_v.y) };
	}

	inline float norm(const sf::Vector2f &_v) {
		return sqrt(powf(_v.x, 2) + powf(_v.y, 2));
	}

	inline float squaredNorm(const sf::Vector2f &_v) {
		return powf(_v.x, 2) + powf(_v.y, 2);
	}
}