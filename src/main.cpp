#include <SDL.h>  // ★ SDL は一番上あたりで読み込む

#include "core/Window.h"
#include "gfx/Renderer.h"
#include "objects/TriangleObject.h"
#include "scene/Scene.h"

#include <glad/glad.h>
#include <memory>

namespace {

struct GameContext {
    Scene scene;
    Renderer renderer;
};

void Initialize(GameContext& context) {
    context.scene.add(std::make_unique<TriangleObject>());
}

void Update(GameContext& context, Window& window, float dt) {
    window.pollEvents();
    context.scene.update(dt);
}

void Render(GameContext& context, Window& window) {
    int width = 0;
    int height = 0;
    window.getSize(width, height);
    glViewport(0, 0, width, height);

    context.renderer.clear(0.1f, 0.2f, 0.6f, 1.f);
    context.scene.render(context.renderer);
    window.swap();
}
}  // namespace

int main(int argc, char* argv[]) {  // ★ 引数付き main にする
    Window window(1280, 720, "my_engine");
    GameContext context;

    Initialize(context);

    const float dt = 0.016f;
    while (window.isOpen()) {
        Update(context, window, dt);
        Render(context, window);
    }
    return 0;
}
