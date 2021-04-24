#ifndef _M_K_
#define _M_K_
#include "StandardObject.h"

//void mouse(SDL_Window* &, SDL_Renderer* &);

void RandomMove(Object &, const Object*, const int &);

void KeyboardMove(SDL_Event&, Object&, const Object*, const int&);

void startMenu(SDL_Renderer* &);

#endif
