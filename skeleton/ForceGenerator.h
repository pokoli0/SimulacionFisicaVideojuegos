#pragma once

#include <vector>

#include "Particle.h"
#include <iostream>

class ForceGenerator
{
public:
	ForceGenerator(float dur = -1.0f);
	~ForceGenerator();

	virtual PxVec3 calculateForce(Particle* p) = 0;
	virtual PxVec3 calculateForce(PxRigidDynamic* r) = 0;

	virtual void update(double t) = 0;

	// Getters
	bool isAlive() const { return alive; }

protected:
	float duration;
	bool alive;
};
