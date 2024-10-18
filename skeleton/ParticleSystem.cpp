#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(PxVec3 em)
{
	emisor = em;

	dir = PxVec3(2, 0, 0);
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update(double t)
{
	Particle* particles = new Particle(emisor, dir, PxVec3(0, -5, 0));

	if (particles->getLifeTime() >= t) {
		destroyParticle(particles);
	}
}

void ParticleSystem::destroyParticle(Particle* p)
{
}
