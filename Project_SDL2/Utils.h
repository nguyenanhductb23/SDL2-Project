#ifndef _UTILS_
#define _UTILS_

#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "PrintText.h"
#include "StandardObject.h"
using namespace std;

#define CLOCK_NOW chrono::system::time_point;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int TITLE_HEIGHT = 100;
const int SQ_SIZE = 50;
const int NUM_OF_SQ_BY_X = SCREEN_WIDTH / SQ_SIZE;
const int NUM_OF_SQ_BY_Y = SCREEN_HEIGHT / SQ_SIZE;
const SDL_Rect BIG_RECT = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
const string WINDOW_TITLE = "SCREEEEEEEN";

///Mix_Chunk* punch_sound = Mix_LoadWAV( "punch.wav" );
///Mix_Chunk* ting_sound = Mix_LoadWAV( "ting.wav" );
///Mix_Music* gMusic = Mix_LoadMUS("beat.wav");

void logSDLError(std::ostream& os, const string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

SDL_Texture* loadPNG(SDL_Renderer*, SDL_Surface*, const char*);

SDL_Texture* loadPNG_KeyColor(SDL_Renderer*, SDL_Surface*, const char*);

void presentPNG(SDL_Renderer*, SDL_Texture* texture, const SDL_Rect &rect);

bool loadMedia(SDL_Renderer*);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

#endif
