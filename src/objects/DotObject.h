#pragma once
#include "../scene/GameObject.h"
#include "../gfx/Mesh.h"
#include "../gfx/Shader.h"
#include "BlockPlacement.h"
#include <vector>

class DotObject : public GameObject {
public:
    DotObject();
    void update(float dt) override;
    void render(Renderer& renderer) override;

private:
    static constexpr float blockSize = 0.1f;
    static constexpr float blockSnap = 0.1f;
    static constexpr float placeInterval = 0.15f;

    float x = 0.0f;
    float y = 0.0f;
    float placeCooldown = 0.0f;
    std::vector<block_placement::BlockPos> blocks;
    Mesh mesh;
    Shader shader;
    Mesh blockMesh;
    Shader blockShader;
};
