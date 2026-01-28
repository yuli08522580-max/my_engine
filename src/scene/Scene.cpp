// scene/Scene.cpp
#include "Scene.h"
#include "GameObject.h"

Scene::~Scene() = default;  // ★ 追加

void Scene::add(std::unique_ptr<GameObject> obj) {
    objects.push_back(std::move(obj));
}

void Scene::update(float dt) {
    for (auto& o : objects) o->update(dt);
}

void Scene::render(Renderer& renderer) {
    for (auto& o : objects) o->render(renderer);
}
