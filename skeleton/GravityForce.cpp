#include "GravityForce.h"

GravityForce::GravityForce(PxVec3 g, float dur)
	: gAcceleration(g), ForceGenerator(dur)
{
	duration = dur;
	gAcceleration = PxVec3(0, -9.8f, 0); // def

	if (g != gAcceleration) {
		gAcceleration = g;
	}
}

GravityForce::~GravityForce()
{

}

PxVec3 GravityForce::calculateForce(Particle* p)
{
	return p->getMass() * gAcceleration;
}

PxVec3 GravityForce::calculateForce(RigidBody* p)
{
	return p->getBody()->getMass() * gAcceleration;
}

void GravityForce::update(double t)
{
	if (duration > 0.0f) {
		duration -= t;
		if (duration <= 0.0f) {
			alive = false; // Desactiva la fuerza cuando se agote la duración
		}
	}
}
