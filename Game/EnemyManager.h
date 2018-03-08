#pragma once
#include "GameObject.h"
class EnemyManager : public GameObject {
	GameObject * m_enemy;
	GameObject * m_player;

	// Parameters
	const std::vector<sf::Vector2f> m_spawnPositions = { sf::Vector2f{ -450, -50 }, sf::Vector2f{ 1000, 400 } };
public:
	EnemyManager(GameObject * _enemy, GameObject * _player);
	~EnemyManager();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

