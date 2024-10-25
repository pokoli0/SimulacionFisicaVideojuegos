#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <iostream>

class Particle;

using namespace physx;
using namespace std;

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
