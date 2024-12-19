#include "NormalGenerator.h"

NormalGenerator::NormalGenerator(Particle* p, float rate, PxVec3 desv, float spawnR, GenDistribution dist, float ratio)
    : ParticleGenerator(p, rate, spawnR, dist), velocidadMedia(p->getVelocity()), desvVelo(desv) 
{
    particlesRatio = ratio;
}

NormalGenerator::~NormalGenerator()
{
    for (Particle* p : particles)
    {
        delete p; // Elimina cada partícula creada
    }
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
    const int randomColor = rand() % 3; // 0, 1 o 2

    switch (randomColor) {
    case 0: color = PxVec4(1.0f, 1.0f, 0.0f, 1.0f); break; // Amarillo
    case 1: color = PxVec4(1.0f, 0.5f, 0.0f, 1.0f); break; // Naranja
    case 2: color = PxVec4(1.0f, 0.0f, 0.0f, 1.0f); break; // Rojo
    }

    Particle* p = new Particle();

    p->setVelocity(randomVelocity);
    p->setPosition(calculatePosition());
    p->setRatio(particlesRatio);
    p->setColor(color); // Asigna el color generado

    particles.push_back(p);

    return p;
}
