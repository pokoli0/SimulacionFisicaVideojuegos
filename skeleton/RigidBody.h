#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

using namespace physx;

class RigidBody {
public:
    // Constructor
    RigidBody(PxPhysics* physics, PxScene* scene, const PxGeometry& geometry, PxTransform transform,
        float density, PxVec3 initialVelocity, PxVec4 color);

    ~RigidBody();

    // M�todos para acceder al cuerpo din�mico
    PxRigidDynamic* getBody() const { return body; }

private:
    PxRigidDynamic* body = nullptr; // Actor din�mico de PhysX
    PxShape* shape = nullptr;       // Forma del actor
    RenderItem* renderItem = nullptr; // Renderizaci�n asociada

};

