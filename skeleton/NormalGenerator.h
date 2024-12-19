#pragma once
#include "ParticleGenerator.h"
#include <random>

using namespace std;
using namespace physx;

class NormalGenerator : public ParticleGenerator
{
public:
	NormalGenerator(Particle* p, float rate, PxVec3 desv, float spawnR, GenDistribution dist, float ratio, bool f);
	~NormalGenerator();
	Particle* emit() override;

private:

	PxVec3 velocidadMedia;
	PxVec3 desvVelo;
	std::vector<Particle*> particles;

	float particlesRatio;

	bool fire;
};

using nd = normal_distribution<float>;

