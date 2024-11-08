#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	dir = PxVec3(0, 5, 0); // default
	
}

ParticleSystem::ParticleSystem(PxVec3 em)
{
	emisor = em;
}

ParticleSystem::~ParticleSystem()
{
	for (auto p : pList) {
		delete p;
		p = nullptr;
	}
	for (auto g : gList) {
		delete g;
		g = nullptr;
	}

	pList.clear();
	gList.clear();
}

void ParticleSystem::update(double t)
{
	toErase.clear();
	fToErase.clear();

	for (auto g : gList) {
		if (g != nullptr) {
			g->update(t, *this);
		}
	}

	for (auto it = pList.begin(); it != pList.end(); ) {
		if (*it != nullptr) {
			(*it)->isAlive(t, *this, Particle::SEMIEULER);
			it++;
		}
	}

	for (auto p : toErase) {
		auto it = std::find(pList.begin(), pList.end(), p);
		if (it != pList.end()) {
			pList.erase(it);
			delete p;
		}
	}

	// Fuerzas
	for (auto f : fList) {
		if (f) {
			f->update(t);
		}
	}
	for (auto f : fToErase) {
		auto it = std::find(fList.begin(), fList.end(), f);
		if (it != fList.end()) {
			fList.erase(it);
			delete f;
		}
	}
}

void ParticleSystem::addParticle(Particle* p)
{
	pList.push_back(p);
	p->setIterator(--pList.end());
}

void ParticleSystem::destroyParticle(Particle* p)
{
	if (p != nullptr && p->getIterator() != pList.end()) {
		toErase.push_back(p);
	}
}

void ParticleSystem::addGenerator(GeneratorType type, PxVec3 pos, PxVec3 direction, float rate, PxVec3 desv, 
	float range, float spawnR, GenDistribution sp, float rat, float lifetime)
{
	Particle p = Particle(pos, direction, PxVec3(0, -9.8, 0));

	p.setRatio(rat);
	p.setLifeTime(lifetime);

	if (type == UNIFORME) {
		gList.push_back(new UniformGenerator(&p, rate, range, spawnR, sp));
	}
	else { //normal
		gList.push_back(new NormalGenerator(&p, rate, desv, spawnR, sp));
	}
}

void ParticleSystem::addGravity(PxVec3 g)
{
	fList.push_back(new GravityForce(g));
	cout << "gravity " << endl;
}
