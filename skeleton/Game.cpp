#include "Game.h"

Game::Game(PxPhysics* p, PxScene* s) : physics(p), scene(s), activeScene(nullptr) {}

Game::~Game() {
    for (auto scene : scenes) {
        delete scene;
    }
}

void Game::addScene(Scene* scene) {
    if (scene) {
        scenes.push_back(scene);
    }
}

void Game::setActiveScene(int index) {
    if (index >= 0 && index < scenes.size()) {
        activeScene = scenes[index];
        activeScene->initScene();
    }
}

void Game::update(double t) {
    if (activeScene) {
        activeScene->update(t);
    }
}

void Game::keyPressed(unsigned char key, const PxTransform& camera) {
    if (activeScene) {
        activeScene->keyPressed(key, camera);
    }
}
