// scene/Scene.h
#pragma once
#include <vector>
#include <memory>

class GameObject;
class Renderer;

// 複数のゲームオブジェクトを保持し、一括更新・描画を行うクラス。
class Scene {
public:
    // シーンに含まれるオブジェクト群を破棄する。
    ~Scene();

    // オブジェクトをシーンに追加する。
    void add(std::unique_ptr<GameObject> obj);
    // すべてのオブジェクトの更新処理を呼び出す。
    void update(float dt);
    // すべてのオブジェクトの描画処理を呼び出す。
    void render(Renderer& renderer);

private:
    // シーンに属するゲームオブジェクトの所有コンテナ。
    std::vector<std::unique_ptr<GameObject>> objects;
};
