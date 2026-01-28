#pragma once
#include "../scene/GameObject.h"
#include "../gfx/Mesh.h"
#include "../gfx/Shader.h"

class DotObject : public GameObject {
public:
    DotObject();
    void update(float dt) override;
    void render(Renderer& renderer) override;

private:
    float x = 0.0f;
    float y = 0.0f;
    Mesh mesh;
    Shader shader;
};
