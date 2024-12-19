#pragma once

#include "Scene.h"
#include "RigidBody.h"
#include "ParticleGenerator.h"

#include "Game.h"

class Result : public Scene {
public:
    Result(Game* game, PxPhysics* physics, PxScene* scene);
    ~Result() override = default;

    void update(double t) override;
    void initScene() override;
    void clearScene() override;

    void setPotatoes(const std::vector<RigidBody*>& cookedPotatoes);

    void setDefaultMaterial(PxMaterial* material) override { Scene::setDefaultMaterial(material); };

private:
    Game* game = nullptr;

    std::vector<RigidBody*> potatoes;

    ParticleSystem* pSystem = nullptr;

    std::vector<ParticleGenerator*> finalGenerator;
};
