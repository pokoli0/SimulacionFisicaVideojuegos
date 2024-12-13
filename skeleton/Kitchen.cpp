#include "Kitchen.h"

Kitchen::Kitchen(PxPhysics* physics, PxScene* scene)
    : Scene(physics, scene)
{

}

Kitchen::~Kitchen()
{
    for (auto rb : renderItems) {
        delete rb;
    }
}

void Kitchen::initScene()
{
    if (!defaultMaterial) {
        throw std::runtime_error("Default material no inicializado.");
    }

    // Crear el plano para la encimera (marrón)
    PxRigidStatic* countertop = physics->createRigidStatic(PxTransform({ 0, -5, 0 }));
    PxShape* countertopShape = physics->createShape(PxBoxGeometry(50, 0.5, 50), *defaultMaterial);
    countertop->attachShape(*countertopShape);
    scene->addActor(*countertop);
    renderItems.push_back(new RenderItem(countertopShape, countertop, PxVec4(0.3f, 0.4f, 0.9f, 1.0f)));

    // Crear el plano para la vitrocerámica (negro clarito)
    PxRigidStatic* stovetop = physics->createRigidStatic(PxTransform({ 0, -4.9, 0 }));
    PxShape* stovetopShape = physics->createShape(PxBoxGeometry(30, 0.5, 30), *defaultMaterial);
    stovetop->attachShape(*stovetopShape);
    scene->addActor(*stovetop);
    renderItems.push_back(new RenderItem(stovetopShape, stovetop, PxVec4(0.1, 0.1, 0.1, 1.0f)));

    // Sarten
    createPan();

    // Camara
    setupCamera();
}

void Kitchen::createPan()
{
    // Crear la sartén (cuerpo cuadrado)
    PxRigidStatic* panBase = physics->createRigidStatic(PxTransform({ 0, -4.4, 0 }));
    PxShape* panBaseShape = physics->createShape(PxBoxGeometry(10, 1, 10), *defaultMaterial);
    panBase->attachShape(*panBaseShape);
    scene->addActor(*panBase);
    renderItems.push_back(new RenderItem(panBaseShape, panBase, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    // Bordes de la sartén
    PxRigidStatic* panEdge1 = physics->createRigidStatic(PxTransform({ -10, -2.4, 0 }));
    PxShape* panEdgeShape1 = physics->createShape(PxBoxGeometry(0.5, 3, 10), *defaultMaterial);
    panEdge1->attachShape(*panEdgeShape1);
    scene->addActor(*panEdge1);
    renderItems.push_back(new RenderItem(panEdgeShape1, panEdge1, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    PxRigidStatic* panEdge2 = physics->createRigidStatic(PxTransform({ 10, -2.4, 0 }));
    PxShape* panEdgeShape2 = physics->createShape(PxBoxGeometry(0.5, 3, 10), *defaultMaterial);
    panEdge2->attachShape(*panEdgeShape2);
    scene->addActor(*panEdge2);
    renderItems.push_back(new RenderItem(panEdgeShape2, panEdge2, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    PxRigidStatic* panEdge3 = physics->createRigidStatic(PxTransform({ 0, -2.4, -10 }));
    PxShape* panEdgeShape3 = physics->createShape(PxBoxGeometry(10, 3, 0.5), *defaultMaterial);
    panEdge3->attachShape(*panEdgeShape3);
    scene->addActor(*panEdge3);
    renderItems.push_back(new RenderItem(panEdgeShape3, panEdge3, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    PxRigidStatic* panEdge4 = physics->createRigidStatic(PxTransform({ 0, -2.4, 10 }));
    PxShape* panEdgeShape4 = physics->createShape(PxBoxGeometry(10, 3, 0.5), *defaultMaterial);
    panEdge4->attachShape(*panEdgeShape4);
    scene->addActor(*panEdge4);
    renderItems.push_back(new RenderItem(panEdgeShape4, panEdge4, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    // Mango de la sartén
    PxRigidStatic* panHandle = physics->createRigidStatic(PxTransform({ 0, -3, -15 }));
    PxShape* panHandleShape = physics->createShape(PxBoxGeometry(1, 1, 5), *defaultMaterial);
    panHandle->attachShape(*panHandleShape);
    scene->addActor(*panHandle);
    renderItems.push_back(new RenderItem(panHandleShape, panHandle, PxVec4(0.0f, 0.0f, 0.0f, 1.0f)));

}

void Kitchen::setupCamera()
{
    if (!GetCamera()) {
        throw std::runtime_error("Camara no inicializada.");
    }

    const PxVec3 eye(0.0f, 30.0f, -30.0f); // Posicion
    const PxVec3 dir(0.0f, -1.0f, 1.0f);   // Direccion

    Snippets::Camera* camera = GetCamera();
    *camera = Snippets::Camera(eye, dir);
}