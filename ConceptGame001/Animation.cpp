#include "Animation.h"
#include "ResourceManager.h"
#include "Display.h"
#include "VectorOperations.h"
#include "Debug.h"

#include <algorithm>

Animation::Animation(std::string _name, int _numberOfFrames, const std::vector<int> &_frameLengths, int _scale, bool _isLooping) :
	m_name (_name) , m_isPlaying(true), m_currentFrame(0), m_numberOfFrames(_numberOfFrames), m_frameLengths(_frameLengths), m_scale(_scale),
	m_isLooping(_isLooping) {

	m_frameTime = m_frameLengths[m_currentFrame] * m_scale;

	// Load texture
	m_texture = ResourceManager::getInstance().getTexture(_name);
	m_sprite.setTexture(*m_texture);
	
	m_frameSize = m_texture->getSize();
	m_frameSize.x /= m_numberOfFrames;
	
	m_sprite.setOrigin(VectorOperations::utof(m_frameSize) / 2.f);

	setSpriteRect();
}

Animation::~Animation() {
}

void Animation::play() {
	m_isPlaying = true;
}

void Animation::pause() {
	m_isPlaying = false;
}

void Animation::reset() {
	m_currentFrame = 0;
	m_frameTime = m_frameLengths[m_currentFrame] * m_scale;

	setSpriteRect();
}

void Animation::update(float _dt) {
	if (!m_isPlaying) {
		return;
	}

	m_frameTime--;

	if (m_frameTime == 0) {
		// check if last frame
		if (m_currentFrame == m_numberOfFrames - 1 && !m_isLooping) {
			m_isPlaying = false;
			notifyOnAnimationEnd();
		} else {
			// next frame
			m_currentFrame = (m_currentFrame + 1) % m_numberOfFrames;
			m_frameTime = m_frameLengths[m_currentFrame] * m_scale;

			setSpriteRect();
		}
	}
}

void Animation::draw() {
	Display::draw(m_sprite);
}

void Animation::attachObserver(AnimationObserver * _o) {
	m_observers.push_back(_o);
}

void Animation::dettachObserver(AnimationObserver * _o) {
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), _o), m_observers.end());
}

void Animation::setSpriteRect() {
	m_sprite.setTextureRect(sf::IntRect(m_frameSize.x * m_currentFrame, 0, m_frameSize.x, m_frameSize.y));
}

void Animation::notifyOnAnimationEnd() {
	for (auto &o : m_observers) {
		o->onAnimationEnd();
	}
}