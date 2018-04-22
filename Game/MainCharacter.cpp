#include "MainCharacter.h"
#include "Debug.h"
#include "PhysicsEngine.h"
#include "Input.h"
#include "GameStateManager.h"
#include "FloatOperations.h"
#include "GameSettings.h"
#include "Projectile.h"
#include "ChainedProjectile.h"
#include "VectorOperations.h"
#include "Particles.h"

#include <cmath>

MainCharacter::MainCharacter():
	m_direction {-1},
	m_characterState {CHARACTER_STATE::IDLE},
	m_chainState {CHAIN_STATE::UNCHAINED},
	m_shootingState {SHOOTING_STATE::NOTHING},
	m_ammoState {AMMO_STATE::YES_AMMO},
	m_chain {nullptr},
	m_arrowInCollision {nullptr},
	m_currentShootingPower{ m_minShootingSpeed },
	m_additionalGravityMultiplier { 0.f } {

	setObjectTag("Main");
	setObjectLayer("Player");
	

	// Init shape
	m_shape.setSize(sf::Vector2f{ 40.f, 80.f });
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setFillColor(sf::Color::Blue);

	m_bodyController.load("archer_guy");
	m_bowController.load("archer_guy_bow", false);

	// Create rigid body
	Collider * collider = PhysicsEngine::getInstance().createCollider(this);
	collider->setSize(m_shape.getSize());
	m_colliders.push_back(collider);

	m_rigidBody = PhysicsEngine::getInstance().createRigidBody(collider);
	m_rigidBody->setGravity(true);
	m_rigidBody->setBounceFactor(0.1f);
	collider->setTrigger(false, m_rigidBody);

	// Init transform
	setPosition(sf::Vector2f{ 700.f, 20.f });

	m_numberOfArrows = m_maxArrows;
}

MainCharacter::~MainCharacter() {
}

void MainCharacter::update(float _dt) {
	if (Input::getKeyDown(Input::C)) {
		m_particleSystem = GameStateManager::instantiate(&Particles(), 1);
	}

	m_bodyController.update(_dt);
	m_bowController.update(_dt);

	m_ammoState = m_numberOfArrows > 0 ? AMMO_STATE::YES_AMMO : AMMO_STATE::NO_AMMO;

	movement(_dt);
	extraGravity(_dt);
	jump(_dt);
	shootCharge(_dt);
}

void MainCharacter::draw() {
	m_bodyController.draw();
	
	if (m_ammoState == AMMO_STATE::YES_AMMO) {
		m_bowController.draw();
	}

	//Display::draw(m_shape);
}

void MainCharacter::onCollision(Collider * _this, Collider * _other) {
	auto otherGameObject = _other->getGameObject();

	// Floor contact
	if (otherGameObject->isObjectTag("Floor") || _other->getGameObject()->isObjectTag("BottomFloor")) {
		m_characterState = CHARACTER_STATE::IDLE;
		m_additionalGravityMultiplier = 0.f;
	}

	// Arrow contact
	if (otherGameObject->isObjectLayer("Arrow")) {
		m_arrowInCollision = _other->getGameObject();

		m_characterState = CHARACTER_STATE::IDLE;
		m_additionalGravityMultiplier = 0.f;
	}
	else {
		m_arrowInCollision = nullptr;
	}

	// Arrow pickup
	if (otherGameObject->isObjectTag("CollectableArrow")) {
		m_numberOfArrows++;
	}
}

void MainCharacter::setPosition(sf::Vector2f _pos) {
	m_position = _pos;
	m_shape.setPosition(_pos);
	
	m_bodyController.setPosition(_pos);
	m_bowController.setPosition(_pos);

	for (Collider * c : m_colliders) {
		c->setPosition(_pos);
	}

	if (m_particleSystem) {
		m_particleSystem->setPosition(_pos);
	}
}

GameObject * MainCharacter::clone() {
	return nullptr;
}

