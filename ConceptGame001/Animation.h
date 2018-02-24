#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationObserver.h"
/**
	Class represents one animation. Played from a single sprite sheet.
**/
class Animation {
	std::string m_name;

	// Frame parameters
	sf::Vector2u m_frameSize;			// size of a single frame
	std::vector<int> m_frameLengths;	// number of updates for each frame
	int m_numberOfFrames;				// total number of frames
	int m_scale;						// multiplier for frameLengths

	// Current state
	int m_frameTime;		// updates left for current frame
	bool m_isPlaying;
	int m_currentFrame;		// current frame index
	bool m_isLooping;

	// Visuals
	sf::Sprite m_sprite;	
	sf::Texture *m_texture;	// texture pointer. texture resources are handled by the resource manager\

	// Animation observers
	std::vector<AnimationObserver*> m_observers;
public:
	Animation(std::string _name, int _numberOfFrames, const std::vector<int> &_frameLengths, int _scale, bool _isLooping = true);
	~Animation();

	// Animation controll
	void play();
	void pause();
	void reset();

	// Base engine methods
	void update(float _dt);
	void draw();

	// Observers
	void attachObserver(AnimationObserver *_o);
	void dettachObserver(AnimationObserver *_o);
private:
	void setSpriteRect();
	void notifyOnAnimationEnd();
#pragma region Getters and setters
public:
	inline std::string getName() { return m_name; };
	inline void setName(std::string _name) { m_name = _name; };

	inline sf::Vector2f getPosition() { return m_sprite.getPosition(); };
	inline void setPosition(const sf::Vector2f &_pos) { m_sprite.setPosition(_pos); };
#pragma endregion
};