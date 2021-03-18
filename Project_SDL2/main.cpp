#include <iostream>
#include <SDL.h>
#include "mouse_and_keyboard.h"
#include "Utils.h"
#include "Duc_s_algo.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    //VeHinh(window, renderer);
    determine(window, renderer);
    //mouse(window, renderer);

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    cout << "Hello world!" << endl;
    return 0;
}


