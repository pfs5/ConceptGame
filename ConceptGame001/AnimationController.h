#pragma once
#include "Animation.h"

#include <vector>
#include <map>

/**
	Class servers as a container for animations. Handles animation switching.
	Used by a single object that is to be animated.
**/
class AnimationController : public AnimationObserver{
	const std::string RESOURCE_FOLDER = "resources/animation_controllers/";
	const std::string EXTENSION = ".json";

	sf::Vector2f m_position;

	std::vector<Animation*> m_animations;
	int m_currentAnimation;
	int m_nextAnimation;

	std::map<std::string, int> m_animationIndices;

	std::vector<int> m_transitions;
public:
	AnimationController();
	~AnimationController();
	
	void load(std::string _name);

	// Base engine methods
	void update(float _dt);
	void draw();

	// Controller methods
	void playAnimation(std::string _animation, bool _playInstantly = true);

	// Animation observer
	virtual void onAnimationEnd() override;
private:
	bool loadFromFile(std::string _path);
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

#pragma endregion

};