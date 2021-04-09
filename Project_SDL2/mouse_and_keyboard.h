#ifndef _M_K_
#define _M_K_
#include "StandardObject.h"

void mouse(SDL_Window* &, SDL_Renderer* &);

void KeyboardMove(SDL_Rect& rect);

void move(SDL_Window*, SDL_Renderer*, SDL_Surface*, SDL_Surface*, SDL_Texture*, SDL_Texture*,
          StandardObject&, SDL_Rect&, SDL_Rect*, const int, SDL_Rect*, const int, int &);

void determine(SDL_Window* &, SDL_Renderer* &, int&);

#endif
