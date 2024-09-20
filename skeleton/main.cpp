#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

std::string display_text = "pokoli0";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

// **** items ****
RenderItem* sphere = NULL;
RenderItem* xSphere = NULL;
RenderItem* ySphere = NULL;
RenderItem* zSphere = NULL;
RenderItem* originSphere = NULL;

// **** transforms ****
PxTransform* sphereTf;
PxTransform* xTf;
PxTransform* yTf;
PxTransform* zTf;
PxTransform* originTf;



// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// **** init renderItems **** 
	
	// Sphere
	sphereTf = new PxTransform(0, 40.0f, 0);
	sphere = new RenderItem(CreateShape(PxSphereGeometry(10)), sphereTf, Vector4(0.3, 0.5, 0.4, 1));

	// Ejes XYZ
	xTf = new PxTransform(10, 0, 0);
	xSphere = new RenderItem(CreateShape(PxSphereGeometry(1)), xTf, Vector4(1, 0, 0, 1));
	yTf = new PxTransform(0, 10, 0);
	ySphere = new RenderItem(CreateShape(PxSphereGeometry(1)), yTf, Vector4(0, 1, 0, 1));
	zTf = new PxTransform(0, 0, 10);
	zSphere = new RenderItem(CreateShape(PxSphereGeometry(1)), zTf, Vector4(0, 0, 1, 1));
	originTf = new PxTransform(0, 0, 0);
	originSphere = new RenderItem(CreateShape(PxSphereGeometry(1)), originTf, Vector4(1, 1, 1, 1));
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t) // es como el update
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// **** deregisters **** 
	DeregisterRenderItem(sphere);
	DeregisterRenderItem(xSphere);
	DeregisterRenderItem(ySphere);
	DeregisterRenderItem(zSphere);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera) //input 
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}