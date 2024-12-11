#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;

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

    // Métodos para acceder al cuerpo dinámico
    PxRigidDynamic* getBody() const { return body; }

private:
    PxRigidDynamic* body = nullptr; // Actor dinámico de PhysX
    PxShape* shape = nullptr;       // Forma del actor
    RenderItem* renderItem = nullptr; // Renderización asociada

};

