#pragma once
#include <SFML/Graphics.hpp>
class Animation {
	std::string m_name;

	bool m_isPlaying;
	int m_currentFrame;
	int m_numberOfFrames;

	// Frames
	sf::Vector2u m_frameSize;
	std::vector<int> m_frameLengths;
	int m_frameTime;

	int m_scale = 10;

	// Visuals
	sf::Sprite m_sprite;
	sf::Texture *m_texture;
public:
	Animation(std::string _name, int _numberOfFrames, const std::vector<int> &_frameLengths);
	~Animation();

	void play();
	void stop();
	void reset();

	// Base methods
	void update(float _dt);
	void draw();

#pragma region Getters and setters
	inline std::string getName() { return m_name; };
	inline void setName(std::string _name) { m_name = _name; };

	inline sf::Vector2f getPosition() { return m_sprite.getPosition(); };
	inline void setPosition(const sf::Vector2f &_pos) { m_sprite.setPosition(_pos); };
#pragma endregion
};