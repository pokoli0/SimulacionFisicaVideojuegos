#include "ParticleGenerator.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(Particle* p, float rate, float spawnR, GenDistribution sp)
    : particle(*p), particlePerSecond(rate), emissionRange(spawnR), distribution(sp)
{
    std::random_device rd;
    randomizer.seed(rd());
}

PxVec3 ParticleGenerator::calculatePosition()
{
    PxVec3 modPos = particle.getPosition();
    PxVec3 endPos;

    if (distribution == UNIFORMDIST) {

        std::uniform_real_distribution<float> distX(modPos.x - emissionRange, modPos.x + emissionRange);
        std::uniform_real_distribution<float> distY(modPos.y - emissionRange, modPos.y + emissionRange);
        std::uniform_real_distribution<float> distZ(modPos.z - emissionRange, modPos.z + emissionRange);
        endPos = Vector3(distX(randomizer), distY(randomizer), distZ(randomizer));
    }
    else { // normal

        Vector3 dev = { emissionRange, emissionRange, emissionRange };
        std::normal_distribution<float> distX(modPos.x, emissionRange);
        std::normal_distribution<float> distY(modPos.y, emissionRange);
        std::normal_distribution<float> distZ(modPos.z, emissionRange);
        endPos = Vector3(distX(randomizer), distY(randomizer), distZ(randomizer));
    }
    return endPos;
}

void ParticleGenerator::update(double t, ParticleSystem& pS) {
    // Acumula el tiempo
    accumulatedTime += t;

    // Particulas a emitir
    int particlesToEmit = static_cast<int>(accumulatedTime * particlePerSecond);

    for (int i = 0; i < particlesToEmit; ++i) {
        Particle* newParticle = emit();
        if (newParticle) {
            pS.addParticle(newParticle);
        }
    }

    // Restar el tiempo emitido
    accumulatedTime -= particlesToEmit / particlePerSecond;
}