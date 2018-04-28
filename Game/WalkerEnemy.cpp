#include "WalkerEnemy.h"
#include "ResourceManager.h"
#include "Display.h"
#include "PhysicsEngine.h"
#include "VectorOperations.h"
#include "Projectile.h"
#include "GameStateManager.h"
#include "Explosion.h"
#include "Debug.h"

WalkerEnemy::WalkerEnemy() : m_walkState{WALK_STATE::STEP_ONE} {
	setObjectLayer("WalkerEnemy");
	setObjectTag("Enemy");

	//auto tex = ResourceManager::getInstance().getTexture("walker_enemy");
	//tex->setSmooth(true);
	//m_sprite.setTexture(*tex);
	//m_sprite.setOrigin(VectorOperations::utof(tex->getSize()) / 2.f);

	// Eye collider
	auto eyeCollider = PhysicsEngine::getInstance().createCollider(this);
	eyeCollider->setID(EYE_COLLIDER_ID);
	eyeCollider->setSize(sf::Vector2f{ 50.f, 20.f });
	eyeCollider->setOffset(EYE_COL_OFFSET_1);
	m_colliders.push_back(eyeCollider);

	// Wheel collider
	auto wheelCollider = PhysicsEngine::getInstance().createCollider(this);
	wheelCollider->setID(WHEEL_COLLIDER_ID);
	wheelCollider->setSize(sf::Vector2f{ 50.f, 30.f });
	wheelCollider->setOffset(WHEEL_COL_OFFSET_1);
	m_colliders.push_back(wheelCollider);

	// Body collider
	auto bodyCollider = PhysicsEngine::getInstance().createCollider(this);
	bodyCollider->setID(BODY_COLLIDER_ID);
	bodyCollider->setSize(sf::Vector2f{ 60.f, 100.f });
	bodyCollider->setOffset(sf::Vector2f{ -5.f, -30.f });
	m_colliders.push_back(bodyCollider);

	// Leg collider
	auto legCollider = PhysicsEngine::getInstance().createCollider(this);
	legCollider->setID(LEG_COLLIDER_ID);
	legCollider->setSize(sf::Vector2f{ 50.f, 80.f });
	legCollider->setOffset(sf::Vector2f{ -30.f, 60.f });
	m_colliders.push_back(legCollider);

	// Base collider
	auto baseCollider = PhysicsEngine::getInstance().createCollider(this);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(baseCollider);

	baseCollider->setID(BASE_COLLIDER_ID);
	baseCollider->setSize(sf::Vector2f{ 100, 20 });
	baseCollider->setOffset(sf::Vector2f{-20.f, 110.f});
	baseCollider->setTrigger(false, m_rigidBody);
	m_colliders.push_back(baseCollider);

	// Init animator
	m_bodyController.load("walker_enemy");
}

WalkerEnemy::~WalkerEnemy() {
}

void WalkerEnemy::update(float _dt) {
	m_bodyController.update(_dt);
	m_counter += _dt;

	float speed = .4f * 2.f;
	int scale = 5;

	switch (m_walkState) {
		case WALK_STATE::STEP_ONE: {
			move(sf::Vector2f{ speed, 0.f });

			// move eye collider
			float offset = 10.f / (7.f / 60.f * scale) * m_counter;
			m_colliders[EYE_COLLIDER_ID]->setOffset(EYE_COL_OFFSET_2 - sf::Vector2f{0, offset });
			m_colliders[WHEEL_COLLIDER_ID]->setOffset(WHEEL_COL_OFFSET_2 - sf::Vector2f{ 0, offset });

			if (m_counter > 7.f / 60.f * scale) {
				m_walkState = WALK_STATE::HOLD_ONE;

				m_colliders[EYE_COLLIDER_ID]->setOffset(EYE_COL_OFFSET_2);
				m_colliders[WHEEL_COLLIDER_ID]->setOffset(WHEEL_COL_OFFSET_2);
			}

			break;
		}
		case WALK_STATE::HOLD_ONE:
			if (m_counter > 11.f / 60.f * scale) {
				m_walkState = WALK_STATE::STEP_TWO;
				m_colliders[EYE_COLLIDER_ID]->setOffset(EYE_COL_OFFSET_1);
				m_colliders[WHEEL_COLLIDER_ID]->setOffset(WHEEL_COL_OFFSET_1);
			}
			break;
		case WALK_STATE::STEP_TWO: {
			move(sf::Vector2f{ speed, 0.f });
			// move eye collider
			float offset = 10.f / (7.f / 60.f * scale) * (m_counter - 10.f / 60.f * scale);
			m_colliders[EYE_COLLIDER_ID]->setOffset(EYE_COL_OFFSET_2 - sf::Vector2f{ 0, offset });
			m_colliders[WHEEL_COLLIDER_ID]->setOffset(WHEEL_COL_OFFSET_2 - sf::Vector2f{ 0, offset });

			if (m_counter > 18.f / 60.f * scale) {
				m_walkState = WALK_STATE::HOLD_TWO;
				m_colliders[EYE_COLLIDER_ID]->setOffset(EYE_COL_OFFSET_2);
				m_colliders[WHEEL_COLLIDER_ID]->setOffset(WHEEL_COL_OFFSET_2);
			}
			break;
		}
		case WALK_STATE::HOLD_TWO:
			if (!m_bodyController.isPlaying()) {
				m_walkState = WALK_STATE::STEP_ONE;
				m_counter = 0.f;
				m_bodyController.playAnimation("walk_right");
			}
			break;
		case WALK_STATE::DESTROYED:
			legDestroySequence(_dt);
			break;
		case WALK_STATE::DRIVE:
			// Move right
			move(sf::Vector2f{DRIVE_SPEED * _dt, 0.f});
		break;
	}
}

