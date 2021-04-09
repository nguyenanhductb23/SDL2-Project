#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "mouse_and_keyboard.h"
#include "Utils.h"
#include "Duc_s_algo.h"
#include "StandardObject.h"
#include "PrintText.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";

int main(int argc, char* argv[])
{
    //StandardObject* ens = new StandardObject();
    int score = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    //loadMedia(renderer);
    //VeHinh(window, renderer);
    //printText(window, renderer);
    determine(window, renderer, score);
    //mouse(window, renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    //cout << "Hello world!  " << score << endl;
    return 0;
}
