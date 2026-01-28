// core/Game.h
#pragma once

#include "../gfx/Renderer.h"
#include "../scene/Scene.h"

class Window;

class Game {
public:
    explicit Game(Window& window);

    void Initialize();
    void Update(float dt);
    void Render();

private:
    Window& window;
    Scene scene;
    Renderer renderer;
};
