#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

namespace Debug {
	inline void log(std::string _s) {
		std::cout << _s << std::endl;
	}

	inline void log(sf::Vector2f _v) {
		std::string s = "V2f: " + std::to_string(_v.x) + " " + std::to_string(_v.y);
		log(s);
	}
};