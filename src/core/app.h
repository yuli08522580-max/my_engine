// core/App.h
#pragma once
#include "../scene/Scene.h"
#include "../gfx/Renderer.h"

class Window;

// シンプルなアプリ実行ループを提供するクラス。
class App {
public:
    // ウィンドウ参照を受け取り、初期オブジェクトを構築する。
    App(Window& window);
    // アプリのメインループを実行する。
    void run();

private:
    // 描画先となるウィンドウ参照。
    Window& window;
    // 更新・描画対象オブジェクトを管理するシーン。
    Scene scene;
    // 描画コマンドを実行するレンダラー。
    Renderer renderer;
};
