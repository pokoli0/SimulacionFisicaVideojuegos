#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

#include <list>

//class ParticleSystem;

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

    // M�todos para acceder al cuerpo din�mico
    PxRigidDynamic* getBody() const { return body; }

    void setColor(const PxVec4& newColor);

    std::list<RigidBody*>::iterator getIterator() const { return iterator; }
    void setIterator(list<RigidBody*>::iterator i) { iterator = i; }


    float cookingTime = 0.0f; // Tiempo acumulado para la cocci�n
    bool isCooking = false;   // Si est� en el proceso de cocci�n

private:
    PxRigidDynamic* body = nullptr; // Actor din�mico de PhysX
    PxShape* shape = nullptr;       // Forma del actor
    RenderItem* renderItem = nullptr; // Renderizaci�n asociada

    list<RigidBody*>::iterator iterator;




};

