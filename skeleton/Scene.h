#pragma once
#include <vector>
#include "RigidBody.h"
#include "ForceGenerator.h"

class Scene {
public:
    Scene(PxPhysics* physics, PxScene* scene);
    virtual ~Scene();

    virtual void initScene(); // Inicializaci�n espec�fica de la escena
    virtual void update(double t); // Actualizaci�n l�gica
    virtual void keyPressed(unsigned char key, const PxTransform& camera);



protected:
    std::vector<RigidBody*> rigidBodies; // S�lidos r�gidos en la escena
    std::vector<ForceGenerator*> forces; // Fuerzas aplicadas

    PxPhysics* physics;
    PxScene* scene;
};
