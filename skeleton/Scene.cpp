#include "Scene.h"

Scene::Scene(PxPhysics* physics, PxScene* scene)
    : physics(physics), scene(scene) {}

Scene::~Scene() {
    for (auto rb : rigidBodies) {
        delete rb;
    }
    for (auto f : forces) {
        delete f;
    }
}

void Scene::initScene()
{
}

void Scene::update(double t) 
{
    for (RigidBody* rb : rigidBodies) {
        if (rb && rb->getBody()) {
            rb->getBody()->clearForce(PxForceMode::eFORCE);

            for (ForceGenerator* force : forces) {
                if (force && force->isAlive()) {
                    PxVec3 forceVec = force->calculateForce(rb);
                    rb->getBody()->addForce(forceVec);
                }
            }
        }
    }
}

void Scene::keyPressed(unsigned char key, const PxTransform& camera)
{
}

void Scene::clearScene()
{

    // Limpiar fuerzas
    for (ForceGenerator* force : forces) {
        delete force;
    }
    forces.clear();


}
