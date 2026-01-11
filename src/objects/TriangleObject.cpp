// objects/TriangleObject.cpp
#include "TriangleObject.h"
#include "../gfx/Renderer.h"
#include <cmath>

TriangleObject::TriangleObject()
: mesh(Mesh::createTriangle()),
  shader(Shader::fromBasicColor())
{}

void TriangleObject::update(float dt) {
    time += dt;
}

void TriangleObject::render(Renderer& renderer) {
    renderer.draw(mesh, shader);
}
