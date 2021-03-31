#include <iostream>
#include <SDL.h>
#include <windows.h>
#include <SDL_image.h>
#include <ctime>
#include <SDL_ttf.h>

#ifndef _Text_
    #define _Text_
    #include "PrintText.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";

void loadBackground(SDL_Renderer* renderer, const char* path, SDL_Rect rect) {
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;
    IMG_Init(IMG_INIT_PNG);
    image = IMG_Load(path);
    if (image == NULL)
        cerr << "Can't load background. Error: " << SDL_GetError();
    else {
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
        SDL_FreeSurface(image);
    }
}

/**SDL_Surface* loadImage(string path) {
    SDL_Surface* load = NULL;
    SDL_Surface* bkg = NULL;
    load = IMG_Load(path.c_str());
    if (load == NULL) cout << "Can't load background";
    else {
        bkg = SDL_DisplayFormat(load);
        SDL_FreeSurface(load);
    }
    return bkg;
}*/

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

/**void setBkg(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (loadMedia()) SDL_BlitSurface(surface, NULL, bkg, NULL);
}*/

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
                   const SDL_Rect* rectt, const int ENEMIES, const SDL_Rect* wall, const int WALLS) {
    SDL_RenderClear(renderer);
    SDL_Rect big_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    loadBackground(renderer, "Background.png", big_rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(renderer, &treasure);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < ENEMIES; i++) {
        SDL_RenderFillRect(renderer, &rectt[i]);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int i = 0; i < WALLS; i++) {
        SDL_RenderFillRect(renderer, &wall[i]);
    }
    SDL_RenderPresent(renderer);
}

void GameOver(SDL_Window* window, SDL_Renderer* renderer, int &score) {
    SDL_SetRenderDrawColor(renderer, 255, 127, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    printText(window, renderer);
    cout << "GAME OVER!!" << endl << "Your score: " << score;
    exit(0);
}

void moveTreasure(SDL_Rect& treasure) {
    treasure.x = rand() % (SCREEN_WIDTH - treasure.w);
    treasure.y = rand() % (SCREEN_HEIGHT - treasure.h);
}

#endif
