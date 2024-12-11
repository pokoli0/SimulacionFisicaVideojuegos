#include "BuoyantForce.h"

BuoyantForce::BuoyantForce(float h, float V, float d)
{
    _height = h;
    _volume = V;
    _liquid_density = d;

    _liquid_particle = new Particle(PxVec3(0, 0, 0), PxVec3(0, 0, 0), 1, PxVec4(0, 1, 1, 1));
}

PxVec3 BuoyantForce::calculateForce(Particle* p)
{
    if (p == nullptr) cout << "Particula nula" << endl;

    const float h = p->getPosition().y;
    const float h0 = _liquid_particle->getPosition().y;

    Vector3 f(0, 0, 0);
    float immersed = 0.0;
    if (h - h0 > _height * 0.5) {
        immersed = 0.0;
    }
    else if (h0 - h > _height * 0.5) {
        // Totally immersed
        immersed = 1.0;
    }
    else {
        immersed = (h0 - h) / _height + 0.5;
    }

    f.y = _liquid_density * _volume * immersed * 9.8;

	return f;
}

PxVec3 BuoyantForce::calculateForce(PxRigidDynamic* r)
{
    return PxVec3();
}
