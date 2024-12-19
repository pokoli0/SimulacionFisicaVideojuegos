#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

#include <list>

class ParticleSystem;

using namespace physx;
using namespace std;

class RigidBody {
public:
    // Default
    RigidBody(PxPhysics* physics, PxScene* scene);
    
    // Constructor
    RigidBody(PxPhysics* physics, PxScene* scene, const PxGeometry& geometry, PxTransform transform,
        float density, PxVec3 initialVelocity, PxVec4 color);

    // Constructor con tensor de inercia
    RigidBody(PxPhysics* physics, PxScene* scene, const PxGeometry& geometry, PxTransform transform,
        float mass, PxVec3 inertiaTensor, PxVec3 initialVelocity, PxVec4 color);

    ~RigidBody();

    void isAlive(double t, ParticleSystem& system);
    bool updateLifeTime(double t);
    bool isOnRatio();

    void setLifeTime(double time) { lifeTime = time; }
    double getLifeTime() const { return lifeTime; }

    void setCenter(const PxVec3& c) { center = c; }
    void setRatio(float r) { ratio = r; }

    // Métodos para acceder al cuerpo dinámico
    PxRigidDynamic* getBody() const { return body; }

    void setColor(const PxVec4& newColor);

    std::list<RigidBody*>::iterator getIterator() const { return iterator; }
    void setIterator(list<RigidBody*>::iterator i) { iterator = i; }

    RenderItem* getRenderItem() { return renderItem; }

    bool isCooking = false;
    bool isOnFire = false;
    float cookingTime = 0.0f;

private:
    PxRigidDynamic* body = nullptr; // Actor dinámico de PhysX
    PxShape* shape = nullptr;       // Forma del actor
    RenderItem* renderItem = nullptr; // Renderización asociada

    list<RigidBody*>::iterator iterator;

    double lifeTime = -1.0; // Vida útil del sólido, -1 significa infinito
    PxVec3 center = PxVec3(0, 0, 0);         // Centro de referencia para el rango
    float ratio = 1000; // Rango alto por defecto


};

