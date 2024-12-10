#include "RigidBody.h"

RigidBody::RigidBody(PxPhysics* physics, PxScene* scene, PxGeometry geometry, PxTransform transform, float density, PxVec3 initialVelocity, PxVec4 color)
{
	// Solido rigido dinamico
	PxRigidDynamic* new_solid;
	new_solid = physics->createRigidDynamic(transform);
	new_solid->setLinearVelocity(initialVelocity);
	new_solid->setAngularVelocity(PxVec3(0, 0, 0));

	PxShape* sh;
	sh = CreateShape(geometry);
	new_solid->attachShape(*sh);

	PxRigidBodyExt::updateMassAndInertia(*new_solid, density);
	scene->addActor(*new_solid);

	// Renderizar actor
	RenderItem* dynamic = new RenderItem(sh, new_solid, color);
}

RigidBody::~RigidBody()
{
    if (renderItem) delete renderItem;
    if (body) body->release();
}
