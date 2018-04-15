#pragma once
#include <GameObject.h>
class Particles : public GameObject{
	sf::Sprite m_sprite;

	std::vector<sf::Vector2f> m_particles;
	int m_currentParticle;

	bool m_initialized;
	float m_counter;
public:
	Particles();
	~Particles();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _this, Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;
};

