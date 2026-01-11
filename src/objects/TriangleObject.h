// objects/TriangleObject.h
#pragma once
#include "../scene/GameObject.h"
#include "../gfx/Mesh.h"
#include "../gfx/Shader.h"

class TriangleObject : public GameObject {
public:
    TriangleObject();
    void update(float dt) override;
    void render(Renderer& renderer) override;

private:
    float time = 0.f;
    Mesh mesh;
    Shader shader;
};
