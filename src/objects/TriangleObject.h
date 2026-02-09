#pragma once
#include "../scene/GameObject.h"
#include "../gfx/Mesh.h"
#include "../gfx/Shader.h"

// 三角形メッシュを描画するサンプル用ゲームオブジェクト。
class TriangleObject : public GameObject {
public:
    // 三角形メッシュとシェーダーを初期化する。
    TriangleObject();
    // 経過時間を更新する。
    void update(float dt) override;
    // 三角形を描画する。
    void render(Renderer& renderer) override;

private:
    // 生成後の経過時間。
    float time = 0.f;
    // 描画対象のメッシュ。
    Mesh mesh;
    // 描画時に使用するシェーダー。
    Shader shader;
};
