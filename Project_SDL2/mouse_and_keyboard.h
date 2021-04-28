#ifndef _M_K_
#define _M_K_

#include <vector>
#include "Struct.h"
#include "Duc_s_algo.h"
#include "Utils.h"
#include "StandardObject.h"
#include "PrintText.h"

//void mouse(SDL_Window* &, SDL_Renderer* &);

void RandomMove(Object&, const Object*, const int&, int**);

void KeyboardMove(SDL_Event&, Object&, Object*, int&, int**);

void startMenu(Media*);

void Replay(Media*, int&);

#endif
