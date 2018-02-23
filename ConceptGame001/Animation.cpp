#include "Animation.h"
#include "ResourceManager.h"
#include "Display.h"
#include "VectorOperations.h"
#include "Debug.h"

Animation::Animation(std::string _name, int _numberOfFrames, const std::vector<int> &_frameLengths, int _scale) :
	m_name (_name) , m_isPlaying(false), m_currentFrame(0), m_numberOfFrames(_numberOfFrames), m_frameLengths(_frameLengths), m_scale(_scale) {

	m_frameTime = m_frameLengths[m_currentFrame];

	m_texture = ResourceManager::getInstance().getTexture(_name);

	m_sprite.setTexture(*m_texture);
	
	m_frameSize = m_texture->getSize();
	m_frameSize.x /= m_numberOfFrames;
	
	m_sprite.setOrigin(VectorOperations::utof(m_frameSize) / 2.f);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y));
}

Animation::~Animation() {
}

void Animation::play() {
	m_isPlaying = true;
}

void Animation::stop() {
	m_isPlaying = false;
}

void Animation::reset() {
	m_currentFrame = 0;
}

void Animation::update(float _dt) {
	m_frameTime--;

	if (m_frameTime == 0) {
		// next frame
		m_currentFrame = (m_currentFrame + 1) % m_numberOfFrames;
		m_frameTime = m_frameLengths[m_currentFrame] * m_scale;

		m_sprite.setTextureRect(sf::IntRect(m_frameSize.x * m_currentFrame, 0, m_frameSize.x, m_frameSize.y));
	}
}

void Animation::draw() {
	Display::draw(m_sprite);
}
