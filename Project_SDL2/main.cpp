#include <iostream>
#include <SDL.h>
#include "mouse_and_keyboard.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void VeHinh(SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    VeHinh(renderer);
    SDL_RenderPresent(renderer);
    mouse(window, renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    cout << "Hello world!" << endl;
    return 0;
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(1000);
    }
}

void VeHinh(SDL_Renderer* renderer)
{
    SDL_Event event;
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 20;
    rect.h = 15;
    SDL_SetRenderDrawColor(renderer,0,0,255,255);
    SDL_RenderFillRect(renderer, &rect);
    while (event.type != SDL_QUIT) {
        rect.x = event.motion.x;
        rect.y = event.motion.y;
        SDL_SetRenderDrawColor(renderer,0,100,0,255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_Delay(500);
        SDL_RenderClear(renderer);
        //();
    }
}
