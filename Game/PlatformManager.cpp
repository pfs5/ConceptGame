#include "PlatformManager.h"
#include "Input.h"
#include "GameStateManager.h"
#include "Debug.h"

PlatformManager::PlatformManager() {
}


PlatformManager::~PlatformManager() {
	for (auto p : m_platforms) {
		delete p;
	}
}

void PlatformManager::update(float _dt) {
	if (!m_initiated) {
		m_initiated = true;
		init();
	}

	// Spawn
	if (Input::getKeyDown(Input::Num1)) {
		if (m_platforms[0]->isEnabled()) {
			m_platforms[0]->disable();
		}
		else {
			m_platforms[0]->enable();
		}
	}

	if (Input::getKeyDown(Input::Num2)) {
		if (m_platforms[1]->isEnabled()) {
			m_platforms[1]->disable();
		}
		else {
			m_platforms[1]->enable();
		}
	}

	if (Input::getKeyDown(Input::Num3)) {
		if (m_platforms[2]->isEnabled()) {
			m_platforms[2]->disable();
		}
		else {
			m_platforms[2]->enable();
		}
	}

	if (Input::getKeyDown(Input::Num4)) {
		if (m_platforms[3]->isEnabled()) {
			m_platforms[3]->disable();
		}
		else {
			m_platforms[3]->enable();
		}
	}
}

void PlatformManager::draw() {
}

void PlatformManager::onCollision(Collider * _other) {
}

GameObject * PlatformManager::clone() {
	return nullptr;
}

void PlatformManager::setPosition(sf::Vector2f _pos) {
}

void PlatformManager::init() {
	// Init platforms
	for (auto pos : m_positions) {
		auto newPlat = static_cast<Platform*>(GameStateManager::instantiate(&Platform(pos)));
		newPlat->setPosition(pos);

		//newPlatform->disable();

		m_platforms.push_back(newPlat);
	}
}
