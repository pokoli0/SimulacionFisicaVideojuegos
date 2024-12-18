#pragma once
#include <vector>
#include "RigidBody.h"
#include "ForceGenerator.h"

class Scene {
public:
    Scene(PxPhysics* physics, PxScene* scene);
    virtual ~Scene();

    virtual void initScene(); // Inicialización específica de la escena
    virtual void update(double t); // Actualización lógica
    virtual void keyPressed(unsigned char key, const PxTransform& camera);



protected:
    std::vector<RigidBody*> rigidBodies; // Sólidos rígidos en la escena
    std::vector<ForceGenerator*> forces; // Fuerzas aplicadas

    PxPhysics* physics;
    PxScene* scene;
};
