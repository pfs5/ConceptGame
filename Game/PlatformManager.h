#pragma once
#include "GameObject.h"
#include "Platform.h"

class PlatformManager : public GameObject {

	const std::vector<sf::Vector2f> m_positions{
		sf::Vector2f{ 300, 400 },
		sf::Vector2f{ 700, 500 },
		sf::Vector2f{ 1100, 400 },
		sf::Vector2f{ 700, 300 }
	};

	bool m_initiated = false;
	std::vector<Platform *> m_platforms;

public:
	PlatformManager();
	~PlatformManager();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void init();
};

