#pragma once
#include "GameObject.h"
#include "Platform.h"

class PlatformManager : public GameObject {

	const std::vector<sf::Vector2f> m_positions {
		sf::Vector2f{ 300, 80 },
		sf::Vector2f{ 300, 400 },

		sf::Vector2f{ 700, -100 },
		sf::Vector2f{ 700, 250 },
		sf::Vector2f{ 700, 600 },
		
		sf::Vector2f{ 1100, 80 },
		sf::Vector2f{ 1100, 400 }
	};

	bool m_initiated = false;
	std::vector<Platform *> m_platforms;

public:
	PlatformManager();
	~PlatformManager();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void init();
	void togglePlatform(int _index);
};

