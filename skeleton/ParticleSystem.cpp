#include "ParticleSystem.h"
#include <cstdlib> // Para rand y srand
#include <ctime>   // Para inicializar la semilla de n�meros aleatorios

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
        delete r;
        r = nullptr;
    }

	pList.clear();
	gList.clear();
    fList.clear();
    rList.clear();
}

void ParticleSystem::update(double t)
{
    // Eliminar part�culas y generadores inactivos
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

    for (auto r : rToErase) {
        auto it = std::find(rList.begin(), rList.end(), r);
        if (it != rList.end()) {
            rList.erase(it);
            delete r;
        }
    }

    for (auto g : gToErase) {
        auto it = std::find(gList.begin(), gList.end(), g);
        if (it != gList.end()) {
            gList.erase(it);
            delete g;
        }
    }

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

    // Actualizar todas las part�culas
    for (auto it = pList.begin(); it != pList.end(); ) {
        if (*it != nullptr) {
            // Reiniciar aceleraci�n a cero
            (*it)->setAcceleration(PxVec3(0, 0, 0));

            // Aplicar fuerzas
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

    // Actualizar s�lidos r�gidos
    for (auto it = rList.begin(); it != rList.end(); ) {
        if (*it) {
            (*it)->getBody()->clearForce(PxForceMode::eFORCE);

            // Aplicar fuerzas
            for (auto f : fList) {
                if (f && f->isAlive()) {
                    PxVec3 force = f->calculateForce(*it);
                    (*it)->getBody()->addForce(force);
                }
            }

            (*it)->isAlive(t, *this);
            ++it;
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

void ParticleSystem::removeRigidBody(RigidBody* r)
{
    auto it = std::find(rList.begin(), rList.end(), r);
    if (it != rList.end()) {
        rList.erase(it);
    }
}


#pragma region Generador
ParticleGenerator* ParticleSystem::addGenerator(GeneratorType type, PxVec3 pos, PxVec3 direction, float rate, PxVec3 desv,
    float range, float spawnR, GenDistribution sp, float rat, float pRatio, float lifetime, bool fire)
{
    Particle p = Particle();
    p.setPosition(pos);
    p.setVelocity(direction);
    p.setAcceleration(PxVec3(0, 0, 0));

    p.setRatio(rat);
    p.setLifeTime(lifetime);

    ParticleGenerator* newGen = nullptr;
    if (type == UNIFORME) {
        newGen = new UniformGenerator(&p, rate, range, spawnR, sp, fire);
    }
    else { // Generador normal
        newGen = new NormalGenerator(&p, rate, desv, spawnR, sp, pRatio, fire);
    }

    gList.push_back(newGen);
    newGen->setIterator(--gList.end());

    return newGen;
}

void ParticleSystem::destroyGenerator(ParticleGenerator* gen)
{
    if (gen != nullptr && gen->getIterator() != gList.end()) {
        gToErase.push_back(gen);
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

void ParticleSystem::toggleWind()
{
    if (windActive) {
        removeForce(ForceType::WIND);
        windActive = false;
        windForce = nullptr;
    }
    else {
        windForce = new WindForce(PxVec3(0, 0, 30), 0.5f, 0.1f, -1.0f); // Viento hacia la derecha
        fList.push_back(windForce);
        windActive = true;
    }
}

void ParticleSystem::removeForce(ForceType type) {
    for (auto it = fList.begin(); it != fList.end(); ++it) {
        if ((*it)->getForceType() == type) {
            delete* it;
            fList.erase(it);
            break;
        }
    }
}
#pragma endregion

#pragma region Muelles
void ParticleSystem::generateParticleSpringDemo()
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
void ParticleSystem::generateRBSpringDemo(PxPhysics* physics, PxScene* sc)
{
    RigidBody* part1 = new RigidBody(physics, sc);
    part1->getBody()->setGlobalPose(PxTransform(PxVec3(10, 10, 0)));
    RigidBody* part2 = new RigidBody(physics, sc);
    part2->getBody()->setGlobalPose(PxTransform(PxVec3(-10, 10, 0)));
    part2->getBody()->setMass(2);

    addRigidBody(part1);
    addRigidBody(part2);

    //SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, part2);
    //fList.push_back(f1);
    //SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, part1);
    //fList.push_back(f2);


    //// Then one spring with one fixed side

    //RigidBody* part3 = new RigidBody();
    //part3->setPosition(PxVec3(-10, 20, 0));
    ////part3->setMass(2.0);
    //addRigidBody(part3);

    //AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 10, { 10.0, 20.0, 0.0 });
    //fList.push_back(f3);
}

RigidBody* ParticleSystem::generateFloatingPotato(PxPhysics* physics, PxScene* sc)
{
    // Dimensiones de la sart�n
    const float panWidth = 15;  // Ancho total de la sart�n
    const float panDepth = 15;  // Profundidad total de la sart�n
    const float panHeight = 5.0f;  // Altura base donde flotan las patatas

    // Generar posici�n aleatoria dentro de la sart�n
    const float x = (static_cast<float>(rand()) / RAND_MAX) * panWidth - (panWidth / 2);
    const float z = (static_cast<float>(rand()) / RAND_MAX) * panDepth - (panDepth / 2);
    const PxVec3 position(x, panHeight, z); // Posici�n de la patata

    // Color fijo para la patata (amarillo claro)
    const PxVec4 color(1, 1, 0, 1);

    // Tama�o fijo de las patatas
    const PxBoxGeometry geometry(2.0f, 0.5f, 0.5f);

    RigidBody* r = new RigidBody(physics, sc, geometry, PxTransform(position), 1500, PxVec3(0, 0, 0), color);

    // A�adir al sistema de flotaci�n
    addRigidBody(r);
    addBuoyancy(10, 10, 1000);

    return r;
}

#pragma endregion

