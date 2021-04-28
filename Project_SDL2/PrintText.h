#ifndef _PRINT_TEXT_
#define _PRINT_TEXT_

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Utils.h"

using namespace std;

void printText(SDL_Renderer*);

SDL_Texture* loadFromRenderedText(string, SDL_Color, TTF_Font* &, SDL_Renderer* &);

void copyText(SDL_Texture*, const SDL_Rect &, SDL_Renderer* &);

#endif // _PRINT_TEXT_
