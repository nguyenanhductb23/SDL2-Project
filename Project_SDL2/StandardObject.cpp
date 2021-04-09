#include "StandardObject.h"
#include <iostream>

StandardObject::StandardObject() {
    texture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    //this->loadPNG(renderer);
}

///StandardObject::StandardObject(string path, int x, int y, int w, int h) {
///    IMG_Init(IMG_INIT_PNG);
///    texture = IMG_Load(path);
///    rect = {x, y, w, h};
///}

SDL_Texture* StandardObject::loadPNG(SDL_Renderer* renderer, SDL_Surface* image, const char* path) {
    SDL_Texture* texture = NULL;
    IMG_Init(IMG_INIT_PNG);
    image = IMG_Load(path);
    if (image == NULL)  std::cerr << "Can't load background. Error: " << SDL_GetError();
    else {
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
    }
    return texture;
}

void StandardObject::presentPNG(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect &rect) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

void StandardObject::setRect(const int& x, const int& y, const int& w, const int& h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

StandardObject::~StandardObject() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}

void StandardObject::Render(SDL_Renderer* renderer, const SDL_Rect* pos) {
    SDL_Rect pos_rect = { rect.x, rect.y, rect.w, rect.h };
    if (pos != NULL) {
        pos_rect.w = pos->w;
        pos_rect.h = pos->h;
    }
    SDL_RenderCopy(renderer, texture, pos, &pos_rect);
}
