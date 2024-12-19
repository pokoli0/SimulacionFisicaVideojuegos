#include "Result.h"
#include "ParticleSystem.h"

Result::Result(Game* g, PxPhysics* physics, PxScene* scene)
    : Scene(physics, scene), game(g) 

{
    pSystem = new ParticleSystem();

    pSystem->addGravity(PxVec3(0, -9.8, 0));
}

void Result::update(double t)
{
    pSystem->update(t);
}

void Result::initScene() {
    // Crear el recipiente rojo
    PxRigidStatic* containerBase = physics->createRigidStatic(PxTransform({ 0, -4.4f, 0 }));
    PxShape* containerBaseShape = physics->createShape(PxBoxGeometry(10.0f, 0.5f, 10.0f), *defaultMaterial);
    containerBase->attachShape(*containerBaseShape);
    scene->addActor(*containerBase);
    renderItems.push_back(new RenderItem(containerBaseShape, containerBase, PxVec4(0.8f, 0.9f, 1.0f, 1.0f))); 

    // Bordes del recipiente
    PxRigidStatic* containerEdge1 = physics->createRigidStatic(PxTransform({ -10, -3.9f, 0 }));
    PxShape* containerEdgeShape1 = physics->createShape(PxBoxGeometry(0.5f, 2.0f, 10.0f), *defaultMaterial);
    containerEdge1->attachShape(*containerEdgeShape1);
    scene->addActor(*containerEdge1);
    renderItems.push_back(new RenderItem(containerEdgeShape1, containerEdge1, PxVec4(0.8f, 0.9f, 1.0f, 1.0f)));

    PxRigidStatic* containerEdge2 = physics->createRigidStatic(PxTransform({ 10, -3.9f, 0 }));
    PxShape* containerEdgeShape2 = physics->createShape(PxBoxGeometry(0.5f, 2.0f, 10.0f), *defaultMaterial);
    containerEdge2->attachShape(*containerEdgeShape2);
    scene->addActor(*containerEdge2);
    renderItems.push_back(new RenderItem(containerEdgeShape2, containerEdge2, PxVec4(0.8f, 0.9f, 1.0f, 1.0f)));

    PxRigidStatic* containerEdge3 = physics->createRigidStatic(PxTransform({ 0, -3.9f, -10 }));
    PxShape* containerEdgeShape3 = physics->createShape(PxBoxGeometry(10.0f, 2.0f, 0.5f), *defaultMaterial);
    containerEdge3->attachShape(*containerEdgeShape3);
    scene->addActor(*containerEdge3);
    renderItems.push_back(new RenderItem(containerEdgeShape3, containerEdge3, PxVec4(0.8f, 0.9f, 1.0f, 1.0f)));

    PxRigidStatic* containerEdge4 = physics->createRigidStatic(PxTransform({ 0, -3.9f, 10 }));
    PxShape* containerEdgeShape4 = physics->createShape(PxBoxGeometry(10.0f, 2.0f, 0.5f), *defaultMaterial);
    containerEdge4->attachShape(*containerEdgeShape4);
    scene->addActor(*containerEdge4);
    renderItems.push_back(new RenderItem(containerEdgeShape4, containerEdge4, PxVec4(0.8f, 0.9f, 1.0f, 1.0f)));

    finalGenerator.push_back(
        pSystem->addGenerator(UNIFORME,
            PxVec3(-20, 0, 30), // Posición del generador
            PxVec3(0, 0, 0),                          // Velocidad inicial
            15,                                       // Tasa de generación
            PxVec3(0, 0, 0),                          // Sin desviación inicial
            10,                                       // Rango de emisión
            3,                                        // Spawn range
            GenDistribution::UNIFORMDIST,             // Distribución uniforme
            200,                                      // Ratio
            5,                                        // Vida útil
            30,                                       // Radio vivo
            true));

    finalGenerator.push_back(
        pSystem->addGenerator(UNIFORME,
            PxVec3(20, 0, 30), // Posición del generador
            PxVec3(0, 0, 0),                          // Velocidad inicial
            15,                                       // Tasa de generación
            PxVec3(0, 0, 0),                          // Sin desviación inicial
            10,                                       // Rango de emisión
            3,                                        // Spawn range
            GenDistribution::UNIFORMDIST,             // Distribución uniforme
            200,                                      // Ratio
            5,                                        // Vida útil
            30,                                       // Radio vivo
            true));

}

void Result::clearScene()
{
    Scene::clearScene();
}

void Result::setPotatoes(const std::vector<RigidBody*>& cookedPotatoes) {
    potatoes = cookedPotatoes; // Transferir las patatas cocinadas
    for (auto p : potatoes) {
        pSystem->addRigidBody(p);
    }
}
