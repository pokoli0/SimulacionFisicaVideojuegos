#include "Particle.h"
#include <math.h>
#include <iostream>
#include "ParticleSystem.h"

Particle::Particle(PxVec3 pos, PxVec3 velo, PxVec3 accele) : pose(pos), vel(velo), accel(accele)
{
	damping = 0.99;

	PxSphereGeometry sphere(1);
	PxShape* shape = CreateShape(sphere);
	transform = new PxTransform(pose);

	renderItem = new RenderItem(shape, transform, Vector4(1, 0.5, 1, 1));

	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete transform;
}

void Particle::Integrate(double t, IntegrationType type)
{
	if (type == EULER) {
		vel = vel + accel * t;
		vel = vel * pow(damping, t);
		pose = pose + vel * t;
	}
	else { // semieuler
		pose = pose + vel * t;
		vel = vel + accel * t;
		vel = vel * pow(damping, t);
	}
}

bool Particle::isAlive(double t, ParticleSystem& system)
{
	alive = true;
	timeAlive += t;
	if (timeAlive > lifeTime || !isOnRatio()) {
		system.destroyParticle(this);
		alive = false;
	}
	return alive;
}

bool Particle::isOnRatio()
{
	return (pose - center).magnitude() < ratio;
}
