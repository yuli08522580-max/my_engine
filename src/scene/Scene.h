// scene/Scene.h
#pragma once
#include <vector>
#include <memory>

class GameObject;
class Renderer;

class Scene {
public:
    ~Scene();  // ★ 追加

    void add(std::unique_ptr<GameObject> obj);
    void update(float dt);
    void render(Renderer& renderer);

private:
    std::vector<std::unique_ptr<GameObject>> objects;
};
