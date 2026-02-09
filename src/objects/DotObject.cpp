#include "DotObject.h"
#include "../gfx/Renderer.h"
#include <SDL.h>
#include <algorithm>

DotObject::DotObject()
: mesh(Mesh::dotSprite()),
  shader(Shader::vertexColorOffset()),
  blockMesh(Mesh::coloredQuad(blockSize, 0.55f, 0.35f, 0.15f)),
  blockShader(Shader::vertexColorOffset())
  shader(Shader::vertexColorOffset()),
  blockMesh(Mesh::coloredQuad(blockSize, 0.55f, 0.35f, 0.15f)),
  blockShader(Shader::vertexColorOffset())
{}

void DotObject::update(float dt) {
    const Uint8* keys = SDL_GetKeyboardState(nullptr);
    float dx = 0.0f;
    float dy = 0.0f;
    if (keys[SDL_SCANCODE_W]) dy += 1.0f;
    if (keys[SDL_SCANCODE_S]) dy -= 1.0f;
    if (keys[SDL_SCANCODE_D]) dx += 1.0f;
    if (keys[SDL_SCANCODE_A]) dx -= 1.0f;

    const float speed = 0.6f;
    x += dx * speed * dt;
    y += dy * speed * dt;

    // 画面端の少し内側に移動範囲を制限する。
    x = std::clamp(x, -0.95f, 0.95f);
    y = std::clamp(y, -0.95f, 0.95f);

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
}
