#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include <vector>
#include <PxPhysicsAPI.h>
#include "ParticleGenerator.h"
#include "Result.h"

#include "Game.h"

class Kitchen : public Scene {
public:
    Kitchen(Game* game, PxPhysics* physics, PxScene* scene);
    ~Kitchen();

    void initScene() override;
    void update(double t) override;
    void keyPressed(unsigned char key, const PxTransform& camera) override;;
    void clearScene() override; // limpia todo menos las patatas para el final result

    void createKitchen();
    void createPan();

    void setupCamera();

    // ingredientes
    void addOil();
    void addPotatoes();
    void addSalt();

    PxVec4 calculatePotatoColor(float elapsedTime);

    // Comprobacion de si la patata esta en el area de la sarten
    void checkPanLimits();
    void checkExtinguisherUsingTime(double t);

    // EVENTOS
    void generateFire(const PxVec3& position);
    void useExtinguisher();

    void endCooking();



    void setDefaultMaterial(PxMaterial* material) override { Scene::setDefaultMaterial(material); };

private:
    Game* game = nullptr;

    // Encargado de la gravedad
    ParticleSystem* pSystem = nullptr; 

    // Encargado de la flotacion
    ParticleSystem* buoySystem = nullptr;

    // Encargado del fuego: sin gravedad, pero con viento
    ParticleSystem* fireSystem = nullptr;

    std::vector<ParticleSystem*> systems;

    std::vector<RigidBody*> potatoesB;
    std::vector<RigidBody*> allPotatoes;

    bool oiled = false;
    int oilLevel = 0; // Control del nivel de aceite (0, 1, 2)
    float panWidth = 20.0f; // Ancho de la sartén
    float panDepth = 20.0f; // Profundidad de la sartén
    float panHeight = 0.5f; // Altura máxima del aceite

    int potatoes = 0;
    int maxPotatoes = 15;

    bool salted = false;
    int saltDensity = 15;
    int salt = 0;

    /// Gestion del fuego y el extintor
    bool extinguisher = false;
    float extinguisherTime = 0.0f;          // Tiempo que lleva activo el extintor
    const float extinguisherThreshold = 5.0f; // Tiempo necesario para extinguir el fuego
    bool canGenerateFire = true;           // Bandera para permitir o prohibir nuevos fuegos
    ParticleGenerator* extinguisherGenerator = nullptr;
    std::vector<ParticleGenerator*> fireGenerators;


};
