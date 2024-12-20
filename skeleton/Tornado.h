#pragma once

#include "WindForce.h"

class Tornado : public WindForce {
public:
    Tornado(PxVec3 center, float intensity, float radius = 50.0f, float duration = -1.0f);

    PxVec3 calculateForce(Particle* p) override;
    PxVec3 calculateForce(RigidBody* rigid) override;

private:
    PxVec3 center;  // Centro del torbellino
    float K;        // Intensidad del torbellino
    float radius;   // Radio
};
