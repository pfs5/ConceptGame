#include "PhysicsLayers.h"

int PhysicsLayers::layerNumber(std::string _name) {
	for (int i = 0; i < layers.size(); ++i) {
		if (_name == layers[i]) {
			return i;
		}
	}

	return -1;
}

std::string PhysicsLayers::layerName(int _number) {
	return layers[_number];
}
