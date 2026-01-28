#pragma once
#include "../scene/GameObject.h"
#include "../gfx/Mesh.h"
#include "../gfx/Shader.h"

class MarioObject : public GameObject {
public:
    MarioObject();
    void update(float dt) override;
    void render(Renderer& renderer) override;

private:
    float time = 0.f;
    int frame = 0;
    Mesh meshA;
    Mesh meshB;
    Shader shader;
};
