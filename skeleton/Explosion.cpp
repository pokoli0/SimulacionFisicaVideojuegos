#include "Explosion.h"
#include <cmath>

Explosion::Explosion(PxVec3 center, float intensity, float radius, float tau, const std::list<Particle*>& particles)
    : ForceGenerator(-1.0f, ForceType::EXPLOSION), explosionCenter(center), intensity(intensity), radius(radius), tau(tau), elapsedTime(0), affectedParticles(particles)
{}

Explosion::Explosion(PxVec3 center, float intensity, float radius, float tau, const std::list<RigidBody*>& bodies)
    : ForceGenerator(-1.0f, ForceType::EXPLOSION), explosionCenter(center), intensity(intensity), radius(radius), tau(tau), elapsedTime(0), affectedRB(bodies)
{}

Explosion::~Explosion()
{

}

PxVec3 Explosion::calculateForce(Particle* p)
{
    if (!p || std::find(affectedParticles.begin(), affectedParticles.end(), p) == affectedParticles.end()) return PxVec3(0, 0, 0);

    const PxVec3 displacement = p->getPosition() - explosionCenter;
    const float distance = displacement.magnitude();

    // Si está fuera del radio de la explosión, no hay fuerza
    if (distance > radius) return PxVec3(0, 0, 0);

    // Fuerza según la fórmula del enunciado
    const float r2 = distance * distance;
    const float timeFactor = exp(-elapsedTime / tau); // e^(-t / tau)
    const PxVec3 force = (intensity / r2) * displacement.getNormalized() * timeFactor;

    return force;
}

PxVec3 Explosion::calculateForce(RigidBody* r)
{
    if (!r || std::find(affectedRB.begin(), affectedRB.end(), r) == affectedRB.end()) return PxVec3(0, 0, 0);

    const PxVec3 displacement = r->getBody()->getGlobalPose().p - explosionCenter;
    const float distance = displacement.magnitude();

    // Si está fuera del radio de la explosión, no hay fuerza
    if (distance > radius) return PxVec3(0, 0, 0);

    // Fuerza según la fórmula del enunciado
    const float r2 = distance * distance;
    const float timeFactor = exp(-elapsedTime / tau); // e^(-t / tau)
    const PxVec3 force = (intensity / r2) * displacement.getNormalized() * timeFactor;

    return force;
}

void Explosion::update(double t) 
{
    elapsedTime += t;
}
