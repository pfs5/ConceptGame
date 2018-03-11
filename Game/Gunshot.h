#pragma once

#include "GameObject.h"

#include <SFML/Graphics.hpp>

class Gunshot : public GameObject{
	sf::Vector2f m_start;
	sf::Vector2f m_end;

	sf::Clock m_timer;

	// Visuals
	sf::RectangleShape m_shape;

	// Parameters
	const float m_duration = 2.f;
public:
	Gunshot(const sf::Vector2f & _start = sf::Vector2f{ 0, 0 }, const sf::Vector2f & _end = sf::Vector2f{ 0, 0 });
	~Gunshot();

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void initShape();

#pragma region Getters and setters
public:
	inline void setStart(const sf::Vector2f &_start) { m_start = _start; initShape(); };
	inline void setEnd(const sf::Vector2f &_end) { m_end = _end; initShape(); };
	inline void setPositions(const sf::Vector2f &_start, const sf::Vector2f &_end) {
		m_start = _start;
		m_end = _end;
		initShape();
	};
#pragma endregion

};

