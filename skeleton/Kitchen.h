#pragma once
#include "Scene.h"
#include <vector>
#include <PxPhysicsAPI.h>

class Kitchen : public Scene {
public:
    Kitchen(PxPhysics* physics, PxScene* scene);
    ~Kitchen();

    void initScene() override;

    void createPan();

    void setupCamera();

    // Setters
    void setDefaultMaterial(PxMaterial* material) { defaultMaterial = material; }

private:
    PxMaterial* defaultMaterial = nullptr; // Asegúrate de inicializar esto al crear la escena
    std::vector<RenderItem*> renderItems;
};
