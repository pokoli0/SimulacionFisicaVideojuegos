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

	Particle(PxVec3 pos, PxVec3 velo, PxVec3 accele);
	~Particle();

	void Integrate(double t, IntegrationType type);
	bool isAlive(double t, ParticleSystem& system);

	bool isOnRatio();

	// getters & setters
	double getLifeTime() const { return lifeTime; }
	void setLifeTime(double t) { lifeTime = t; }
	list<Particle*>::iterator getIterator() const { return iterator; }
	void setIterator(list<Particle*>::iterator i) { iterator = i; }

	PxVec3 getPosition() const { return pose; }
	void setPosition(PxVec3 p) { pose = p; }
	void setVelocity(PxVec3 v) { vel = v; }
	PxVec3 getVelocity() const { return vel; }
	void setAcceleration(PxVec3 a) { accel = a; }

	void setRatio(float r) { ratio = r; }

protected:
	list<Particle*>::iterator iterator;

	PxVec3 vel;
	PxVec3 accel;
	PxVec3 pose;

	PxTransform poseT;

	PxTransform* transform = nullptr;

	double damping;

	RenderItem* renderItem = nullptr;

	double mass;

	double lifeTime;
	double timeAlive;

	bool alive;

	PxVec3 center;
	float ratio;
};
