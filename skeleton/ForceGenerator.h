#pragma once

#include <vector>

#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator(float dur);
	~ForceGenerator();

	virtual PxVec3 calculateForce(Particle* p) = 0;
	virtual void update(double t) = 0;

	// Getters

	bool isAlive() { return alive; }

protected:
	float duration;
	bool alive;
};
