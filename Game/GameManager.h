#pragma once
#include "GameObject.h"
#include "CollectableArrow.h"

class GameManager : public GameObject {
	const std::vector <sf::Vector2f> SPAWN_POSITIONS_LEFT = {
		sf::Vector2f{ 900.f, -500.f },
		sf::Vector2f{ 700.f, -500.f },
		sf::Vector2f{ 475.f, -500.f },
		sf::Vector2f{ 150.f, -500.f }
	};

	const std::vector <sf::Vector2f> SPAWN_POSITIONS_RIGHT = {
		sf::Vector2f{ 100.f, -500.f },
		sf::Vector2f{ 200.f, -500.f },
		sf::Vector2f{ 550.f, -500.f },
		sf::Vector2f{ 850.f, -500.f },
		sf::Vector2f{ 1000.f, -500.f }
	};

	const float MAX_ARROW_OFFSET = 200.f;

public:
	GameManager();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void spawnArrow(sf::Vector2f _pos, CollectableArrow::ARROW_DIRECTION _dir);
};