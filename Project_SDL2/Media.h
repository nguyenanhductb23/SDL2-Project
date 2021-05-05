#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "Utils.h"

struct Media{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* background_png;
    SDL_Texture* start_menu_png;
    SDL_Texture* game_over_png;
    SDL_Texture* instruction_png;
    SDL_Texture* instruction2_png;
    SDL_Texture* choose_mode_png;
    SDL_Texture* pause_png;
    SDL_Texture* pause_button_png;
    SDL_Texture* Werner_png;
    SDL_Texture* enemy_png;
    SDL_Texture* wall_png;
    SDL_Texture* treasure_png;
    Mix_Music* music;
    Mix_Chunk* ping;
    Mix_Chunk* bupp;
    Mix_Chunk* explode;
    TTF_Font* font;
    Media() {
        initSDL(window, renderer);
        background_png = loadPNG(renderer, NULL, "Media/Background.png");
        start_menu_png = loadPNG(renderer, NULL, "Media/StartMenu.png");
        game_over_png = loadPNG(renderer, NULL, "Media/GameOver.png");
        instruction_png = loadPNG(renderer, NULL, "Media/Instruction.png");
        instruction2_png = loadPNG(renderer, NULL, "Media/Instruction2.png");
        choose_mode_png = loadPNG(renderer, NULL, "Media/ChooseMode.png");
        pause_png = loadPNG(renderer, NULL, "Media/Pause.png");
        pause_button_png = loadPNG_KeyColor(renderer, NULL, "Media/PauseButton.png");
        Werner_png = loadPNG_KeyColor(renderer, NULL, "Media/Werner.png");
        enemy_png = loadPNG_KeyColor(renderer, NULL, "Media/An_enemy.png");
        wall_png = loadPNG_KeyColor(renderer, NULL, "Media/Brick.png");
        treasure_png = loadPNG_KeyColor(renderer, NULL, "Media/Treasure.png");
        music = Mix_LoadMUS("Media/NaturalSound.wav");
        ping = Mix_LoadWAV("Media/ping.wav");
        bupp = Mix_LoadWAV("Media/bupp.wav");
        explode = Mix_LoadWAV("Media/laser.wav");
        font = TTF_OpenFont("Media/LibraSans.ttf", 30);
    }
    ~Media() {
        quitSDL(window, renderer);
        window = NULL;               renderer = NULL;
        Mix_FreeMusic(music);           music = NULL;
        Mix_FreeChunk(ping);            ping = NULL;
        Mix_FreeChunk(bupp);            bupp = NULL;
        Mix_FreeChunk(explode);            explode = NULL;
        TTF_CloseFont(font);            font = NULL;
        SDL_DestroyTexture(background_png);         background_png = NULL;
        SDL_DestroyTexture(start_menu_png);         start_menu_png = NULL;
        SDL_DestroyTexture(instruction_png);         instruction_png = NULL;
        SDL_DestroyTexture(game_over_png);         game_over_png = NULL;
        SDL_DestroyTexture(Werner_png);         Werner_png = NULL;
        SDL_DestroyTexture(treasure_png);         treasure_png = NULL;
        SDL_DestroyTexture(enemy_png);         enemy_png = NULL;
        SDL_DestroyTexture(treasure_png);         treasure_png = NULL;
        SDL_DestroyTexture(wall_png);         wall_png = NULL;
    }
};

#endif // _MEDIA_H_
