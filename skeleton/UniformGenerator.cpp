#include "UniformGenerator.h"

UniformGenerator::UniformGenerator(Particle* p, float rate, float range, float spawnRange, GenDistribution dist)
    : ParticleGenerator(p, rate, spawnRange, dist)
{
    cout << "Uniform generator created." << endl;

    PxVec3 vel = p->getVelocity();  // Velocidad inicial de la partícula
    PxVec3 desv = PxVec3(range, range, range);  // Desviación máxima para la velocidad

    // Asegura que la velocidad en Y sea siempre positiva (hacia arriba)
    minVel = vel - desv;
    maxVel = vel + desv;
    minVel.y = 10.0f;  // Velocidad mínima en Y (hacia arriba)
    maxVel.y = 30.0f;  // Velocidad máxima en Y (hacia arriba)
}

Particle* UniformGenerator::emit()
{
    ud distX(minVel.x, maxVel.x);
    ud distY(minVel.y, maxVel.y);
    ud distZ(minVel.z, maxVel.z);

    // Calcula la velocidad aleatoria en las direcciones X, Y, Z
    PxVec3 randomVelocity(distX(randomizer), distY(randomizer), distZ(randomizer));

    Particle* p = new Particle(particle);  // Crea la nueva partícula

    //cout << "Generated velocity: " << randomVelocity.x << ", " << randomVelocity.y << ", " << randomVelocity.z << endl;

    p->setVelocity(randomVelocity);  // Asigna la velocidad calculada
    p->setPosition(calculatePosition());  // Calcula y asigna la posición

    return p;
}

