#pragma once
#include "GameObject.h"
#include "BasicEnemy.h"
#include "WalkerEnemy.h"
#include "EnemyObserver.h"
class EnemyManager : public GameObject, EnemyObserver {
	enum MANAGER_STATE {
		SPAWNING,
		WAITING,
		SWITCHING_WAVE
	};

	GameObject * m_player;

	// State
	MANAGER_STATE m_state;
	bool m_started;

	int m_currentWave;
	int m_activeEnemies;

	float m_timer;

	// Debug
	sf::RectangleShape m_spawnPositionVisual;

	// Wave data
	std::vector<int> m_maxEnemies;
	std::vector<float> m_spawnPeriods;

	// Parameters
	const sf::Vector2f m_spawnPosition = sf::Vector2f{ -600.f, 600.f };
	const int MAX_WAVES = 5;
	const float INTER_WAVE_DELAY = 5.f;

public:
	EnemyManager(GameObject * _player);
	~EnemyManager();

	//void spawnBasicEnemy(BasicEnemy::ENEMY_TYPE _type);

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void initWaves();

	void spawnEnemies(float _dt);
	void spawnEnemy();

	// Inherited via EnemyObserver
	virtual void notify() override;
};

