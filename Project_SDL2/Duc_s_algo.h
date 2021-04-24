#ifndef _ALGOS_
#define _ALGOS_
#include "StandardObject.h"

bool isIn(const SDL_Point, SDL_Rect);

void playerHitAnObject(SDL_Renderer*, Object&, Object&, const Object*, const int, int&);

bool CanMove(const SDL_Rect&, const Object*, const int);

void freeFalling(SDL_Renderer* &, Object&);

#endif
