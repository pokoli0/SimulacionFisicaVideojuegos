#pragma once
#include "Particle.h"

#include <random>
class ParticleSystem;


using namespace physx;
using namespace std;

enum GenDistribution {
	UNIFORMDIST,
	NORMALDIST
};

class ParticleGenerator
{
protected:
	mt19937 randomizer;
	float particlePerSecond;
	float accumulatedTime = 0.0f;
	float emissionRange;
	GenDistribution distribution;

	Particle particle;

public:
	ParticleGenerator(Particle* p, float rate, float spawnR, GenDistribution sp);

	virtual Particle* emit() = 0;

	PxVec3 calculatePosition();

	void update(double t, ParticleSystem& pS);

	// getters
	float getParticlePerSecond() const { return particlePerSecond; }
};

