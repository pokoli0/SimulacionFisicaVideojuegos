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

    // Actualizar todos los generadores
    for (auto g : gList) {
        if (g != nullptr) {
            g->update(t, *this);
        }
    }

    // Actualizar todas las partículas
    for (auto it = pList.begin(); it != pList.end(); ) {
        if (*it != nullptr) {
            // Reiniciar aceleración a cero
            (*it)->setAcceleration(PxVec3(0, 0, 0));

            // Aplicar fuerzas (como gravedad) a la aceleracion
            for (auto f : fList) {
                if (f && f->isAlive()) {
                    PxVec3 force = f->calculateForce(*it);
                    PxVec3 accel = force / (*it)->getMass();  // F = ma
                    (*it)->setAcceleration((*it)->getAcceleration() + accel);
                }
            }

            // Integrar la particula con la nueva aceleracion
            (*it)->isAlive(t, *this, Particle::SEMIEULER);
            it++;
        }
    }

    // Eliminar partículas y generadores inactivos
    for (auto p : toErase) {
        auto it = std::find(pList.begin(), pList.end(), p);
        if (it != pList.end()) {
            pList.erase(it);
            delete p;
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
    Particle p = Particle(pos, direction, PxVec3(0, 0, 0));

    p.setRatio(rat);
    p.setLifeTime(lifetime);

    if (type == UNIFORME) {
        gList.push_back(new UniformGenerator(&p, rate, range, spawnR, sp));
    }
    else { // Generador normal
        gList.push_back(new NormalGenerator(&p, rate, desv, spawnR, sp));
    }
}


void ParticleSystem::addGravity(PxVec3 g)
{
	fList.push_back(new GravityForce(g));
}

void ParticleSystem::addWind(PxVec3 windVelocity, float k1, float k2, float duration) 
{
	fList.push_back(new WindForce(windVelocity, k1, k2, duration));
}

void ParticleSystem::addTornado(PxVec3 center, float intensity, float radius, float duration) 
{
    fList.push_back(new Tornado(center, intensity, radius, duration));
}

void ParticleSystem::addExplosion(PxVec3 center, float intensity, float radius, float tau) 
{
    fList.push_back(new Explosion(center, intensity, radius, tau, pList));
}


