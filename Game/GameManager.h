#pragma once
#include "GameObject.h"
#include "CollectableArrow.h"

class GameManager : public GameObject, CollectableArrowObserver {
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

	// State
	bool m_isInitialized;
	int m_activeCollectableArrows;

	float m_healthPoints;

	// Parameters
	const float MAX_ARROW_OFFSET = 200.f;
	const int MIN_ARROWS_IN_SCENE = 3;
	const int INITIAL_ARROWS_IN_SCENE = 10;
public:
	GameManager();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

	// Game management
	inline float getHealthPoints() const { return m_healthPoints; };
	inline void setHealthPoints(const float &_hp) { m_healthPoints = _hp; };

#pragma region Singleton
public:
	static GameManager * getInstance() {
		static GameManager instance;
		return &instance;
	}
#pragma endregion

private:
	void spawnArrow(sf::Vector2f _pos, CollectableArrow::ARROW_DIRECTION _dir);
	void spawnArrows(int _numberOfArrows);

	// Inherited via CollectableArrowObserver
	virtual void notify() override;
};