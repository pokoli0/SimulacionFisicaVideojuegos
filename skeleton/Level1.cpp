#include "Level1.h"

void Level1::initScene()
{
	Scene::initScene();

	rigidBodies.push_back(new RigidBody(
		physics, scene, PxBoxGeometry(5, 5, 5), PxTransform({ 0, 10, 0 }), 0.15f, PxVec3(0, 0, 0), PxVec4(1, 0, 0, 1)));
}
