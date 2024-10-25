#include "Particle.h"
#include <math.h>
#include <iostream>
#include "ParticleSystem.h"

Particle::Particle(PxVec3 pos, PxVec3 velo, PxVec3 accele) : pose(pos), vel(velo), accel(accele)
{
	damping = 0.99;
	pose = physx::PxTransform(pos);
	
	accel = Vector3(0, 0, 0);
	lifeTime = 0.0;

	vel = velo;
	accel = accele;

	alive = true;

	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, &pose, PxVec4(0,0,0,1));

	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	//delete renderItem;
	//renderItem = nullptr;
}

void Particle::Integrate(double t, IntegrationType type)
{
	if (type == EULER) {
		vel = vel + accel * t;
		vel = vel * pow(damping, t);
		pose.p = pose.p + vel * t;
	}
	else { // semieuler
		pose.p = pose.p + vel * t;
		vel = vel + accel * t;
		vel = vel * pow(damping, t);
	}
}

void Particle::isAlive(double t, ParticleSystem& system, IntegrationType type)
{
	timeAlive += t;
	Integrate(t, type);
	if (timeAlive > lifeTime || !isOnRatio()) { // ver donde se modifica lifetime
		system.destroyParticle(this);
		alive = false;
	}
}

bool Particle::isOnRatio()
{
	return (pose.p - center).magnitude() < ratio;
}
