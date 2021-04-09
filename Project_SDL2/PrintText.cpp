#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

TTF_Font* TTF_OpenFont(const char *file, int ptsize);

void printText(SDL_Window* window, SDL_Renderer* renderer) {
    TTF_Font* font = NULL;
    font = TTF_OpenFont("ARCADE.ttf", 30);
    SDL_Color col = {243, 156, 18};
    string text = "CAPTION DEUER";
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), col);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);
    srcRest.x = 0;
    srcRest.y = 0;
    desRect.x = 200;
    desRect.y = 270;
    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
    //Copy a portion of the texture to the current rendering target.
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
    //draw to screen
    SDL_RenderPresent(renderer);
}
