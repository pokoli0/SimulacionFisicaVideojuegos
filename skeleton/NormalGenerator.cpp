#include "NormalGenerator.h"

NormalGenerator::NormalGenerator(Particle* p, float rate, PxVec3 desv, float spawnR, GenDistribution dist)
    : ParticleGenerator(p, rate, spawnR, dist), velocidadMedia(p->getVelocity()), desvVelo(desv) 
{

}

// using nd = normal_distribution<float>;
Particle* NormalGenerator::emit()
{
    nd distX(velocidadMedia.x, desvVelo.x);
    nd distY(velocidadMedia.y, desvVelo.y);
    nd distZ(velocidadMedia.z, desvVelo.z);

    PxVec3 randomVelocity(distX(randomizer), distY(randomizer), distZ(randomizer));
    Particle* p = new Particle(particle);

    p->setVelocity(randomVelocity);
    p->setPosition(calculatePosition());

    return p;
}
