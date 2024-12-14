#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos)
    : SpringForceGenerator(k, resting, nullptr) 
{
    otherP = new Particle(anchor_pos, PxVec3(0,0,0), 1, PxVec4(1,1,1,1), PxSphereGeometry(1), true);
}

AnchoredSpringFG::~AnchoredSpringFG() {
    delete otherP;
}
