#ifndef _UTILS_
#define _UTILS_
#include <iostream>
#include "StandardObject.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int SQ_SIZE = 50;
const SDL_Rect big_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
const std::string WINDOW_TITLE = "SCREEEEEEEN";

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

SDL_Texture* loadPNG(SDL_Renderer*, SDL_Surface*, const char*);

void presentPNG(SDL_Renderer*, SDL_Texture* texture, const SDL_Rect &rect);

bool loadMedia(SDL_Renderer*);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void moveTreasure(Object&);

void GameOver(SDL_Renderer*, int&);

#endif
