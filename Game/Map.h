#pragma once
class Map {
public:
	virtual ~Map() {};
	virtual void drawBackground() = 0;
	virtual void drawForeground() = 0;
};