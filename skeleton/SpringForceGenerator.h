#pragma once

#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
public: 
	SpringForceGenerator(double kCoeff, double _restingLength, Particle* _other);

	virtual ~SpringForceGenerator(){}

	virtual PxVec3 calculateForce(Particle* particle) override;
	virtual PxVec3 calculateForce(RigidBody* r) override;

	virtual void update(double t) override {}

	inline void setK(double k) { K = k; }

protected:
	double K; 
	double restingLength;
	Particle* otherP;
};

