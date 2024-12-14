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

    void keyPressed(unsigned char key, const PxTransform& camera) override;;

    void createPan();

    void setupCamera();

    void addOil();

    // Setters
    void setDefaultMaterial(PxMaterial* material) { defaultMaterial = material; }

private:
    ParticleSystem* pSystem = nullptr;

    PxMaterial* defaultMaterial = nullptr; // Asegúrate de inicializar esto al crear la escena
    std::vector<RenderItem*> renderItems;

    int oilLevel = 0; // Control del nivel de aceite (0, 1, 2)
    float panWidth = 20.0f; // Ancho de la sartén
    float panDepth = 20.0f; // Profundidad de la sartén
    float panHeight = 0.5f; // Altura máxima del aceite


};
