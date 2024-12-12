#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	
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
    for (auto f : fList) {
        delete f;
        f = nullptr;
    }
    for (auto r : rList) {
        //delete r;
        r = nullptr;
    }

	pList.clear();
	gList.clear();
    fList.clear();
    rList.clear();
}

void ParticleSystem::update(double t)
{
    pToErase.clear();
    fToErase.clear();
    gToErase.clear();
    rToErase.clear();

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
                    const PxVec3 force = f->calculateForce(*it);
                    const PxVec3 accel = force / (*it)->getMass();  // F = ma
                    (*it)->setAcceleration((*it)->getAcceleration() + accel);
                }
            }

            // Integrar la particula con la nueva aceleracion
            (*it)->isAlive(t, *this, Particle::SEMIEULER);
            it++;
        }
    }

    // Actualizar sólidos rígidos
    for (RigidBody* rb : rList) {
        if (rb) {
            rb->getBody()->clearForce(PxForceMode::eFORCE);

            for (auto f : fList) {
                if (f && f->isAlive()) {
                    const PxVec3 force = f->calculateForce(rb);
                    rb->getBody()->addForce(force);
                }
            }
        }
    }

    // Eliminar partículas y generadores inactivos
    for (auto p : pToErase) {
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

    for (auto g : gToErase) {
        auto it = std::find(gList.begin(), gList.end(), g);
        if (it != gList.end()) {
            gList.erase(it);
            delete g;
        }
    }

    for (auto r : rToErase) {
        auto it = std::find(rList.begin(), rList.end(), r);
        if (it != rList.end()) {
            rList.erase(it);
            delete r;
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
		pToErase.push_back(p);
	}
}

void ParticleSystem::addRigidBody(RigidBody* rigid) {
    rList.push_back(rigid);
    rigid->setIterator(--rList.end());
}

void ParticleSystem::destroyRigidBody(RigidBody* rigid) {
    if (rigid != nullptr && rigid->getIterator() != rList.end()) {
        rToErase.push_back(rigid);
    }
}


#pragma region Generador
void ParticleSystem::addGenerator(GeneratorType type, PxVec3 pos, PxVec3 direction, float rate, PxVec3 desv, 
    float range, float spawnR, GenDistribution sp, float rat, float lifetime)
{
    Particle p = Particle();
    p.setPosition(pos);
    p.setVelocity(direction);
    p.setAcceleration(PxVec3(0, 0, 0));

    p.setRatio(rat);
    p.setLifeTime(lifetime);

    if (type == UNIFORME) {
        gList.push_back(new UniformGenerator(&p, rate, range, spawnR, sp));
    }
    else { // Generador normal
        gList.push_back(new NormalGenerator(&p, rate, desv, spawnR, sp));
    }
}
#pragma endregion

#pragma region Fuerzas

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
void ParticleSystem::addSpring(Particle* other)
{
    fList.push_back(new SpringForceGenerator(1, 10, other));
}
void ParticleSystem::addBuoyancy(float height, float volume, float density)
{
    fList.push_back(new BuoyantForce(height, volume, density));
}
#pragma endregion

#pragma region Muelles
void ParticleSystem::generateSpringDemo()
{
    // First one standard spring uniting 2 particles
    Particle* part1 = new Particle();
    part1->setPosition(PxVec3(10, 10, 0));
    Particle* part2 = new Particle();
    part2->setPosition(PxVec3(-10, 10, 0));
    part2->setMass(2);

    addParticle(part1);
    addParticle(part2);

    SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, part2);
    fList.push_back(f1);
    SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, part1);
    fList.push_back(f2);


    // Then one spring with one fixed side

    Particle* part3 = new Particle();
    part3->setPosition(PxVec3(-10, 20, 0));
    //part3->setMass(2.0);
    addParticle(part3);

    AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 10, { 10.0, 20.0, 0.0 });
    fList.push_back(f3);
}
#pragma endregion

