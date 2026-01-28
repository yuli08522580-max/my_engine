#include <SDL.h>  // ★ SDL は一番上あたりで読み込む

#include "core/Game.h"
#include "core/Window.h"

int main(int argc, char* argv[]) {  // ★ 引数付き main にする
    Window window(1280, 720, "my_engine");
    Game game(window);

    game.Initialize();

    const float dt = 0.016f;
    while (window.isOpen()) {
        game.Update(dt);
        game.Render();
    }
    return 0;
}
