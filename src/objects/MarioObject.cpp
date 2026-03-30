#include "MarioObject.h"
#include "../gfx/Renderer.h"

MarioObject::MarioObject()
: meshA(Mesh::marioSprite(0)),
  meshB(Mesh::marioSprite(1)),
  shader(Shader::vertexColor())
{}

void MarioObject::update(float dt) {
    // 1秒あたり4コマ相当で進め、2フレームをループさせる。
    time += dt;
    frame = (static_cast<int>(time * 4.0f) % 2);
}

void MarioObject::render(Renderer& renderer) {
    // 更新済みフレームに応じて対応スプライトを描画する。
    if (frame == 0) {
        renderer.draw(meshA, shader);
    } else {
        renderer.draw(meshB, shader);
    }
}
