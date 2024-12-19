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
public:
	ParticleGenerator(Particle* p, float particleSecond, float spawnR, GenDistribution sp);
	virtual ~ParticleGenerator() = default;

	virtual Particle* emit() = 0;

	PxVec3 calculatePosition();

	void update(double t, ParticleSystem& pS);

	// getters
	float getParticlePerSecond() const { return particlePerSecond; }

	list<ParticleGenerator*>::iterator getIterator() const { return iterator; }
	void setIterator(list<ParticleGenerator*>::iterator i) { iterator = i; }

protected:
	mt19937 randomizer;
	float particlePerSecond;
	float accumulatedTime = 0.0f;
	float emissionRange;
	GenDistribution distribution;

	// particula a instanciar
	Particle particle;

	list<ParticleGenerator*>::iterator iterator;

};

