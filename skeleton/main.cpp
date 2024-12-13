#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Vector3D.h"
#include "Particle.h"
#include "ParticleSystem.h"

#include "RigidBody.h"


#include "Game.h"
#include "Level1.h"

#include <iostream>

Game* game = nullptr;

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

	// --- Creacion de material ---
	//createMaterial(staticFriction, dynamicFriction, restitution);
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f); // Para los solidos rigidos

	// --- Creacion de escena ---
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f); // Importante!!!
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);



	/// ==== PRACTICA 1 ====
	 
	// particle = new Particle();
	
	
	/// ==== PRACTICA 2 ====

	pSystem = new ParticleSystem();
	
	//pSystem->addGenerator(UNIFORME,
	//	PxVec3(0, 0, 0),  // Centro del generador
	//	PxVec3(0, 0, 0),  // Velocidad inicial nula
	//	10,               // Tasa de generación (partículas por segundo)
	//	PxVec3(0, 0, 0),  // Sin desviación inicial
	//	10,               // Rango de emisión
	//	3,                // Spawn range
	//	GenDistribution::UNIFORMDIST,
	//	200,               // Ratio
	//	5                 // Vida útil
	//);

	//pSystem->addGenerator(NORMAL,
	//	Vector3(0, 0, 0), //pos
	//	Vector3(0, 30, 0), //dir
	//	25, //rate
	//	Vector3(10, 0.0001, 10), // desv
	//	20, //range
	//	5, //spawn range
	//	GenDistribution::UNIFORMDIST, 
	//	50, //ratio
	//	10); //lifetime
	

	/// ==== PRACTICA 3 ====

	pSystem->addGravity(PxVec3(0, -9.8f, 0));
	//pSystem->addWind(PxVec3(30, 0, 0), 0.5f); // viento hacia la derecha
	//pSystem->addTornado(PxVec3(0, 0, 0), 20, 50, -1.0f); // tornado con centro , intensidad, radio y duracion infinita (-1)


	/// ==== PRACTICA 4 ====

	//pSystem->generateParticleSpringDemo();

	Particle* p = new Particle(PxVec3(0, 10, 0), PxVec3(0, 0, 0), 1, PxVec4(1, 1, 0, 1), PxSphereGeometry(1));
	pSystem->addParticle(p);
	pSystem->addBuoyancy(10, 10, 1000);

	
	/// ==== PRACTICA 5 ====

	//// Generar suelo
	//PxRigidStatic* Suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	//PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	//Suelo->attachShape(*shape);
	//gScene->addActor(*Suelo);

	//// Pintar suelo
	//RenderItem* item;
	//item = new RenderItem(shape, Suelo, { 0, 0, 1, 1 });

	// ---- Solido rigido dinamico ----
	//RigidBody* rb = new RigidBody(
	//	gPhysics,
	//	gScene,
	//	PxBoxGeometry(5.0f, 5.0f, 5.0f),
	//	PxTransform({-70, 100, -70}),
	//	0.15f,
	//	PxVec3(0, 5, 0),
	//	PxVec4(0, 0, 1, 1)
	//);

	//// Dimensiones del cuboide
	//float a = 5.0f; // Largo
	//float b = 3.0f; // Ancho
	//float c = 2.0f; // Altura
	//float mass = 1; // Masa

	//// Calcular tensores de inercia
	//PxVec3 inertiaTensor;
	//inertiaTensor.x = (1.0f / 12.0f) * mass * (b * b + c * c);
	//inertiaTensor.y = (1.0f / 12.0f) * mass * (a * a + c * c);
	//inertiaTensor.z = (1.0f / 12.0f) * mass * (a * a + b * b);

	//// Crear el objeto RigidBody con tensor de inercia
	//RigidBody* rb = new RigidBody(
	//	gPhysics,
	//	gScene,
	//	PxBoxGeometry(a / 2, b / 2, c / 2), // PxBoxGeometry usa la mitad de las dimensiones
	//	PxTransform({ 0, 10, 0 }),           // Transform inicial
	//	mass,                              // Masa
	//	inertiaTensor,                     // Tensor de inercia
	//	PxVec3(0, 0, 0),                   // Velocidad inicial
	//	PxVec4(1, 0, 0, 1)                 // Color rojo
	//);

	//pSystem->addRigidBody(rb);

	//pSystem->addWind(PxVec3(20, 0, 0), 0.5f);


	/// ==== PROYECTO ====

	//game = new Game(gPhysics, gScene);

	//Level1* level1 = new Level1(gPhysics, gScene);

	//game->addScene(level1);

	//game->setActiveScene(0);

}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t) // es como el update
{
	pSystem->update(t);

	PX_UNUSED(interactive);

	if(game) game->update(t);

	//for (int i = 0; i < proyectiles.size(); i++) {

	//	proyectiles[i]->Integrate(t, Particle::IntegrationType::SEMIEULER);
	//}
	
	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	delete pSystem;	

	for (auto p : proyectiles) {
		delete p;
	}

	if(game) delete game;

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
	Particle* particle = new Particle();

	//particle->setVelocity()
	//PxVec3(GetCamera()->getTransform().p),
	//	PxVec3(GetCamera()->getDir() * 10),
	//	1,
	//	PxVec4(1, 1, 1, 1)
	//
	pSystem->addParticle(particle);
	proyectiles.push_back(particle);
	cout << "Particulas: " << proyectiles.size() << endl;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera) //input 
{
	if(game) game->keyPressed(key, camera);

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

	case 'Q':
		pSystem->removeForce(ForceType::GRAVITY);
		break;
	
	case 'O':
		pSystem->addGravity(PxVec3(0, 9.8, 0)); // Hacia arriba
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