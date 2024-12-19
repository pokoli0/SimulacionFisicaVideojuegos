#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include <vector>
#include <PxPhysicsAPI.h>

class Kitchen : public Scene {
public:
    Kitchen(PxPhysics* physics, PxScene* scene);
    ~Kitchen();

    void initScene() override;
    void update(double t) override;
    void keyPressed(unsigned char key, const PxTransform& camera) override;;

    void createKitchen();
    void createPan();

    void setupCamera();

    // ingredientes
    void addOil();
    void addPotatoes();

    PxVec4 calculateColor(float elapsedTime);

    // Comprobacion de si la patata esta en el area de la sarten
    void checkPanLimits();

    // EVENTOS
    void generateFire(const PxVec3& position);

    // Setters
    void setDefaultMaterial(PxMaterial* material) { defaultMaterial = material; }

private:
    // Encargado de la gravedad
    ParticleSystem* pSystem = nullptr; 

    // Encargado de la flotacion
    ParticleSystem* buoySystem = nullptr;

    std::vector<ParticleSystem*> systems;

    PxMaterial* defaultMaterial = nullptr;
    std::vector<RenderItem*> renderItems;

    std::vector<RigidBody*> potatoesB;

    int oilLevel = 0; // Control del nivel de aceite (0, 1, 2)
    float panWidth = 20.0f; // Ancho de la sartén
    float panDepth = 20.0f; // Profundidad de la sartén
    float panHeight = 0.5f; // Altura máxima del aceite

    int potatoes = 0;
    int maxPotatoes = 15;

};
