#include "WindForce.h"

WindForce::WindForce(PxVec3 windVel, float k1, float k2, float dur)
    : windVelocity(windVel), coeffK1(k1), coeffK2(k2), ForceGenerator(dur) 
{

}

PxVec3 WindForce::calculateForce(Particle* p)
{
    if (!p) return PxVec3(0, 0, 0); // Si la partícula no existe, no hay fuerza

    PxVec3 relativeVelocity = windVelocity - p->getVelocity();
    PxVec3 force = coeffK1 * relativeVelocity;

    // Si hay un término cuadrático
    if (coeffK2 != 0.0f) {
        force += coeffK2 * relativeVelocity.magnitude() * relativeVelocity;
    }

    return force;
}

void WindForce::update(double t)
{
    if (duration > 0.0f) {
        duration -= t;
        if (duration <= 0.0f) {
            alive = false;
        }
    }
}