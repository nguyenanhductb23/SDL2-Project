#ifndef _M_K_
#define _M_K_

#include <vector>
#include "Media.h"
#include "Duc_s_algo.h"
#include "Utils.h"
#include "StandardObject.h"

void RandomMove(const int& mode, Object&, const Object*, const int&, int**);

void KeyboardMove(const int& mode, SDL_Event&, Object&, Object*, int&, int**);

void startMenu(Media*);

void pauseMenu(Media*, const int&);

void playAgain(Media*, const int& mode, const int&);

int chooseMode(Media*);

#endif
