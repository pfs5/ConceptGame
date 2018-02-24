#pragma once
#include "RigidBody.h"
#include "Collider.h"
#include "PhysicsLayers.h"

class Collider;

/**
	Generic game object for the engine. All objects in the game inherit the class
	in order to work with the engine and game.
**/
class GameObject {
protected:
	std::string m_objectTag = "";
	int m_physicsLayer = 0;

	// Transform
	sf::Vector2f m_position;

	// State
	bool m_isActive = true;
	
	// Physics
	RigidBody * m_rigidBody;
	std::vector<Collider*> m_colliders;

public:
	GameObject();
	~GameObject();

	// Game core
	virtual void update(float _dt) = 0;
	virtual void draw() = 0;

	// Physics
	void setRigidBody(RigidBody *_rb);
	RigidBody * getRigidBody();
	void addCollider(Collider *_c);

	virtual void onCollision(Collider * _other) = 0;

	// Transform
	void move(sf::Vector2f _delta);
	
	// Prototype pattern allows cloning of gameobjects = prefab mechanism
	virtual GameObject * clone() = 0;

	#pragma region Getters and setters
public:
	inline std::string getObjectTag() const { return m_objectTag; };

	void setObjectLayer(std::string layer);
	std::string getObjectLayer();
	int getLayerNumber();

	virtual void setPosition(sf::Vector2f _pos) = 0;
	inline sf::Vector2f getPosition() { return m_position; };

	inline void setActive(bool _a) { m_isActive = _a; };
	inline bool isActive() { return m_isActive; };
	#pragma endregion
};

