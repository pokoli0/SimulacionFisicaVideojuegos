#include "RigidBody.h"
#include <iostream>

RigidBody::RigidBody(PxPhysics* physics, PxScene* scene)
{
    body = physics->createRigidDynamic(PxTransform(0,0,0));
    
    body->setLinearVelocity(PxVec3(0,0,0));
    body->setAngularVelocity(PxVec3(0, 0, 0));

    //// Dimensiones del cuboide
    float a = 5.0f; // Largo
    float b = 1.0f; // Ancho
    float c = 1.0f; // Altura

    // Asociar forma
    PxShape* sh = CreateShape(PxBoxGeometry(a,b,c)); // Cubo por defecto
    body->attachShape(*sh);

    // Masa y tensor de inercia
    PxRigidBodyExt::updateMassAndInertia(*body, 0.15f);

    scene->addActor(*body);

    renderItem = new RenderItem(sh, body, PxVec4(0.5, 0.5, 0, 1));
}

RigidBody::RigidBody(PxPhysics* physics, PxScene* scene, const PxGeometry& geometry, PxTransform transform, float density, PxVec3 initialVelocity, PxVec4 color)
{
    // Creacion del solido
    body = physics->createRigidDynamic(transform);

    body->setLinearVelocity(initialVelocity);
    body->setAngularVelocity(PxVec3(0, 0, 0));

    // Asociar forma
    PxShape* sh = CreateShape(geometry);
    body->attachShape(*sh);

    // Masa y tensor de inercia
    PxRigidBodyExt::updateMassAndInertia(*body, density);

    // Para que le afecten las fisicas de la escena e interactue con otros solidos
    scene->addActor(*body);

    renderItem = new RenderItem(sh, body, color);
}

RigidBody::RigidBody(PxPhysics* physics, PxScene* scene, const PxGeometry& geometry, PxTransform transform, float mass, PxVec3 inertiaTensor, PxVec3 initialVelocity, PxVec4 color)
{
    if (!physics || !scene) {
        throw std::runtime_error("Physics o Scene no pueden ser nulos");
    }

    // Crear un cuerpo rígido dinámico
    PxRigidDynamic* new_solid = physics->createRigidDynamic(transform);
    if (!new_solid) {
        throw std::runtime_error("Error: No se pudo crear PxRigidDynamic");
    }

    // Configurar velocidades iniciales
    new_solid->setLinearVelocity(initialVelocity);
    new_solid->setAngularVelocity(PxVec3(0, 0, 0));

    // Crear la forma asociada
    PxShape* sh = CreateShape(geometry);
    if (!sh) {
        throw std::runtime_error("Error: No se pudo crear PxShape");
    }
    new_solid->attachShape(*sh);

    // Configurar la masa y los tensores de inercia manualmente
    new_solid->setMass(mass);
    new_solid->setMassSpaceInertiaTensor(inertiaTensor);

    // Añadir el actor a la escena
    scene->addActor(*new_solid);

    // Renderizar el actor
    renderItem = new RenderItem(sh, new_solid, color);
    body = new_solid; // Guardar referencia
}


RigidBody::~RigidBody()
{
    if (renderItem) delete renderItem;
    if (body) body->release();
}

void RigidBody::setColor(const PxVec4& newColor)
{
    if (renderItem) {
        renderItem->color = newColor;
    }
}
