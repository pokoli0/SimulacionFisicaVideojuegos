#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class BuoyantForce : public ForceGenerator
{
public:
	BuoyantForce(float h, float V, float d);
	~BuoyantForce();

	// f = m*a
	PxVec3 calculateForce(Particle* p) override;
	PxVec3 calculateForce(RigidBody* r) override;

	void update(double t) override {};


protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle; // For representation
};

