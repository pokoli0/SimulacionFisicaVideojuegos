#pragma once
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <cmath>
#include <list>
#include <iostream>

#include "Particle.h"
#include "RigidBody.h"

#include "ParticleGenerator.h"
#include "UniformGenerator.h"
#include "NormalGenerator.h"

#include "ForceGenerator.h"
#include "GravityForce.h"
#include "WindForce.h"
#include "Tornado.h"
#include "Explosion.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "BuoyantForce.h"



using namespace physx;
using namespace std;

class Particle;
class RigidBody;
class ParticleGenerator;

enum GeneratorType {
	UNIFORME,
	NORMAL
};

class ParticleSystem
{
public:
	ParticleSystem();

	~ParticleSystem();

	void update(double t);

	void addParticle(Particle* p);
	void destroyParticle(Particle* p);

	void addRigidBody(RigidBody* rigid);
	void destroyRigidBody(RigidBody* rigid);
	void removeRigidBody(RigidBody* r); // para que no se le apliquen las fuerzas


	ParticleGenerator* addGenerator(GeneratorType type, PxVec3 pos, PxVec3 direction, float rate, PxVec3 desv, 
		float range, float spawnR, GenDistribution sp, float rat, float pRatio, float lifetime, bool fire);
	void destroyGenerator(ParticleGenerator* gen);

	void addGravity(PxVec3 g);
	void addWind(PxVec3 windVelocity, float k1, float k2 = 0.0f, float duration = -1.0f);
	void addTornado(PxVec3 center, float intensity, float radius, float duration);
	void addExplosion(PxVec3 center, float intensity, float radius, float tau);

	void addSpring(Particle* other);
	void addBuoyancy(float height, float volume, float density);

	void toggleWind();

	void removeForce(ForceType type);

	// muelles
	void generateParticleSpringDemo();
	void generateRBSpringDemo(PxPhysics* physics, PxScene* sc);

	// juego
	RigidBody* generateFloatingPotato(PxPhysics* physics, PxScene* sc);

	// getters & setters
	double getParticleLifeTime(Particle* p) { return p->getLifeTime(); }


private:

	list<Particle*> pList;
	vector<Particle*> pToErase;

	list<ParticleGenerator*> gList;
	vector<ParticleGenerator*> gToErase;

	// Fuerzas
	list<ForceGenerator*> fList;
	vector<ForceGenerator*> fToErase;

	// Solidos
	list<RigidBody*> rList;
	vector<RigidBody*> rToErase;

	bool windActive = false;
	WindForce* windForce = nullptr;
};

