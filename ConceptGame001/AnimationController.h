#pragma once
#include "Animation.h"

#include <vector>

class AnimationController {
	const std::string RESOURCE_FOLDER = "resources/animation_controllers/";
	const std::string EXTENSION = ".json";

	sf::Vector2f m_position;

	std::vector<Animation*> m_animations;
	int m_currentAnimation;
	int m_nextAnimation;
public:
	AnimationController();
	~AnimationController();
	
	void load(std::string _name);

	// Base methods
	void update(float _dt);
	void draw();

	// Controller methods
	void playAnimation(std::string _animation, bool _playInstantly = true);

#pragma region Getters and setters
	inline sf::Vector2f getPosition() { return m_position; };
	inline void setPosition(const sf::Vector2f &_pos) { 
		m_position = _pos; 
		for (Animation *a : m_animations) {
			a->setPosition(_pos);
		}
	};

#pragma endregion
private:
	bool loadFromFile(std::string _path);
};