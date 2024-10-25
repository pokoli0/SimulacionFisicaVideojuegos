#pragma once
#include "ParticleGenerator.h"
#include <random>

using namespace std;
using namespace physx;

class NormalGenerator : public ParticleGenerator
{
public:
	NormalGenerator(Particle* p, float rate, PxVec3 desv, float spawnR, GenDistribution dist);

	Particle* emit() override;

private:

	PxVec3 velocidadMedia;
	PxVec3 desvVelo;

};

using nd = normal_distribution<float>;

