#pragma once
#include "GameObject.h"
#include "BasicEnemy.h"
class EnemyManager : public GameObject {
	GameObject * m_player;

	// Debug
	sf::RectangleShape m_spawnPositionVisual;

	// Parameters
	const std::vector<sf::Vector2f> m_spawnPositions = { 
		sf::Vector2f{ 100, 100 },
		sf::Vector2f{ 150, 100 },
		sf::Vector2f{ 200, 100 },

		sf::Vector2f{ 1200, 100 },
		sf::Vector2f{ 1250, 100 },
		sf::Vector2f{ 1300, 100 }
	};

	const std::vector<float> m_basicEnemySpeeds = {
		100.f,
		200.f,
		250.f,
		300.f
	};

public:
	EnemyManager(GameObject * _player);
	~EnemyManager();

	void spawnBasicEnemy(BasicEnemy::ENEMY_TYPE _type);

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

