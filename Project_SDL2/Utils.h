#ifndef _UTILS_
#define _UTILS_
#include "StandardObject.h"

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

SDL_Texture* loadPNG(SDL_Renderer*, SDL_Surface*, const char*);

void presentPNG(SDL_Renderer*, SDL_Texture* texture, const SDL_Rect &rect);

bool loadMedia(SDL_Renderer*);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void VeHinh(SDL_Window* window, SDL_Renderer* renderer);

void refreshScreen(SDL_Window*, SDL_Renderer*, SDL_Surface*, SDL_Surface*, SDL_Texture*, SDL_Texture*,
                   StandardObject&, const SDL_Rect&, const SDL_Rect*, const int, const SDL_Rect*, const int);

void moveTreasure(SDL_Rect&);

void GameOver(SDL_Window*, SDL_Renderer*, int&);

#endif
