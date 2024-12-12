#pragma once

#include <vector>

#include "Particle.h"
#include "RigidBody.h"

#include <iostream>

enum class ForceType {
	WIND,
	GRAVITY,
	BUOYANT,
	TORNADO,
	EXPLOSION,
	SPRING,
	DEF
};

class ForceGenerator
{
public:
	ForceGenerator(float dur = -1.0f, ForceType t = ForceType::DEF);
	~ForceGenerator();

	virtual PxVec3 calculateForce(Particle* p) = 0;
	virtual PxVec3 calculateForce(RigidBody* r) = 0;

	virtual void update(double t) = 0;

	// Getters
	bool isAlive() const { return alive; }
	ForceType getForceType() const { return type; }

protected:
	float duration;
	bool alive;

	ForceType type;
};
