#pragma once
#include <iostream>
#include <string>

namespace Debug {
	inline void log(std::string _s) {
		std::cout << _s << std::endl;
	}

	inline void log(bool _b) {
		log(std::to_string(_b));
	}
};