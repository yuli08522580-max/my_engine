#include <SDL.h>  // ★ SDL は一番上あたりで読み込む

#include "core/Window.h"
#include "gfx/Shader.h"
#include "gfx/Mesh.h"

#include <glad/glad.h>
#include <cmath>

int main(int argc, char* argv[]) {  // ★ 引数付き main にする
    Window window(1280, 720, "my_engine");

    Shader shader = Shader::basicColor();
    Mesh mesh = Mesh::triangle2D();

    float t = 0.0f;

    while (window.isOpen()) {
        window.pollEvents();

        int w, h;
        window.getSize(w, h);
        glViewport(0, 0, w, h);

        t += 0.016f;
        float r = 0.5f + 0.5f * std::sinf(t);

        glClearColor(r, 0.2f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        mesh.draw();

        window.swap();
    }
    return 0;
}
