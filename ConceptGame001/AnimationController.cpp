#include "AnimationController.h"
#include "Debug.h"
#include "json.h"
#include <fstream>
#include <sstream>

AnimationController::AnimationController() : m_currentAnimation (0), m_nextAnimation(0){
}

AnimationController::~AnimationController() {
}

void AnimationController::load(std::string _name) {
	if (!loadFromFile(RESOURCE_FOLDER + _name + EXTENSION)) {
		Debug::logError("[AnimationController] Error loading " + _name);
	}
}

void AnimationController::update(float _dt) {
	m_animations[m_currentAnimation]->update(_dt);
}

void AnimationController::draw() {
	m_animations[m_currentAnimation]->draw();
}

void AnimationController::playAnimation(std::string _animation, bool _playInstantly) {
	int animationIndex = m_animationIndices.at(_animation);
	playAnimation(animationIndex, _playInstantly);
}

void AnimationController::setTrigger(std::string _trigger, bool _playInstantly) {
	try {
		int nextAnimation = m_triggerTransitions[m_currentAnimation].at(_trigger);
		playAnimation(nextAnimation, _playInstantly);
	} catch (std::out_of_range) {
		return;
	}
}

void AnimationController::playAnimation(int _animation, bool _playInstantly) {
	try {
		m_nextAnimation = _animation;
		if (_playInstantly) {
			playNextAnimation();
		}
	} catch (std::out_of_range e) {
		return;
	}
}

bool AnimationController::loadFromFile(std::string _path) {
	std::ifstream file{ _path };
	if (file.is_open()) {
		nlohmann::json data;
		file >> data;

		// Animations
		for (auto &a : data["animations"]) {
			std::string name = a["name"];
			std::vector<int> frames = a["frames"];
			int scale = a["scale"];
			bool isLooping = a["looping"];

			Animation *a = new Animation(name, frames.size(), frames, scale, isLooping);
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
}
