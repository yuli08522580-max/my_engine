// scene/GameObject.h
#pragma once

class Renderer;

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void update(float dt) {}
    virtual void render(Renderer& renderer) = 0;
};
