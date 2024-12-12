#pragma once

#include "ForceGenerator.h"

class WindForce : public ForceGenerator {
public:
    WindForce(PxVec3 windVel, float k1, float k2 = 0.0f, float dur = -1.0f);

    ~WindForce() {}

    PxVec3 calculateForce(Particle* p) override;
    PxVec3 calculateForce(RigidBody* r) override;

    void update(double t) override;

protected:
    PxVec3 windVelocity;  // Velocidad del viento
    float coeffK1;        // Coeficiente lineal
    float coeffK2;        // Coeficiente cuadrático
};
