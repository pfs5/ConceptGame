#include "PhysicsLayers.h"

#include <iostream>

const std::vector<std::vector<bool>> PhysicsLayers::fillIgnoreMatrix() {
	std::vector<std::vector<bool>> matrix;
	
	// Init matrix
	for (int i = 0; i < NUMBER_OF_LAYERS; ++i) {
		std::vector<bool> row(NUMBER_OF_LAYERS, false);
		matrix.push_back(row);
	}

	// Add ignores
	matrix[2][5] = true;	// walker enemy - platform
	matrix[5][2] = true;	// walker enemy - platform

	matrix[5][5] = true;	// walker enemy with itself

	for (int i = 0; i < NUMBER_OF_LAYERS; ++i) { matrix[i][3] = true; matrix[3][i] = true; }	// everything with arrows
	
	return matrix;
}

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
