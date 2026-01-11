// gfx/Renderer.cpp
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include <glad/glad.h>

void Renderer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const Mesh& mesh, const Shader& shader) {
    shader.use();
    mesh.draw();
}
