#pragma once
#include "Animation.h"

#include <vector>
#include <map>

/**
	Class servers as a container for animations. Handles animation switching.
	Used by a single object that is to be animated.
**/
class AnimationController : public AnimationObserver {
	const std::string RESOURCE_FOLDER = "../resources/animation_controllers/";
	const std::string EXTENSION = ".json";

	sf::Vector2f m_position;
	float m_rotation;

	std::vector<Animation*> m_animations;
	int m_currentAnimation;
	int m_nextAnimation;

	bool m_isPlaying;

	std::map<std::string, int> m_animationIndices;

	std::vector<int> m_transitions;
	std::vector<std::map<std::string, int>> m_triggerTransitions;
public:
	AnimationController(float _rotation = 0.f);
	~AnimationController();

	void load(std::string _name, bool _play = true);

	// Base engine methods
	void update(float _dt);
	void draw();

	// Controller methods
	void playAnimation(std::string _animation, bool _playInstantly = true);
	void setAnimationTime(float _time, bool _pause = true);
	void setTrigger(std::string _trigger, bool _playInstantly = true);

	// Animation observer
	virtual void onAnimationEnd() override;
private:
	void playAnimation(int _animation, bool _playInstantly = true);
	bool loadFromFile(std::string _name);
	void playNextAnimation();
#pragma region Getters and setters
public:
	inline sf::Vector2f getPosition() { return m_position; };
	inline void setPosition(const sf::Vector2f &_pos) { 
		m_position = _pos; 
		for (Animation *a : m_animations) {
			a->setPosition(_pos);
		}
	};

	inline bool isPlaying() { return m_isPlaying; };
	inline void setColor(sf::Color _color) {
		for (auto &an : m_animations) {
			an->setColor(_color);
		}
	}

#pragma endregion

};