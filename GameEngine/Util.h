#pragma once
#include <ctime>
#include <cstdlib>
#include <iostream>
namespace Util {
	bool isInitialized = false;
	
	inline float randomFloat() {
		if (!isInitialized) {
			srand(time(nullptr));
			isInitialized = true;
		}

		return static_cast<float>(rand()) / RAND_MAX;
	}
	
	inline int randomInt(int _min, int _max) {
		if (!isInitialized) {
			srand(time(nullptr));
			isInitialized = true;
		}

		float num = _min + (_max - _min) * randomFloat();

		return roundf(num);
	}
}