void MainCharacter::movement(float _dt) {
	float dx = 0.f;

	if (Input::getKey(Input::A) || Input::getKey(Input::LARROW)) {
		dx += -m_speed;
		m_direction = -1;
	}

	if (Input::getKey(Input::D) || Input::getKey(Input::RARROW)) {
		dx += m_speed;
		m_direction = 1;
	}

	// Animations
	std::string moveTrigger = "idle";
	int comp = FloatOperations::compare(dx, 0.f);

	switch (comp) {
	case 1:
		moveTrigger = "run_right";
		break;
	case -1:
		moveTrigger = "run_left";
		break;
	}

	m_bodyController.setTrigger(moveTrigger);
	m_bowController.setTrigger(moveTrigger);

	// Add pull velocity
	sf::Vector2f delta{ dx, 0 };

	delta *= _dt;

	// Move
	auto vel = getRigidBody()->getVelocity();
	vel.x = dx;
	vel.y = fminf(m_maxLandSpeed, vel.y);
	getRigidBody()->setVelocity(vel);
}

void MainCharacter::extraGravity(float _dt) {
	// if falling, add gravity
	if (m_rigidBody->getVelocity().y > 100) {
		m_additionalGravityMultiplier = m_landingGravityMultiplier;
	}

	// Apply extra gravity to character
	sf::Vector2f vel = m_rigidBody->getVelocity();
	vel.y += GameSettings::GRAVITY * m_additionalGravityMultiplier * _dt;
	m_rigidBody->setVelocity(vel);
}

void MainCharacter::jump(float _dt) {
	if (m_characterState == CHARACTER_STATE::IDLE) {
		if (Input::getKeyDown(Input::SPACE)) {
			m_rigidBody->setVelocity(sf::Vector2f{ 0.f, -m_jumpVelocity });
			m_characterState = CHARACTER_STATE::JUMPING;

			// Destroy jumped on arrow
			if (m_arrowInCollision != nullptr) {
				Projectile * proj = dynamic_cast<Projectile*>(m_arrowInCollision);

				if (proj != nullptr) {
					proj->breakArrow();
					m_arrowInCollision = nullptr;
				}
			}
		}
	}
	
	// Landing
	if (m_characterState == CHARACTER_STATE::JUMPING) {
		if (Input::getKeyUp(Input::SPACE) || m_rigidBody->getVelocity().y > 0) {
			m_additionalGravityMultiplier = m_landingGravityMultiplier;
		}
	}
}

