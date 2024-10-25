#include "UniformGenerator.h"

UniformGenerator::UniformGenerator(Particle* p, float rate, float range, float spawnRange, GenDistribution dist)
    : ParticleGenerator(p, rate, spawnRange, dist)
{
    PxVec3 vel = p->getVelocity();
    PxVec3 desv = PxVec3(range, range, range);

    minVel = vel - desv;
    maxVel = vel + desv;
}

// using ud = uniform_real_distribution<float>;
Particle* UniformGenerator::emit()
{
    ud distX(minVel.x, maxVel.x);
    ud distY(minVel.y, maxVel.y);
    ud distZ(minVel.z, maxVel.z);

    PxVec3 randomVelocity(distX(randomizer), distY(randomizer), distZ(randomizer));

    Particle* p = new Particle(particle);

    p->setVelocity(randomVelocity);
    p->setPosition(calculatePosition());

    return p;
}
