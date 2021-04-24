#include "mouse_and_keyboard.h"
#include "Utils.h"
#include "Duc_s_algo.h"
#include "StandardObject.h"
#include "PrintText.h"
#include "MainEngine.h"
#include "Sound.h"

using namespace std;

int main(int argc, char* argv[])
{
    int score = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    //printText(window, renderer);

    determine(window, renderer, score);

    //waitUntilKeyPressed();
    quitSDL(window, renderer);
    //cout << "Hello world!  " << score << endl;
    return 0;
}
