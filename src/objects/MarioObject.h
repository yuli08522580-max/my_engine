#pragma once
#include "../scene/GameObject.h"
#include "../gfx/Mesh.h"
#include "../gfx/Shader.h"

class MarioObject : public GameObject {
public:
    // 2枚のスプライトを使う簡易アニメーション付きのマリオオブジェクトを生成する。
    MarioObject();
    // 経過時間から現在フレーム(0 or 1)を更新する。
    void update(float dt) override;
    // 現在フレームに対応するメッシュを描画する。
    void render(Renderer& renderer) override;

private:
    // アニメーション再生用の累積時間[s]。
    float time = 0.f;
    // 現在の表示フレーム番号。
    int frame = 0;
    // フレーム0/1のマリオスプライト。
    Mesh meshA;
    Mesh meshB;
    // スプライト描画に使う共通シェーダー。
    Shader shader;
};
