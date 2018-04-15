#include "Particles.h"
#include "Display.h"
#include "ResourceManager.h"
#include "Debug.h"

int particles = 50;
float period = .01f;
float size = 10.f;

Particles::Particles() : m_currentParticle{ 0 }, m_initialized{ false }, m_counter{0.f} {
	auto tex = ResourceManager::getInstance().getTexture("ice_smoke");
	tex->setSmooth(true);
	m_sprite.setTexture(*tex);
	m_sprite.setOrigin(tex->getSize().x / 2.f, tex->getSize().y / 2.f);
}

Particles::~Particles() {
}

void Particles::update(float _dt) {
	m_counter += _dt;

	if (m_counter > period) {
		m_currentParticle = (m_currentParticle + 1) % particles;
		m_counter = 0;
	}
}

void Particles::draw() {
	int particleIndex = particles - m_currentParticle;
	int alpha = 255;
	float scale;
	for (int i = 0; i < m_particles.size(); ++i) {
		alpha = (float)particleIndex / particles * 255;
		scale = (float)particleIndex / particles * 0.3;

		m_sprite.setPosition(m_particles[i]);
		m_sprite.setColor(sf::Color{255, 255, 255, static_cast<sf::Uint8>(alpha)});
		m_sprite.setScale(scale, scale);

		Display::draw(m_sprite);

		particleIndex = (particleIndex + 1) % particles;
	}
}

void Particles::onCollision(Collider * _this, Collider * _other) {
}

GameObject * Particles::clone() {
	return new Particles();
}

void Particles::setPosition(sf::Vector2f _pos) {
	if (!m_initialized) {
		for (int i = 0; i < particles; ++i) m_particles.push_back(_pos);
		m_initialized = true;
	}
	
	m_position = _pos;
	m_particles[m_currentParticle] = _pos;
}
