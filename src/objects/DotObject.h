#pragma once
#include "../scene/GameObject.h"
#include "../gfx/Mesh.h"
#include "../gfx/Shader.h"
#include "../physics/Collision2D.h"
#include "BlockPlacement.h"
#include "PlayerPhysicsTuning.h"
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
    // 配置ブロック1辺の長さ。
    static constexpr float blockSize = 0.1f;
    // プレイヤー(ドット)の当たり判定サイズ。
    static constexpr float playerSize = 0.05f;
    // ブロック配置座標を丸めるグリッド間隔。
    static constexpr float blockSnap = 0.1f;
    // ブロック配置の連続入力を抑える最小間隔[s]。
    static constexpr float placeInterval = 0.15f;
    // モードインジケータのサイズ。
    static constexpr float modeIndicatorSize = 0.05f;
    // モードインジケータ表示位置(X)。
    static constexpr float modeIndicatorX = -0.92f;
    // モードインジケータ表示位置(Y)。
    static constexpr float modeIndicatorY = 0.92f;
    // 落下速度の上限。
    static constexpr float maxFallSpeed = 2.2f;
    // 重力調整時の増減ステップ。
    static constexpr float gravityAdjustStep = 0.1f;
    // ジャンプ力調整時の増減ステップ。
    static constexpr float jumpAdjustStep = 0.05f;
    // 空中で実行できるジャンプを含む最大ジャンプ回数。
    static constexpr int maxJumpCount = 2;
    // ジャンプ開始位置からの最高到達高さ。
    static constexpr float jumpApexHeight = 0.28f;
    // 最高到達点で静止する時間[s]。
    static constexpr float jumpApexHangDuration = 0.12f;

    // プレイヤー中心位置(X)。
    float x = 0.0f;
    // プレイヤー中心位置(Y)。
    float y = 0.0f;
    // true: ステージ編集モード / false: 通常プレイモード。
    bool stageEditMode = false;
    // モード切り替えキーの前フレーム押下状態。
    bool toggleModeKeyWasDown = false;
    // ブロック配置のクールダウン残り時間[s]。
    float placeCooldown = 0.0f;
    // ブロック削除のクールダウン残り時間[s]。
    float removeCooldown = 0.0f;
    // 垂直方向の速度。
    float velocityY = 0.0f;
    // 接地中かどうか。
    bool grounded = false;
    // ジャンプキーの前フレーム押下状態。
    bool jumpKeyWasDown = false;
    // 現在の滞空中に実行したジャンプ回数。
    int jumpCount = 0;
    // 現在ジャンプ遷移中かどうか。
    bool jumpInProgress = false;
    // 最高到達点で静止中かどうか。
    bool apexHangActive = false;
    // ジャンプ開始時のY座標。
    float jumpStartY = 0.0f;
    // 今回ジャンプで目指す最高到達Y座標。
    float jumpApexY = 0.0f;
    // 最高到達点での経過静止時間[s]。
    float apexHangTimer = 0.0f;
    // 重力増加キーの前フレーム押下状態。
    bool increaseGravityKeyWasDown = false;
    // 重力減少キーの前フレーム押下状態。
    bool decreaseGravityKeyWasDown = false;
    // ジャンプ力増加キーの前フレーム押下状態。
    bool increaseJumpKeyWasDown = false;
    // ジャンプ力減少キーの前フレーム押下状態。
    bool decreaseJumpKeyWasDown = false;
    // 現在配置されているブロック一覧。
    std::vector<block_placement::BlockPos> blocks;
    // 重力・ジャンプ力の動的チューニング値。
    PlayerPhysicsTuning physicsTuning;
    // プレイヤー本体のメッシュ。
    Mesh mesh;
    // プレイヤー本体描画用シェーダー。
    Shader shader;
    // 配置ブロック描画用メッシュ。
    Mesh blockMesh;
    // 配置ブロック描画用シェーダー。
    Shader blockShader;
    // 通常プレイモード表示用インジケータ。
    Mesh playModeIndicatorMesh;
    // 編集モード表示用インジケータ。
    Mesh editModeIndicatorMesh;
    // モードインジケータ描画用シェーダー。
    Shader modeIndicatorShader;
};
