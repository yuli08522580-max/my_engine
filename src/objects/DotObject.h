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
    // ===== ジャンプ調整パラメータ =====
    // 上方向へ押し上げる初速。大きいほど高くジャンプする。
    float jumpVelocity = 0.85f;
    // 下方向へ引っ張る重力加速度。大きいほど速く落下する。
    float gravityAcceleration = 1.8f;
    // 下方向の終端速度。大きいほど落下の最高速度が上がる。
    float maxFallSpeed = 1.4f;

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
