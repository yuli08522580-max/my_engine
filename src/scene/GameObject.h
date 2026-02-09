// scene/GameObject.h
#pragma once

class Renderer;

// シーン内に配置される描画・更新可能オブジェクトの基底クラス。
class GameObject {
public:
    // 派生クラス破棄のための仮想デストラクタ。
    virtual ~GameObject() = default;
    // 1フレーム分の更新処理を行う。
    virtual void update(float dt) {}
    // オブジェクト固有の描画処理を行う。
    virtual void render(Renderer& renderer) = 0;
};
