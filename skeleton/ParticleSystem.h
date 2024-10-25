#pragma once
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <cmath>
#include <list>
#include <iostream>

#include "Particle.h"
#include "ParticleGenerator.h"
#include "UniformGenerator.h"
#include "NormalGenerator.h"


using namespace physx;
using namespace std;

class Particle;
class ParticleGenerator;

enum GeneratorType {
	UNIFORME,
	NORMAL
};

class ParticleSystem
{
public:
	ParticleSystem() {};
	ParticleSystem(PxVec3 em);
	~ParticleSystem();

	void update(double t);
	void addParticle(Particle* p);
	void destroyParticle(Particle* p);

	void addGenerator(GeneratorType type, PxVec3 pos, PxVec3 direction, float rate, PxVec3 desv, 
		float range, float spawnR, GenDistribution sp, float rat, float lifetime = 10.0f);

	// getters & setters
	double getParticleLifeTime(Particle* p) { return p->getLifeTime(); }


private:
	list<Particle*> pList;
	vector<ParticleGenerator*> gList; // cambiar a list si se quiere borrar generadores de forma dinamica
	vector<Particle*> toErase;

	// posicion desde la cual se emiten las particulas
	PxVec3 emisor; 

	PxVec3 dir;

	vector<Particle*> particles;
	
};

