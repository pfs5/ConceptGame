#include "AnimationController.h"
#include "Debug.h"
#include "json.h"
#include <fstream>
#include <sstream>

AnimationController::AnimationController(float _rotation) : 
	m_rotation(_rotation), m_currentAnimation (0), m_nextAnimation(0), m_isPlaying(false) {
}

AnimationController::~AnimationController() {
}

void AnimationController::load(std::string _name, bool _play) {
	if (!loadFromFile(_name)) {
		Debug::logError("[AnimationController] Error loading " + _name);
	}

	m_isPlaying = _play;

	if (_play) {
		m_animations[m_currentAnimation]->play();
	}
	else {
		m_animations[m_currentAnimation]->stop();
	}
}

void AnimationController::update(float _dt) {
	if (m_animations.size() == 2) {
		std::cout << m_currentAnimation << std::endl;
	}

	if (m_isPlaying) {
		m_animations[m_currentAnimation]->update(_dt);
	}
}

void AnimationController::draw() {
	m_animations[m_currentAnimation]->draw();
}

void AnimationController::playAnimation(std::string _animation, bool _playInstantly) {
	int animationIndex = m_animationIndices.at(_animation);
	playAnimation(animationIndex, _playInstantly);
}

void AnimationController::setAnimationTime(float _time, bool _pause) {
	m_animations[m_currentAnimation]->setTime(_time, _pause);
}

void AnimationController::setTrigger(std::string _trigger, bool _playInstantly) {
	try {
		int nextAnimation = m_triggerTransitions[m_currentAnimation].at(_trigger);
		playAnimation(nextAnimation, _playInstantly);

		m_isPlaying = true;
	} catch (std::out_of_range) {
		return;
	}
}

void AnimationController::stop() {
	pause();
	reset();
}

void AnimationController::pause() {
	m_isPlaying = false;
}

void AnimationController::reset() {
	// TODO
}

void AnimationController::playAnimation(int _animation, bool _playInstantly) {
	try {
		m_nextAnimation = _animation;
		if (_playInstantly) {
			playNextAnimation();
		}
		m_isPlaying = true;
	} catch (std::out_of_range e) {
		return;
	}
}

bool AnimationController::loadFromFile(std::string _name) {
	std::string path = RESOURCE_FOLDER + _name + EXTENSION;
	std::ifstream file{ path };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;

		// Animations
		for (auto &a : data["animations"]) {
			std::string name = a["name"];
			std::vector<int> frames = a["frames"];
			int scale = a["scale"];
			bool isLooping = a["looping"];

			Animation *a = new Animation(_name + "_" + name, frames.size(), frames, scale, isLooping);
			a->setRotation(m_rotation);
			m_animations.push_back(a);
			m_transitions.push_back(-1);
			m_triggerTransitions.push_back(std::map<std::string, int>());

			a->attachObserver(this);

			m_animationIndices.emplace(name, m_animations.size() - 1);
		}

		// Transitions
		for (auto &t : data["transitions"]) {
			std::string trigger = t["trigger"];
			std::string from = t["from"];
			std::string to = t["to"];

			int fromIndex = m_animationIndices[from];
			int toIndex = m_animationIndices[to];

			if (trigger == "default") {
				m_transitions[fromIndex] = toIndex;
			} else {
				m_triggerTransitions[fromIndex].emplace(trigger, toIndex);
			}
		}

		file.close();
	} else {
		return false;
	}
}

void AnimationController::playNextAnimation() {
	m_animations[m_currentAnimation]->reset();
	m_currentAnimation = m_nextAnimation;
	m_animations[m_currentAnimation]->play();

	if (m_transitions[m_currentAnimation] != -1) {
		m_nextAnimation = m_transitions[m_currentAnimation];
	}
}

void AnimationController::onAnimationEnd() {
	// Switch to next animation
	if (m_nextAnimation != m_currentAnimation || m_animations[m_currentAnimation]->isLooping()) {
		playNextAnimation();
	}
	else {
		m_isPlaying = false;
	}
}
