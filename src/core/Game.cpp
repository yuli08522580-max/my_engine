// core/Game.cpp
#include "Game.h"
#include "Window.h"
#include "../objects/DotObject.h"
#include <glad/glad.h>
#include <memory>

Game::Game(Window& window)
: window(window) {}

void Game::Initialize() {
    scene.add(std::make_unique<DotObject>());
}

void Game::Update(float dt) {
    window.pollEvents();
    scene.update(dt);
}

void Game::Render() {
    int width = 0;
    int height = 0;
    window.getSize(width, height);
    glViewport(0, 0, width, height);

    renderer.clear(0.1f, 0.2f, 0.6f, 1.f);
    scene.render(renderer);
    window.swap();
}
