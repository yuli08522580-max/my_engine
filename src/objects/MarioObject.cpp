#include "MarioObject.h"
#include "../gfx/Renderer.h"

MarioObject::MarioObject()
: meshA(Mesh::marioSprite(0)),
  meshB(Mesh::marioSprite(1)),
  shader(Shader::vertexColor())
{}

void MarioObject::update(float dt) {
    time += dt;
    frame = (static_cast<int>(time * 4.0f) % 2);
}

void MarioObject::render(Renderer& renderer) {
    if (frame == 0) {
        renderer.draw(meshA, shader);
    } else {
        renderer.draw(meshB, shader);
    }
}
