#pragma once
#include "RenderUtils.hpp"
#include <list>

class ParticleSystem;

using namespace std;
using namespace physx;

class Particle
{
public:
	enum IntegrationType {
		EULER,
		SEMIEULER
	};

	Particle();
	Particle(PxVec3 pos, PxVec3 velo, double m, PxVec4 col);
	Particle(Particle const& p); // Para el sistema de particulas
	~Particle();


	void Integrate(double t, IntegrationType type);
	void isAlive(double t, ParticleSystem& system, IntegrationType type);

	bool isOnRatio();
	bool updateLifeTime(double t);

	// getters & setters
	double getLifeTime() const { return lifeTime; }
	void setLifeTime(double t) { lifeTime = t; }

	list<Particle*>::iterator getIterator() const { return iterator; }
	void setIterator(list<Particle*>::iterator i) { iterator = i; }

	void setPosition(PxVec3 p) { transform.p = p; }
	PxVec3 getPosition() { return transform.p; }

	void setVelocity(PxVec3 v) { vel = v; }
	PxVec3 getVelocity() const { return vel; }

	void setAcceleration(PxVec3 a) { accel = a; }
	PxVec3 getAcceleration() const { return accel; }

	void setRatio(float r) { ratio = r; }

	double getMass() { return mass; }
	void setMass(double m) { mass = m; }

	void setColor(PxVec4 c) { color = c; }
	PxVec4 getColor() { return color; }

protected:
	list<Particle*>::iterator iterator;

	PxVec3 vel;
	PxVec3 accel;
	PxTransform transform; // posicion

	double damping;

	RenderItem* renderItem = nullptr;

	double mass;

	double lifeTime;

	PxVec4 color;

	PxVec3 center;
	float ratio;
};
