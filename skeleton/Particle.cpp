#include "Particle.h"

Particle::Particle(physx::PxVec3 pos, physx::PxVec3 velo, physx::PxVec3 accele) : pose(pos), vel(velo), accel(accele)
{
	damping = 0.99;

	physx::PxSphereGeometry sphere(1);
	physx::PxShape* shape = CreateShape(sphere);
	transform = new physx::PxTransform(pose);

	renderItem = new RenderItem(shape, transform, Vector4(1, 0.5, 1, 1));

	RegisterRenderItem(renderItem);
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
	delete renderItem;
	delete transform;
}

void Particle::Integrate(double t)
{
	vel = vel * pow(damping, t) + accel * t;
	vel = vel * pow(damping, t) + accel * t;

	pose = pose + vel * t;

	transform->p = transform->p + vel * t;
}