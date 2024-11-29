#include "ParticleGenerator.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(Particle* p, float particleSecond, float spawnR, GenDistribution sp)
    : particle(*p), particlePerSecond(particleSecond), emissionRange(spawnR), distribution(sp)
{
    random_device rd;
    randomizer.seed(rd());
}

PxVec3 ParticleGenerator::calculatePosition()
{
    const PxVec3 modPos = particle.getPosition();
    PxVec3 endPos;

    if (distribution == UNIFORMDIST) {

        std::uniform_real_distribution<float> distX(modPos.x - emissionRange, modPos.x + emissionRange);
        std::uniform_real_distribution<float> distY(modPos.y - emissionRange, modPos.y + emissionRange);
        std::uniform_real_distribution<float> distZ(modPos.z - emissionRange, modPos.z + emissionRange);
        endPos = Vector3(distX(randomizer), distY(randomizer), distZ(randomizer));
    }
    else { // normal

        const Vector3 dev = { emissionRange, emissionRange, emissionRange };
        std::normal_distribution<float> distX(modPos.x, emissionRange);
        std::normal_distribution<float> distY(modPos.y, emissionRange);
        std::normal_distribution<float> distZ(modPos.z, emissionRange);
        endPos = Vector3(distX(randomizer), distY(randomizer), distZ(randomizer));
    }
    return endPos;
}

void ParticleGenerator::update(double t, ParticleSystem& system)
{
    const int particles = static_cast<int>(accumulatedTime * particlePerSecond);

    for (int i = 0; i < particles; i++) {
        Particle* newParticle = emit();
        if (!newParticle) {
            cout << "noNueva" << endl;
        }
        else system.addParticle(newParticle);
    }

    accumulatedTime += t;
    accumulatedTime -= particles / particlePerSecond;
}