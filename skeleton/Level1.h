#pragma once
#include "Scene.h"

class Level1 : public Scene 
{
public:
    Level1(PxPhysics* physics, PxScene* scene) : Scene(physics, scene) {}
    void initScene() override;

private:
    void addFloor();

    void addFryer();
};
