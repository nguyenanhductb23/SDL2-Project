#include "Sound.h"

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;

bool loadMedia() {
    //Loading success flag
    bool success = true;
    //Load music
    gMusic = Mix_LoadMUS( "punch.wav" );
    if( gMusic == NULL ) {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    //Load sound effects
    gScratch = Mix_LoadWAV( "ting.wav" );
    if( gScratch == NULL ) {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gHigh = Mix_LoadWAV( "ting.wav" );
    if( gHigh == NULL ) {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gMedium = Mix_LoadWAV( "ting.wav" );
    if( gMedium == NULL ) {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    /**gLow = Mix_LoadWAV( "punch.wav" );
    if( gLow == NULL ) {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }*/

    return success;
}

/**void PlaySound() {
    SDL_Event e;
    if( e.type == SDL_KEYDOWN ) {
        switch( e.key.keysym.sym ) {
            //Play high sound effect
            case SDLK_1:
            Mix_PlayChannel( -1, gHigh, 0 );
            break;

            //Play medium sound effect
            case SDLK_2:
            Mix_PlayChannel( -1, gMedium, 0 );
            break;

            //Play low sound effect
            case SDLK_3:
            Mix_PlayChannel( -1, gLow, 0 );
            break;

            //Play scratch sound effect
            case SDLK_4:
            Mix_PlayChannel( -1, gScratch, 0 );
            break;

            case SDLK_9:
                //If there is no music playing
                if( Mix_PlayingMusic() == 0 ) {
                    //Play the music
                    if( Mix_PlayMusic( gMusic, -1 ) == -1 )
                    {
                        return;
                    }
                    //If music is being played
                    else
                    {
                        //If the music is paused
                        if( Mix_PausedMusic() == 1 )
                        {
                            //Resume the music
                            Mix_ResumeMusic();
                        }
                        //If the music is playing
                        else
                        {
                            //Pause the music
                            Mix_PauseMusic();
                        }
                    }
                    break;
                }
            case SDLK_0:
                //Stop the music
                Mix_HaltMusic();
                break;
        }
    }
}*/

void PlaySound(Mix_Music* gMusic) {
    if( Mix_PlayingMusic() == 0 ) {
        Mix_PlayMusic( gMusic, -1 );
    }
    else {
        if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
        else {
            Mix_PauseMusic();
        }
    }
}
