#pragma once

#include "GameObject.h"
#include "AnimationController.h"

#include <SFML/Graphics.hpp>

class Trail : public GameObject{
	std::string m_name;

	sf::Vector2f m_start;
	sf::Vector2f m_end;

	sf::Vector2f m_startOffset;
	sf::Vector2f m_endOffset;

	sf::Clock m_timer;

	// Visuals
	sf::Sprite m_spriteIdle;
	sf::Sprite m_spriteHit;
	sf::Sprite * m_currentSprite;

	// Parameters
	const float m_duration = 2.f;
public:
	Trail(std::string _name, const sf::Vector2f & _start = sf::Vector2f{ 0, 0 }, const sf::Vector2f & _end = sf::Vector2f{ 0, 0 });
	~Trail();

	void setHit(bool _hit);

	// Inherited via GameObject
	virtual void update(float _dt) override;
	virtual void draw() override;
	virtual void onCollision(Collider * _other) override;
	virtual GameObject * clone() override;
	virtual void setPosition(sf::Vector2f _pos) override;

private:
	void updateVisual();

#pragma region Getters and setters
public:
	inline void setStart(const sf::Vector2f &_start) { m_start = _start; updateVisual(); };
	inline void setEnd(const sf::Vector2f &_end) { m_end = _end; updateVisual(); };
	
	void setPositions(const sf::Vector2f &_start, const sf::Vector2f &_end);

	inline void setOffsets(const sf::Vector2f &_startOffset, const sf::Vector2f &_endOffset) {
		m_startOffset = _startOffset;
		m_endOffset = _endOffset;
	}
#pragma endregion

};

