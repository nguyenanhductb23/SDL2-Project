#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "mouse_and_keyboard.h"
#include "Utils.h"
#include "Duc_s_algo.h"
#include "PrintText.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";

int main(int argc, char* argv[])
{
    int score = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Rect big_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    loadBackground(renderer, "Background.png", big_rect);
    //VeHinh(window, renderer);
    printText(window, renderer);
    determine(window, renderer, score);
    //mouse(window, renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    cout << "Hello world!  " << score << endl;
    return 0;
}


