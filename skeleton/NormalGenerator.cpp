#include "NormalGenerator.h"

NormalGenerator::NormalGenerator(Particle* p, float rate, PxVec3 desv, float spawnR, GenDistribution dist, float ratio, bool f)
    : ParticleGenerator(p, rate, spawnR, dist), velocidadMedia(p->getVelocity()), desvVelo(desv), fire(f)
{
    particlesRatio = ratio;
}

NormalGenerator::~NormalGenerator()
{
    particles.clear();
}

// using nd = normal_distribution<float>;
Particle* NormalGenerator::emit()
{
    nd distX(velocidadMedia.x, desvVelo.x);
    nd distY(velocidadMedia.y, desvVelo.y);
    nd distZ(velocidadMedia.z, desvVelo.z);

    const PxVec3 randomVelocity(distX(randomizer), distY(randomizer), distZ(randomizer));

    // Generar un color aleatorio (amarillo, naranja, rojo) - PARA EL FUEGO DEL JUEGO 
    PxVec4 color;

    if (fire) {
        const int randomColor = rand() % 3; // 0, 1 o 2

        switch (randomColor)
        {
        case 0: color = PxVec4(1.0f, 1.0f, 0.0f, 1.0f);
            break;
        case 1: color = PxVec4(1.0f, 0.5f, 0.0f, 1.0f);
            break;
        case 2: color = PxVec4(1.0f, 0.0f, 0.0f, 1.0f);
            break;
        }
    }
    else {
        const int randomColor = rand() % 2; // 0, 1
        color = PxVec4(0.0f, 0.1f, 0.9f, 1.0f);

        switch (randomColor)
        {
        case 0:
            color = PxVec4(1.0f, 1.0f, 1.0f, 1.0f); // Blanco
            break;
        case 1:
            color = PxVec4(0.8f, 0.9f, 1.0f, 1.0f); // Azul muy claro
            break;
        }

    }


    Particle* p = new Particle();

    p->setVelocity(randomVelocity);
    p->setPosition(calculatePosition());
    p->setRatio(particlesRatio);
    p->setColor(color);

    particles.push_back(p);

    return p;
}
