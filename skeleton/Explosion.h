#pragma once

#include "ForceGenerator.h"
#include <list>

class Explosion : public ForceGenerator {
public:
    Explosion(PxVec3 center, float intensity, float radius, float tau, const std::list<Particle*>& particles);
    Explosion(PxVec3 center, float intensity, float radius, float tau, const std::list<RigidBody*>& bodies);
    ~Explosion();

    PxVec3 calculateForce(Particle* p) override;
    PxVec3 calculateForce(RigidBody* r) override;

    void update(double t) override;

private:
    PxVec3 explosionCenter;       // Centro de la explosión
    float intensity;              // Intensidad de la explosión
    float radius;                 // Radio máximo de la explosión
    float tau;                    // Constante de tiempo
    float elapsedTime;            // Tiempo transcurrido desde que empezó la explosión

    std::list<Particle*> affectedParticles; // Partículas afectadas por la explosión
    std::list<RigidBody*> affectedRB; //RB afectados
};
