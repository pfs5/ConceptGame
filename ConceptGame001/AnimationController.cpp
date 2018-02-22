#include "AnimationController.h"
#include "Debug.h"
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
	for (int i = 0; i < m_animations.size(); ++i) {
		if (_animation == m_animations[i]->getName()) {
			// TODO non instant switching
			m_nextAnimation = i;
			break;
		}
	}
}

std::vector<std::string> splitString(std::string _string, char _delimiter) {
	std::vector<std::string> tokens;
	
	std::stringstream ss(_string);
	std::string token;
	
	while (std::getline(ss, token, _delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

void loadAnimation(std::vector<std::string> _data, std::vector<Animation *> &_container) {
	std::string name = _data[0];
	int frames = stoi(_data[1]);

	std::vector<int> frameLengths;
	for (int i = 2; i < 2 + frames; ++i) {
		frameLengths.push_back(stoi(_data[i]));
	}

	_container.push_back(new Animation(name, frames, frameLengths));
}

bool AnimationController::loadFromFile(std::string _path) {
	std::ifstream file{ _path };
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			// Parse
			char type = line[0];

			switch (type) {
				// animation
				case 'a':
					std::vector<std::string> data = splitString(line.substr(2), ',');
					loadAnimation(data, m_animations);
					break;
			}
		}
	} else {
		return false;
	}
}
