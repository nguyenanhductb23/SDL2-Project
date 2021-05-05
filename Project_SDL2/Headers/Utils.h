#ifndef _UTILS_
#define _UTILS_

#include <iostream>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "StandardObject.h"
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int TITLE_HEIGHT = 100;
const int NUM_OF_MODES = 3;
const int SQ_SIZE[NUM_OF_MODES] = {40, 50, 67};
const int NUM_OF_SQ_BY_X[NUM_OF_MODES] = {25, 20, 15};
const int NUM_OF_SQ_BY_Y[NUM_OF_MODES] = {15, 12, 9};
const int MAX_WALLS[NUM_OF_MODES] = {120, 80, 40};
const SDL_Rect BIG_RECT = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
const SDL_Rect GREEN_RECT = {800, 0, 200, 40};
const SDL_Rect PAUSE_RECT = {805, 0, 45, 40};
const SDL_Rect SCORE_RECT = {860, 5, 125, 27};
const string WINDOW_TITLE = "TREASURE HUNT PRO";

void logSDLError(std::ostream& os, const string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

SDL_Texture* loadPNG(SDL_Renderer*, SDL_Surface*, const char*);

SDL_Texture* loadPNG_KeyColor(SDL_Renderer*, SDL_Surface*, const char*);

void presentPNG(SDL_Renderer*, SDL_Texture* texture, const SDL_Rect &rect);

SDL_Texture* loadFromRenderedText(string, SDL_Color, TTF_Font*&, SDL_Renderer*&);

void copyText(SDL_Texture*, const SDL_Rect&, SDL_Renderer*&);

void PlaySound(Mix_Music* gMusic);

#endif
