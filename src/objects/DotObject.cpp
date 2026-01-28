#include "DotObject.h"
#include "../gfx/Renderer.h"
#include <SDL.h>
#include <algorithm>

DotObject::DotObject()
: mesh(Mesh::dotSprite()),
  shader(Shader::vertexColorOffset())
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

    x = std::clamp(x, -0.95f, 0.95f);
    y = std::clamp(y, -0.95f, 0.95f);
}

void DotObject::render(Renderer& renderer) {
    (void)renderer;
    shader.use();
    shader.setVec2("uOffset", x, y);
    mesh.draw();
}
