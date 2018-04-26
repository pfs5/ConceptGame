#pragma once
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>

#define PI 3.14159265359f

namespace Util {
	static bool isInitialized = false;
	
	/**
		Random float in [0, 1] range
	**/
	inline float randomFloat() {
		if (!isInitialized) {
			srand(time(nullptr));
			isInitialized = true;
		}

		return static_cast<float>(rand()) / RAND_MAX;
	}
	
	/**
		Random integer in [_min, _max] range
	**/
	inline int randomInt(int _min, int _max) {
		if (!isInitialized) {
			srand(time(nullptr));
			isInitialized = true;
		}

		float num = _min + (_max - _min) * randomFloat();

		return roundf(num);
	}

	inline std::string floatToString(const float &_f, const int &_digits) {
		std::stringstream sstream;
		sstream << std::fixed << std::setprecision(_digits) << _f;
		return sstream.str();
	}

	inline float radianToDegree(const float &_radians) {
		return _radians * 180.f / PI;
	}
}