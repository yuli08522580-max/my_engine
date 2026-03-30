#pragma once
#include "../scene/GameObject.h"
#include "../gfx/Mesh.h"
#include "../gfx/Shader.h"
#include "../physics/Collision2D.h"
#include "BlockPlacement.h"
#include <vector>

// プレイヤーが操作する白いドットと配置済みブロックを管理・描画するオブジェクト。
class DotObject : public GameObject {
public:
    DotObject();
    // 入力に応じた移動と、ブロック配置/削除の更新を行う。
    void update(float dt) override;
    // 配置済みブロックとドット本体を描画する。
    void render(Renderer& renderer) override;

private:
    static constexpr float blockSize = 0.1f;
    static constexpr float playerSize = 0.05f;
    static constexpr float blockSnap = 0.1f;
    static constexpr float placeInterval = 0.15f;
    static constexpr float modeIndicatorSize = 0.05f;
    static constexpr float modeIndicatorX = -0.92f;
    static constexpr float modeIndicatorY = 0.92f;
    static constexpr float gravityAcceleration = 1.8f;
    static constexpr float maxFallSpeed = 1.4f;
    static constexpr float jumpVelocity = 0.85f;

    float x = 0.0f;
    float y = 0.0f;
    bool stageEditMode = false;
    bool toggleModeKeyWasDown = false;
    float placeCooldown = 0.0f;
    float removeCooldown = 0.0f;
    float velocityY = 0.0f;
    bool grounded = false;
    bool jumpKeyWasDown = false;
    std::vector<block_placement::BlockPos> blocks;
    Mesh mesh;
    Shader shader;
    Mesh blockMesh;
    Shader blockShader;
    Mesh playModeIndicatorMesh;
    Mesh editModeIndicatorMesh;
    Shader modeIndicatorShader;
};
