#include "Tornado.h"

Tornado::Tornado(PxVec3 center, float intensity, float radius, float duration)
    : WindForce(PxVec3(0, 0, 0), intensity, 0.0f, duration), center(center), K(intensity), radius(radius) 
{

}

PxVec3 Tornado::calculateForce(Particle* p)
{
    PxVec3 particlePos = p->getPosition();

    // distancia de la partícula al centro del torbellino
    PxVec3 direction = particlePos - center;

    float distance = direction.magnitude();

    // velocidad tangencial (perpendicular al radio)
    direction.normalize();

    // velocidad tangencial en torno al centro del torbellino
    PxVec3 tornadoVelocity = PxVec3(
        -(direction.y * K) / (distance + 1e-3f),
        direction.x * K / (distance + 1e-3f),
        0
    );

    return tornadoVelocity;
}