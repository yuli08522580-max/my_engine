#pragma once
#include <string>
#include <SDL.h>

class Window {
public:
    Window(int w, int h, const std::string& title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool isOpen() const { return open; }
    void pollEvents();      // ESC/×で閉じる
    void swap();            // SDL_GL_SwapWindow
    void getSize(int& w, int& h) const;

private:
    void initSdl();
    void setupGlAttributes();
    void create(int w, int h, const std::string& title);
    void initGlad();

private:
    bool open = true;
    SDL_Window* window = nullptr;
    SDL_GLContext glctx = nullptr;
};
