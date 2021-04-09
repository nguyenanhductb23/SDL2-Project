#ifndef _ALGOS_
#define _ALGOS_

bool isIn(const SDL_Point, SDL_Rect);

void playerHitAnObject(SDL_Window*, SDL_Renderer*, const SDL_Rect, SDL_Rect&, const SDL_Rect*, const int, int&);

bool hitTheWall(const SDL_Rect, const SDL_Rect*, const int, const SDL_Rect*, const int);

#endif
