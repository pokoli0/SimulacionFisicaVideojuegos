#pragma once
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <cmath>
#include <list>
#include <iostream>

#include "Particle.h"

using namespace physx;
using namespace std;

class ParticleSystem
{
public:
	ParticleSystem() {};
	ParticleSystem(PxVec3 em);
	~ParticleSystem();

	void update(double t);
	void destroyParticle(Particle* p);

private:
	// posicion desde la cual se emiten las particulas
	PxVec3 emisor; 

	PxVec3 dir;

	vector<Particle*> particles;
	
};

