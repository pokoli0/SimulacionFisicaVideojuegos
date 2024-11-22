#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Vector3D.h"
#include "Particle.h"
#include "ParticleSystem.h"

#include <iostream>

std::string display_text = "Paula Sierra Luque";


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

// Apartado 1
vector<Particle*> proyectiles;

// Apt 2
ParticleSystem* pSystem = NULL;


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
	//sphereTf = new PxTransform(0, 40.0f, 0);
	//sphere = new RenderItem(CreateShape(PxSphereGeometry(10)), sphereTf, Vector4(0.3, 0.5, 0.4, 1));

	//// Ejes XYZ
	//xTf = new PxTransform(10, 0, 0);
	//xSphere = new RenderItem(CreateShape(PxSphereGeometry(1)), xTf, Vector4(1, 0, 0, 1));
	//yTf = new PxTransform(0, 10, 0);
	//ySphere = new RenderItem(CreateShape(PxSphereGeometry(1)), yTf, Vector4(0, 1, 0, 1));
	//zTf = new PxTransform(0, 0, 10);
	//zSphere = new RenderItem(CreateShape(PxSphereGeometry(1)), zTf, Vector4(0, 0, 1, 1));
	//originTf = new PxTransform(0, 0, 0);
	//originSphere = new RenderItem(CreateShape(PxSphereGeometry(1)), originTf, Vector4(1, 1, 1, 1));

	// Particle
	//particle = new Particle(PxVec3(0, 0, 0), PxVec3(0, 0, 0), PxVec3(5, 0, 0));

	// Particle System
	pSystem = new ParticleSystem();


	pSystem->addGenerator(UNIFORME,
		PxVec3(0, 0, 0),  // Centro del generador
		PxVec3(0, 0, 0),  // Velocidad inicial nula
		10,               // Tasa de generación (partículas por segundo)
		PxVec3(0, 0, 0),  // Sin desviación inicial
		10,               // Rango de emisión
		3,                // Spawn range
		GenDistribution::UNIFORMDIST,
		200,               // Ratio
		5                 // Vida útil
	);

	//pSystem->addGenerator(NORMAL,
	//	Vector3(0, 0, 0), //pos
	//	Vector3(0, 30, 0), //dir
	//	25, //rate
	//	Vector3(10, 0.0001, 10), // desv
	//	20, //range
	//	20, //spawn range
	//	GenDistribution::UNIFORMDIST, 
	//	50, //ratio
	//	10); //lifetime

	pSystem->addGravity(PxVec3(0, -9.8f, 0));
	//pSystem->addWind(PxVec3(30, 0, 0), 0.5f); // viento hacia la derecha
	//pSystem->addTornado(PxVec3(0, 0, 0), 20, 50, -1.0f); // tornado con centro , intensidad, radio y duracion infinita (-1)

}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t) // es como el update
{
	pSystem->update(t);

	PX_UNUSED(interactive);

	for (int i = 0; i < proyectiles.size(); i++) {

		proyectiles[i]->Integrate(t, Particle::IntegrationType::SEMIEULER);
	}

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// **** deregisters **** 
	//DeregisterRenderItem(sphere);
	//DeregisterRenderItem(xSphere);
	//DeregisterRenderItem(ySphere);
	//DeregisterRenderItem(zSphere);

	delete pSystem;	

	for (auto p : proyectiles) {
		delete p;
	}

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

void InstanciaParticula() {
	Particle* particle = new Particle(PxVec3(GetCamera()->getTransform().p), PxVec3(GetCamera()->getDir() * 10), PxVec3(0, -5, 0));
	proyectiles.push_back(particle);
	cout << "Particulas: " << proyectiles.size() << endl;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera) //input 
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'B': 
		InstanciaParticula();
		break;

	case 'E': 
		pSystem->addExplosion(
			PxVec3(0,0,0),	 // Centro de la explosión
			5000,            // Intensidad
			100,			 // Radio
			1.0f             // Tau
		);
		break;

	case ' ':
	
		break;
	
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