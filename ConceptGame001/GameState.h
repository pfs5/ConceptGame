#pragma once
class GameObject;

class GameState {
public:
	virtual ~GameState() {};

	virtual void update(float _dt) = 0;
	virtual void draw() = 0;

	virtual GameObject * instantiateObject(GameObject  * _gameObject) = 0;
};
