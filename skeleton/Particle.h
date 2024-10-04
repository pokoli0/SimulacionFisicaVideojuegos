#pragma once

#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <cmath>


class Particle
{
public:
	Particle(physx::PxVec3 pos, physx::PxVec3 velo, physx::PxVec3 accele);
	~Particle();

	void Integrate(double t);

private:
	physx::PxVec3 vel;
	physx::PxVec3 accel;
	physx::PxVec3 pose;

	physx::PxTransform* transform = nullptr;

	double damping;

	RenderItem* renderItem = nullptr;
};
