// core/Game.h
#pragma once

#include "../gfx/Renderer.h"
#include "../scene/Scene.h"

class Window;

// ゲーム全体の更新・描画ループを管理する制御クラス。
class Game {
public:
    // ウィンドウ参照を受け取り、ゲーム実行に必要な状態を初期化する。
    explicit Game(Window& window);

    // シーンに初期オブジェクトを登録する。
    void Initialize();
    // 1フレーム分の入力処理とシーン更新を行う。
    void Update(float dt);
    // 1フレーム分の描画処理を行う。
    void Render();

private:
    // 描画先となるウィンドウ参照。
    Window& window;
    // 現在のゲーム内オブジェクトを保持するシーン。
    Scene scene;
    // OpenGL描画を担当するレンダラー。
    Renderer renderer;
};
