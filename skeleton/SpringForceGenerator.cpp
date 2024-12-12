#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double kCoeff, double _restingLength, Particle* _other)
{
	K = kCoeff;
	restingLength = _restingLength;
	otherP = _other;
}

PxVec3 SpringForceGenerator::calculateForce(Particle* particle)
{
	PxVec3 relative_pos_vector = otherP->getPosition() - particle->getPosition();
	PxVec3 force;

	const float length = relative_pos_vector.normalize();
	const float deltaX = length - restingLength;

	force = relative_pos_vector * deltaX * K;

	return force;
}

PxVec3 SpringForceGenerator::calculateForce(RigidBody* r)
{
	PxVec3 relative_pos_vector = otherP->getPosition() - r->getBody()->getGlobalPose().p;
	PxVec3 force;

	const float length = relative_pos_vector.normalize();
	const float deltaX = length - restingLength;

	force = relative_pos_vector * deltaX * K;

	return force;
}
