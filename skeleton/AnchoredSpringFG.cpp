#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos)
    : SpringForceGenerator(k, resting, nullptr) 
{
    Particle p1;
    Particle* part1 = new Particle(p1);
    part1->setPosition({ 0,0,0 });
    part1->setMass(1.0);
    part1->setColor(PxVec4(1,1,1,1));

    //addParticle(part1);
    other = part1;
}

AnchoredSpringFG::~AnchoredSpringFG() {
    delete other;
}