void WalkerEnemy::draw() {
	//Display::draw(m_sprite);
	m_bodyController.draw();
}

void WalkerEnemy::onCollision(Collider * _this, Collider * _other) {
	if (_this->getGameObject() == _other->getGameObject()) {
		return;
	}

	// Check if base hit
	if (_other->getGameObject()->isObjectTag("BaseTree")) {
		GameStateManager::instantiate(&Explosion(getPosition(), 1, "one")); // explosion
		death();
	}

	int id = _this->getID();
	if (id == EYE_COLLIDER_ID|| id == WHEEL_COLLIDER_ID) {
		if (_other->getGameObject()->getObjectTag() == "Arrow") {
			auto arrow = dynamic_cast<Projectile*>(_other->getGameObject());

			if (!arrow->isStatic()) {
				// Get hit
				GameStateManager::instantiate(&Explosion(_other->getGameObject()->getPosition(), 1, "one")); // explosion
				arrow->destroyArrow();

				death();
			}

		}
	}
	if (id == BODY_COLLIDER_ID) {
		if (m_walkState == WALK_STATE::STATIC && _other->getGameObject()->getObjectTag() == "Floor") {
			m_walkState = WALK_STATE::DRIVE;
		}

		if (_other->getGameObject()->getObjectTag() == "Arrow") {
			auto arrow = dynamic_cast<Projectile*>(_other->getGameObject());
			arrow->breakArrow();
		}
	}
	if (id == LEG_COLLIDER_ID) {
		if (_other->getGameObject()->getObjectTag() == "Arrow" && m_walkState != WALK_STATE::DESTROYED) {
			auto arrow = dynamic_cast<Projectile*>(_other->getGameObject());

			if (!arrow->isStatic()) {
				// Get hit
				GameStateManager::instantiate(&Explosion(_other->getGameObject()->getPosition(), 1, "two")); // explosion
				arrow->destroyArrow();

				destroyLegs();
			}

		}
	}
	if (id == BASE_COLLIDER_ID) {

	}
}

GameObject * WalkerEnemy::clone() {
	return new WalkerEnemy();
}

void WalkerEnemy::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_sprite.setPosition(_pos);
	m_bodyController.setPosition(_pos);
	for (auto col : m_colliders) {
		if (col != nullptr) { col->setPosition(_pos); };
	}
}

void WalkerEnemy::destroyLegs() {
	m_bodyController.pause();
	m_walkState = WALK_STATE::DESTROYED;
	m_destructionState = DESTRUCTION_STATE::START;
	m_counter = 0.f;

	// Disable leg collider
	PhysicsEngine::getInstance().deleteCollider(m_colliders[LEG_COLLIDER_ID]);
	m_colliders[LEG_COLLIDER_ID] = nullptr;
}

void WalkerEnemy::legDestroySequence(float _dt) {
	m_counter += _dt;
	switch (m_destructionState) {
	case DESTRUCTION_STATE::START:
		if (m_counter > .3f) {
			m_destructionState = DESTRUCTION_STATE::EXPLOSION_ONE;
			m_counter = 0.f;

			GameStateManager::instantiate(&Explosion(getPosition() + sf::Vector2f{ -10, 20 }, 1, "two")); // explosion
		}
		break;
	case DESTRUCTION_STATE::EXPLOSION_ONE:
		if (m_counter > .3f) {
			m_destructionState = DESTRUCTION_STATE::EXPLOSION_TWO;
			m_counter = 0.f;

			GameStateManager::instantiate(&Explosion(getPosition() + sf::Vector2f{ -40, 50 }, 1, "two")); // explosion
		}
		break;
	case DESTRUCTION_STATE::EXPLOSION_TWO:
		if (m_counter > .3f) {
			m_destructionState = DESTRUCTION_STATE::EXPLOSION_THREE;
			m_counter = 0.f;

			GameStateManager::instantiate(&Explosion(getPosition() + sf::Vector2f{ -10, 100 }, 1, "two")); // explosion
		}
		break;
	case DESTRUCTION_STATE::EXPLOSION_THREE:
		if (m_counter > .3f) {
			m_destructionState = DESTRUCTION_STATE::END;
			m_counter = 0.f;

			m_bodyController.playAnimation("transition");
			GameStateManager::instantiate(&Explosion(getPosition() + sf::Vector2f{ -20, 10 }, 1, "three")); // explosion
		}
		break;
	case DESTRUCTION_STATE::END:
		if (!m_bodyController.isPlaying()) {
			m_bodyController.playAnimation("drive");
			
			m_colliders[BASE_COLLIDER_ID]->setSize(sf::Vector2f{ 60.f, 100.f });
			m_colliders[BASE_COLLIDER_ID]->setOffset(sf::Vector2f{ -5.f, -30.f });

			m_walkState = WALK_STATE::STATIC;
		}
		break;
	}
}

void WalkerEnemy::death() {
	notifyObservers();

	// Destroy enemy
	GameStateManager::destroyObject(this);
}

void WalkerEnemy::notifyObservers() {
	for (auto &o : m_observers) {
		o->notify();
	}
}

void WalkerEnemy::attachObserver(EnemyObserver * _o) {
	m_observers.push_back(_o);
}
