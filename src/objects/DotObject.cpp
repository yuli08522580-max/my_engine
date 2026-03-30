#include "DotObject.h"
#include "../gfx/Renderer.h"
#include <SDL.h>
#include <algorithm>

namespace {
std::vector<collision2d::AABB> buildStageColliders(
    const std::vector<block_placement::BlockPos>& blocks,
    float blockSize
) {
    std::vector<collision2d::AABB> colliders;
    colliders.reserve(blocks.size());

    const float half = blockSize * 0.5f;
    for (const auto& block : blocks) {
        colliders.push_back({block.x, block.y, half, half});
    }
    return colliders;
}
}

DotObject::DotObject()
: mesh(Mesh::dotSprite(playerSize)),
  shader(Shader::vertexColorOffset()),
  blockMesh(Mesh::coloredQuad(blockSize, 0.55f, 0.35f, 0.15f)),
  blockShader(Shader::vertexColorOffset()),
  playModeIndicatorMesh(Mesh::coloredQuad(modeIndicatorSize, 0.15f, 0.85f, 0.25f)),
  editModeIndicatorMesh(Mesh::coloredQuad(modeIndicatorSize, 0.95f, 0.45f, 0.15f)),
  modeIndicatorShader(Shader::vertexColorOffset())
{}

void DotObject::update(float dt) {
    const Uint8* keys = SDL_GetKeyboardState(nullptr);
    const bool toggleModePressed = keys[SDL_SCANCODE_TAB];
    if (toggleModePressed && !toggleModeKeyWasDown) {
        stageEditMode = !stageEditMode;
    }
    toggleModeKeyWasDown = toggleModePressed;

    float dx = 0.0f;
    float dy = 0.0f;
    if (keys[SDL_SCANCODE_D]) dx += 1.0f;
    if (keys[SDL_SCANCODE_A]) dx -= 1.0f;

    const float speed = 0.6f;
    if (stageEditMode) {
        if (keys[SDL_SCANCODE_W]) dy += 1.0f;
        if (keys[SDL_SCANCODE_S]) dy -= 1.0f;
        velocityY = 0.0f;
    } else {
        velocityY -= gravityAcceleration * dt;
        velocityY = std::max(velocityY, -maxFallSpeed);
        dy = velocityY;
    }

    const collision2d::Vec2 delta{dx * speed * dt, dy * dt};

    if (stageEditMode) {
        x += delta.x;
        y += delta.y;
    } else {
        const float expectedY = y + delta.y;
        const collision2d::AABBCollisionResolver resolver(buildStageColliders(blocks, blockSize));
        const collision2d::Vec2 resolved = resolver.resolveMovement(
            {x, y},
            delta,
            {playerSize * 0.5f, playerSize * 0.5f}
        );
        x = resolved.x;
        y = resolved.y;
        if ((velocityY < 0.0f && y > expectedY) || (velocityY > 0.0f && y < expectedY)) {
            velocityY = 0.0f;
        }
    }

    // 画面端の少し内側に移動範囲を制限する。
    x = std::clamp(x, -0.95f, 0.95f);
    const float clampedY = std::clamp(y, -0.95f, 0.95f);
    if (!stageEditMode && clampedY != y && velocityY < 0.0f) {
        velocityY = 0.0f;
    }
    y = clampedY;

    // ステージ編集モード中のみ、ブロックの配置と削除を許可する。
    if (stageEditMode) {
        // 長押し時の過剰配置を防ぐため、配置間隔をクールダウンで制御する。
        placeCooldown = std::max(0.0f, placeCooldown - dt);
        const bool placePressed = keys[SDL_SCANCODE_SPACE];
        if (placePressed && placeCooldown <= 0.0f) {
            block_placement::tryPlaceBlock(blocks, x, y, blockSnap);
            placeCooldown = placeInterval;
        }

        // Backspace 長押し時の過剰削除を防ぐため、削除間隔をクールダウンで制御する。
        removeCooldown = std::max(0.0f, removeCooldown - dt);
        const bool removePressed = keys[SDL_SCANCODE_BACKSPACE];
        if (removePressed && removeCooldown <= 0.0f) {
            block_placement::tryRemoveBlock(blocks, x, y, blockSnap);
            removeCooldown = placeInterval;
        }
    }
}

void DotObject::render(Renderer& renderer) {
    (void)renderer;

    // 背景側に置かれるブロックを先に描画する。
    blockShader.use();
    for (const auto& block : blocks) {
        blockShader.setVec2("uOffset", block.x, block.y);
        blockMesh.draw();
    }

    // 最後にプレイヤー（白い点）を描画する。
    shader.use();
    shader.setVec2("uOffset", x, y);
    mesh.draw();

    // 左上にモードインジケーターを描画する（緑=プレイ, 橙=編集）。
    modeIndicatorShader.use();
    modeIndicatorShader.setVec2("uOffset", modeIndicatorX, modeIndicatorY);
    if (stageEditMode) {
        editModeIndicatorMesh.draw();
    } else {
        playModeIndicatorMesh.draw();
    }
}
