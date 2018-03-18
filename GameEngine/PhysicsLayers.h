#pragma once
#include <vector>
#include <string>

/**
	Enables the engine to ignore collisions between certain objects in the game.
**/
namespace PhysicsLayers {
	const std::vector<std::string> layers = {"Default", "Arrow", "Enemy",  "Player", "DestroyedArrow"};
	const std::vector<std::vector<bool>> layerIgnoreMatrix{ 
		{	false,	false,	false,	false,	true	},
		{	false,	true,	false,	true,	true	},
		{	false,	false,	true,	false,	true	},
		{	false,	true,	false,	true,	true	},
		{	true,	true,	true,	true,	true	}
	};
	
	int layerNumber(std::string _name);

	std::string layerName(int _number);
}