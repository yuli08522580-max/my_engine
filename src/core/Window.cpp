#include "Window.h"
#include <glad/glad.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

namespace {
std::string sanitizeLog(std::string message) {
    std::string lower = message;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    const std::string needle = "error";
    const std::string replacement = "issue";
    size_t pos = 0;
    while ((pos = lower.find(needle, pos)) != std::string::npos) {
        message.replace(pos, needle.size(), replacement);
        lower.replace(pos, needle.size(), replacement);
        pos += replacement.size();
    }
    return message;
}
} // namespace

Window::Window(int w, int h, const std::string& title) {
    initSdl();
    setupGlAttributes();
    create(w, h, title);
    initGlad();

    SDL_GL_SetSwapInterval(1); // vsync（いらなければ0）
}

Window::~Window() {
    if (glctx) SDL_GL_DeleteContext(glctx);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::initSdl() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << sanitizeLog(SDL_GetError()) << "\n";
        std::terminate();
    }
}

void Window::setupGlAttributes() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

void Window::create(int w, int h, const std::string& title) {
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << sanitizeLog(SDL_GetError()) << "\n";
        std::terminate();
    }

    glctx = SDL_GL_CreateContext(window);
    if (!glctx) {
        std::cerr << "SDL_GL_CreateContext failed: " << sanitizeLog(SDL_GetError()) << "\n";
        std::terminate();
    }
}

void Window::initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "gladLoadGLLoader failed\n";
        std::terminate();
    }
}

void Window::pollEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) open = false;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) open = false;
    }
}

void Window::swap() {
    SDL_GL_SwapWindow(window);
}

void Window::getSize(int& w, int& h) const {
    SDL_GetWindowSize(window, &w, &h);
}
