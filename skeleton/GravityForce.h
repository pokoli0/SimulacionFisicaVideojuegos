#pragma once

#include "ForceGenerator.h"

class GravityForce : public ForceGenerator
{
public:
	GravityForce(Vector3 g, float dur);
	~GravityForce();

	// f = m*a
	PxVec3 calculateForce(Particle* p) override;
	void update(double t) override;


protected:
	// aceleracion de la gravedad
	PxVec3 gAcceleration;
};

