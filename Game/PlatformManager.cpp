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
		togglePlatform(0);
	}
	if (Input::getKeyDown(Input::Num2)) {
		togglePlatform(1);
	}
	if (Input::getKeyDown(Input::Num3)) {
		togglePlatform(2);
	}
	if (Input::getKeyDown(Input::Num4)) {
		togglePlatform(3);
	}
	if (Input::getKeyDown(Input::Num5)) {
		togglePlatform(4);
	}
}

void PlatformManager::draw() {
}

void PlatformManager::onCollision(Collider * _this, Collider * _other) {
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

void PlatformManager::togglePlatform(int _index) {
	if (m_platforms.size() < _index + 1) {
		return;
	}

	if (m_platforms[_index]->isEnabled()) {
		m_platforms[_index]->disable();
	}
	else {
		m_platforms[_index]->enable();
	}
}
