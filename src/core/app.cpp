// core/App.cpp
#include "App.h"
#include "Window.h"
#include <memory>
#include "../objects/TriangleObject.h"

App::App(Window& window) : window(window) {
    scene.add(std::make_unique<TriangleObject>());
}

void App::run() {
    float dt = 0.016f;

    while (window.isOpen()) {
        window.pollEvents();
        scene.update(dt);
        renderer.clear(0.1f, 0.2f, 0.6f, 1.f);
        scene.render(renderer);
        window.swap();
    }
}
