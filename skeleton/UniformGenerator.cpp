#include "UniformGenerator.h"

UniformGenerator::UniformGenerator(Particle* p, float rate, float range, float spawnRange, GenDistribution dist)
    : ParticleGenerator(p, rate, spawnRange, dist)
{
    cout << "Uniform generator created." << endl;

    const PxVec3 vel = p->getVelocity();  // Velocidad inicial de la partícula
    const PxVec3 desv = PxVec3(range, range, range);  // Desviación máxima para la velocidad

    // Asegura que la velocidad en Y sea siempre positiva (hacia arriba)
    minVel = vel - desv;
    maxVel = vel + desv;
    minVel.y = 10.0f;  // Velocidad mínima en Y (hacia arriba)
    maxVel.y = 30.0f;  // Velocidad máxima en Y (hacia arriba)
}

UniformGenerator::~UniformGenerator()
{
    for (Particle* p : particles)
    {
        delete p; // Elimina cada partícula creada
    }
    particles.clear();
}

Particle* UniformGenerator::emit()
{
    ud distX(minVel.x, maxVel.x);
    ud distY(minVel.y, maxVel.y);
    ud distZ(minVel.z, maxVel.z);

    // Calcula la velocidad aleatoria en las direcciones X, Y, Z
    const PxVec3 randomVelocity(distX(randomizer), distY(randomizer), distZ(randomizer));

    Particle* p = new Particle();  // Crea la nueva partícula

    // Generar un color aleatorio (amarillo, naranja, rojo) - PARA EL FUEGO DEL JUEGO 
    PxVec4 color;
    const int randomColor = rand() % 3; // 0, 1 o 2

    switch (randomColor) {
    case 0: color = PxVec4(1.0f, 1.0f, 0.0f, 1.0f); break; // Amarillo
    case 1: color = PxVec4(1.0f, 0.5f, 0.0f, 1.0f); break; // Naranja
    case 2: color = PxVec4(1.0f, 0.0f, 0.0f, 1.0f); break; // Rojo
    }

    p->setVelocity(randomVelocity);  // Asigna la velocidad calculada
    p->setPosition(calculatePosition());  // Calcula y asigna la posición
    p->setColor(color);

    particles.push_back(p);

    return p;
}

