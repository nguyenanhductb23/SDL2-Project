#ifndef _ALGOS_
#define _ALGOS_

#include "StandardObject.h"
#include "Utils.h"
#include "MainEngine.h"
#include "HighScoreFile.h"

string intToString(const int& num);

void GameOver(Media*, const int& mode, int&);

void moveTreasure(const int& mode, Object&, int**);

bool isIn(const SDL_Point&, const SDL_Rect&);

bool isIn(const SDL_Point&, const Object*, const int&, int& i);

bool ReachTreasure(const Object&, const Object&);

bool RectHitsRect(const SDL_Rect&, const SDL_Rect&);

void playerHitAnObject(Media*, const int& mode, Object&, Object&, const Object*, int**, int&);

bool CanMove(const SDL_Rect&, const Object*, const int&);

bool CanMove(const int& mode, const SDL_Rect&, int**);

void freeFalling(Media*, Object&);

void laserShoot(Media*, const int& mode, SDL_Renderer*, SDL_Point&, const Object&, Object*, int&, int**);

void Instruction(Media*);

#endif
