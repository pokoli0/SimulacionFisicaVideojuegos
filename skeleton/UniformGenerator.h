#pragma once
#include "ParticleGenerator.h"
#include <random>

class Particle;

using namespace physx;

class UniformGenerator : public ParticleGenerator
{
public:
    UniformGenerator(Particle* p, float rate, float range, float spawnRange, GenDistribution dist);

    Particle* emit() override;

private:
    PxVec3 minVel;
    PxVec3 maxVel;

};

using ud = uniform_real_distribution<float>;
