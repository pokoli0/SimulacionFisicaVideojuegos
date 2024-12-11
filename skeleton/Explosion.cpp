#include "Explosion.h"
#include <cmath>

Explosion::Explosion(PxVec3 center, float intensity, float radius, float tau, const std::list<Particle*>& particles)
    : ForceGenerator(-1.0f), explosionCenter(center), intensity(intensity), radius(radius), tau(tau), elapsedTime(0), affectedParticles(particles) 
{}

PxVec3 Explosion::calculateForce(Particle* p) {
    if (!p || std::find(affectedParticles.begin(), affectedParticles.end(), p) == affectedParticles.end()) return PxVec3(0, 0, 0);

    PxVec3 displacement = p->getPosition() - explosionCenter;
    float distance = displacement.magnitude();

    // Si está fuera del radio de la explosión, no hay fuerza
    if (distance > radius) return PxVec3(0, 0, 0);

    // Fuerza según la fórmula del enunciado
    float r2 = distance * distance;
    float timeFactor = exp(-elapsedTime / tau); // e^(-t / tau)
    PxVec3 force = (intensity / r2) * displacement.getNormalized() * timeFactor;

    return force;
}

PxVec3 Explosion::calculateForce(PxRigidDynamic* r)
{
    return PxVec3();
}

void Explosion::update(double t) {
    elapsedTime += t; // Actualiza el tiempo transcurrido
}
