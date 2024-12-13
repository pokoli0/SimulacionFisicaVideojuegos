#include "Tornado.h"

Tornado::Tornado(PxVec3 center, float intensity, float radius, float duration)
    : WindForce(PxVec3(0, 0, 0), intensity, 0.0f, duration), center(center), K(intensity), radius(radius) 
{

}

PxVec3 Tornado::calculateForce(Particle* p)
{
    // Posici�n de la part�cula
    const PxVec3 pos = p->getPosition();

    // F�rmula del torbellino
    const PxVec3 force = K * PxVec3(
        - (pos.z - center.z),       // - (z - z_c)
        15 - (pos.y - center.y),     // 50 - (y - y_c)
        pos.x - center.x           // (x - x_c)
    );

    return force;
}

PxVec3 Tornado::calculateForce(RigidBody* rigid) 
{
    if (!rigid) return PxVec3(0, 0, 0);

    // Posici�n del s�lido r�gido
    const PxVec3 pos = rigid->getBody()->getGlobalPose().p;

    // F�rmula del torbellino para s�lidos r�gidos
    const PxVec3 force = K * PxVec3(
        -(pos.z - center.z),
        15 - (pos.y - center.y),
        pos.x - center.x
    );

    return force;
}
