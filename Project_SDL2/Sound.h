#ifndef _SOUND_
#define _SOUND_

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

bool loadMedia();

void PlaySound(Mix_Music* gMusic);

#endif // _SOUND_
