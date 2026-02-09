#pragma once
#include <string>
#include <SDL.h>

// SDLとOpenGLコンテキストの生成・イベント処理を担当するウィンドウクラス。
class Window {
public:
    // 指定サイズ・タイトルでウィンドウを作成する。
    Window(int w, int h, const std::string& title);
    // SDL/OpenGL関連リソースを解放する。
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // ウィンドウが開いているかどうかを返す。
    bool isOpen() const { return open; }
    // イベントキューを処理し、終了操作を検出する。
    void pollEvents();
    // ダブルバッファの内容を画面に反映する。
    void swap();
    // 現在のウィンドウサイズを取得する。
    void getSize(int& w, int& h) const;

private:
    // SDLビデオサブシステムを初期化する。
    void initSdl();
    // OpenGLコンテキスト属性を設定する。
    void setupGlAttributes();
    // SDLウィンドウとOpenGLコンテキストを生成する。
    void create(int w, int h, const std::string& title);
    // GL関数ローダー(glad)を初期化する。
    void initGlad();

private:
    // メインループ継続フラグ。
    bool open = true;
    // SDLウィンドウハンドル。
    SDL_Window* window = nullptr;
    // OpenGLコンテキストハンドル。
    SDL_GLContext glctx = nullptr;
};
