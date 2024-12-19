#pragma once
#include <vector>
#include "Scene.h"

class Game {
public:
    Game(PxPhysics* physics, PxScene* scene);
    ~Game();

    void addScene(Scene* scene);
    void setActiveScene(int index);
    void update(double t);
    void keyPressed(unsigned char key, const PxTransform& camera);
    Scene* getScene(int index) const;

    

private:
    std::vector<Scene*> scenes;
    Scene* activeScene;

    PxPhysics* physics;
    PxScene* scene;
};
