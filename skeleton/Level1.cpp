#include "Level1.h"

void Level1::initScene()
{
	Scene::initScene();


	addFloor();

	addFryer();

	/*rigidBodies.push_back(new RigidBody(
		physics, scene, PxBoxGeometry(5, 5, 5), PxTransform({ 0, 10, 0 }), 0.15f, PxVec3(0, 0, 0), PxVec4(1, 0, 0, 1)));*/
}

void Level1::addFloor()
{
	// Generar suelo
	PxRigidStatic* Suelo = physics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	Suelo->attachShape(*shape);
	scene->addActor(*Suelo);

	// Pintar suelo
	RenderItem* item;
	item = new RenderItem(shape, Suelo, { 1, 1, 1, 1 });

}

void Level1::addFryer()
{
	//
	PxRigidStatic* p1 = physics->createRigidStatic(PxTransform({ 10,10,10 }));
	PxShape* shape = CreateShape(PxBoxGeometry(10, 8, 1));
	p1->attachShape(*shape);
	scene->addActor(*p1);

	RenderItem* item;
	item = new RenderItem(shape, p1, { 0, 0, 1, 1 });

	//
	PxRigidStatic* p2 = physics->createRigidStatic(PxTransform({ 10,10,-10 }));
	p2->attachShape(*shape);
	scene->addActor(*p2);

	item = new RenderItem(shape, p2, { 0, 0, 1, 1 });

	//
	PxRigidStatic* p3 = physics->createRigidStatic(PxTransform({ 0,10,0 }));
	shape = CreateShape(PxBoxGeometry(1, 8, 10));
	p3->attachShape(*shape);
	scene->addActor(*p3);

	item = new RenderItem(shape, p3, { 0, 0, 1, 1 });

	//
	PxRigidStatic* p4 = physics->createRigidStatic(PxTransform({ 20,10,0 }));
	p4->attachShape(*shape);
	scene->addActor(*p4);

	item = new RenderItem(shape, p4, { 0, 0, 0.2, 1 });
}
