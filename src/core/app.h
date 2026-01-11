// core/App.h
#pragma once
#include "../scene/Scene.h"
#include "../gfx/Renderer.h"

class Window;

class App {
public:
    App(Window& window);
    void run();

private:
    Window& window;
    Scene scene;
    Renderer renderer;
};
