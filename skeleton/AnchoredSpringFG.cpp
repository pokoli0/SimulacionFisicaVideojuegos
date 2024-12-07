#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos)
    : SpringForceGenerator(k, resting, nullptr) 
{
    other = new Particle(anchor_pos, PxVec3(0,0,0), 1, PxVec4(1,1,1,1));
}

AnchoredSpringFG::~AnchoredSpringFG() {
    delete other;
}
