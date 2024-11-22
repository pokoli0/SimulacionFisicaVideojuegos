#pragma once

#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
public: 
	SpringForceGenerator(double kCoeff, double _restingLength, Particle* _other);

	virtual ~SpringForceGenerator(){}

	virtual PxVec3 calculateForce(Particle* particle) override;
	virtual void update(double t) override {}

	inline void setK(double k) { K = k; }

private:
	double K; 
	double restingLength;
	Particle* other;
};

