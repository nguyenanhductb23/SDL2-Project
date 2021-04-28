#ifndef _ALGOS_
#define _ALGOS_

#include "StandardObject.h"
#include "Utils.h"
#include "MainEngine.h"
#include "HighScoreFile.h"
#include "Sound.h"

string intToString(const int &num);

void GameOver(Media*, int&);

void moveTreasure(Object&, int**);

bool isIn(const SDL_Point, const SDL_Rect&);

bool ReachTreasure(const Object &Werner, const Object &treasure);

bool RectHitsRect(const SDL_Rect rect1, const SDL_Rect rect2);

void playerHitAnObject(Media*, Object&, Object&, const Object*, int**, int&);

bool CanMove(const SDL_Rect&, const Object*, const int&);

void freeFalling(Media*, Object&);

void Instruction(Media*);

#endif
