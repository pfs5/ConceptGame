#pragma once
#include "GameObject.h"
class EnemyManager : public GameObject {
	GameObject * m_player;

	// Debug
	const bool m_showSpawnPositions = true;
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
public:
	EnemyManager(GameObject * _player);
	~EnemyManager();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