void MainCharacter::shootCharge(float _dt) {
	if (m_ammoState == AMMO_STATE::NO_AMMO) {
		return;
	}

	// Start charging normal shot
	if (Input::getKeyDown(Input::X)) {
		if (m_shootingState == SHOOTING_STATE::NOTHING) {
			if (m_chainState == CHAIN_STATE::CHAINED) {
				breakChain();
				m_chainState = CHAIN_STATE::UNCHAINED;
			}

			m_bowController.setTrigger("pull");

			m_currentShootingPower = m_minShootingSpeed;
			m_shootingState = SHOOTING_STATE::CHARGING_NORMAL;
		}
	}
	
	if (Input::getKeyDown(Input::Z)) {
		if (m_chainState == CHAIN_STATE::CHAINED) {
			if (m_chain->isStatic()) {
				m_chainState = CHAIN_STATE::UNCHAINED;
				pullChain();
			}
		} else if (m_shootingState == SHOOTING_STATE::NOTHING) {
			shootChain(m_direction, m_shootingChainSpeed);
			m_chainState = CHAIN_STATE::CHAINED;

			//m_bowController.setTrigger("pull");

			//m_currentShootingPower = m_minShootingSpeed;
			//m_shootingState = SHOOTING_STATE::CHARGING_CHAINED;
		}
	}

	// Release normal shot
	if (Input::getKeyUp(Input::X) && m_shootingState == SHOOTING_STATE::CHARGING_NORMAL) {
		shoot(m_direction, m_currentShootingPower);
		m_shootingState = SHOOTING_STATE::BOW_RELEASE;
	}

	//if (Input::getKeyUp(Input::X) && m_shootingState == SHOOTING_STATE::CHARGING_CHAINED) {
	//	shootChain(m_direction, m_currentShootingPower);
	//	m_shootingState = SHOOTING_STATE::BOW_RELEASE;
	//	m_chainState = CHAIN_STATE::CHAINED;
	//}

	// Charge shoot power
	if (m_shootingState == SHOOTING_STATE::CHARGING_NORMAL || m_shootingState == SHOOTING_STATE::CHARGING_CHAINED) {
		m_currentShootingPower = fminf(m_currentShootingPower + m_shootingChargeSpeed * _dt, m_maxShootingSpeed);
		
		// Update animation
		float animationTime = (m_currentShootingPower - m_minShootingSpeed) / (m_maxShootingSpeed - m_minShootingSpeed);
		m_bowController.setAnimationTime(animationTime);
	}

	// Release shot
	if (m_shootingState == SHOOTING_STATE::BOW_RELEASE) {
		float delta = (m_maxShootingSpeed - m_minShootingSpeed) * m_bowReleaseSpeed * _dt;
		m_currentShootingPower = fmaxf(m_currentShootingPower - delta, m_minShootingSpeed);

		// Update animation
		float animationTime = (m_currentShootingPower - m_minShootingSpeed) / (m_maxShootingSpeed - m_minShootingSpeed);
		m_bowController.setAnimationTime(animationTime);

		// Release over
		if (FloatOperations::compare(animationTime, 0.f) <= 0) {
			m_bowController.setTrigger("reload");
			m_shootingState = SHOOTING_STATE::BOW_RELOAD;
		}
	}

	// Reload shot
	if (m_shootingState == SHOOTING_STATE::BOW_RELOAD) {
		if (!m_bowController.isPlaying()) {
			m_shootingState = SHOOTING_STATE::NOTHING;
			m_bowController.setTrigger("end_reload");
		}
	}
}

void MainCharacter::shoot(int _direction, float _velocity) {
	m_numberOfArrows--;

	GameObject * projectile = GameStateManager::instantiate(&Projectile(_direction), 1);

	sf::Vector2f projPos = m_position + sf::Vector2f{ m_shape.getSize().x * static_cast<float>(_direction), 0.f };
	projectile->setPosition(projPos);

	projectile->getRigidBody()->setVelocity(sf::Vector2f{_direction * _velocity, 0.f});

	projectile->setActive(true);
}

void MainCharacter::shootChain(int _direction, float _velocity) {
	m_numberOfArrows--;

	m_chain = dynamic_cast<ChainedProjectile*> (GameStateManager::instantiate(&ChainedProjectile(_direction), 1));

	m_chain->setPlayerRef(this);

	//sf::Vector2f projPos = m_position + sf::Vector2f{ m_shape.getSize().x * static_cast<float>(_direction), 0.f };
	sf::Vector2f projPos = m_position + sf::Vector2f{ 0.f, -100.f };
	m_chain->setPosition(projPos);

	//m_chain->getRigidBody()->setVelocity(sf::Vector2f{ _direction * _velocity, 0.f });
	m_chain->getRigidBody()->setVelocity(sf::Vector2f{0.f, -_velocity});

	m_chain->setActive(true);
}

void MainCharacter::pullChain() {
	sf::Vector2f pullDirection = m_chain->getPosition() - getPosition();
	pullDirection /= VectorOperations::norm(pullDirection);

	m_additionalGravityMultiplier = 0.f;

	auto velocity = getRigidBody()->getVelocity();
	velocity.y = fminf(velocity.y, 0.f);
	velocity += m_pullSpeed * pullDirection;
	getRigidBody()->setVelocity(velocity);

	m_chain->pullChain(-pullDirection);
}

void MainCharacter::breakChain() {
	m_chain->destroyChain();
}
