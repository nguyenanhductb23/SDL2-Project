#include <iostream>
#include <SDL.h>
#include <ctime>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";

SDL_Surface* bkg = NULL;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
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

bool loadMedia()
{
    SDL_Surface* bkg = NULL;
    bool success = true;
    bkg = SDL_LoadBMP("hello_world.bmp");
    if (bkg == NULL)
    {
        cout << "Loading image failed. " << SDL_GetError();
        success = false;
    }

    return success;
}

void setBkg(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (loadMedia()) SDL_BlitSurface(surface, NULL, bkg, NULL);
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

void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect, const SDL_Rect& treasure,
                   const SDL_Rect* rectt, const int ENEMIES, const SDL_Rect* wall, const int WALLS)
{
    //setBkg(window, renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(renderer, &treasure);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < ENEMIES; i++) {
        SDL_RenderFillRect(renderer, &rectt[i]);
    }
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
    for (int i = 0; i < WALLS; i++) {
        SDL_RenderFillRect(renderer, &wall[i]);
    }
    SDL_RenderPresent(renderer);
}

void GameOver(SDL_Window* window, SDL_Renderer* renderer) {\
    SDL_SetRenderDrawColor(renderer, 255, 127, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}

void moveTreasure(SDL_Rect& treasure) {
    treasure.x = rand() % (SCREEN_WIDTH - treasure.w);
    treasure.y = rand() % (SCREEN_HEIGHT - treasure.h);
}
