#include <iostream>
#include "SDL.h"
#include "DLMath.h"
#include "DLVector.h"
#include "DLQuat.h"

using namespace std;
using namespace DontLaugh;

const int WIDTH = 800, HEIGHT = 600; // SDL窗口的宽和高

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // 初始化SDL
        cout << "SDL could not initialized with error: " << SDL_GetError() << endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("DL SoftRender", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (nullptr == window) {
        cout << "SDL could not create window with error: " << SDL_GetError() << endl;
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_SOFTWARE);

    SDL_Event windowEvent; // SDL窗口事件
    while (true) {
        if (SDL_PollEvent(&windowEvent)) { // 对当前待处理事件进行轮询。
            if (SDL_QUIT == windowEvent.type) { // 如果事件为推出SDL，结束循环。
                cout << "SDL quit!!" << endl;
                break;
            }
        }
    }

    SDL_DestroyWindow(window); // 推出SDL窗体
    SDL_Quit(); // SDL推出

    return 0;
}
