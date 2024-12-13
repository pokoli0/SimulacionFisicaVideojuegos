#include "BuoyantForce.h"

BuoyantForce::BuoyantForce(float h, float V, float d)
    : ForceGenerator(duration, ForceType::BUOYANT)
{
    _height = h;
    _volume = V;
    _liquid_density = d;
    _depth = 10;

    _liquid_particle = new Particle(PxVec3(0, 0, 0), PxVec3(0, 0, 0), 1, PxVec4(0, 1, 1, 1), PxBoxGeometry(10,3,10));
}

BuoyantForce::~BuoyantForce()
{
    delete _liquid_particle;
}

PxVec3 BuoyantForce::calculateForce(Particle* p)
{
    if (p == nullptr) cout << "Particula nula" << endl;

    const float h = p->getPosition().y + _depth;
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

PxVec3 BuoyantForce::calculateForce(RigidBody* r) 
{
    if (r == nullptr) return PxVec3(0, 0, 0);

    const float h = r->getBody()->getGlobalPose().p.y + _depth;
    const float h0 = _liquid_particle->getPosition().y;

    PxVec3 f(0, 0, 0);
    float immersed = 0.0f;
    if (h - h0 > _height * 0.5f) {
        immersed = 0.0f;
    }
    else if (h0 - h > _height * 0.5f) {
        immersed = 1.0f;
    }
    else {
        immersed = (h0 - h) / _height + 0.5f;
    }

    f.y = _liquid_density * _volume * immersed * 9.8f;

    return f;
}
