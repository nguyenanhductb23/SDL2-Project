#ifndef _MEDIA_H_
#define _MEDIA_H_

#include "Utils.h"

class Media{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* background_png;
    SDL_Texture* start_menu_png;
    SDL_Texture* game_over_png;
    SDL_Texture* instruction_png;
    SDL_Texture* Werner_png;
    SDL_Texture* enemy_png;
    SDL_Texture* wall_png;
    SDL_Texture* treasure_png;
    Mix_Music* music;
    Mix_Chunk* ping;
    Mix_Chunk* bupp;
    TTF_Font* font;
    Media() {
        initSDL(window, renderer);
        background_png = loadPNG(renderer, NULL, "Sky.png");
        start_menu_png = loadPNG(renderer, NULL, "StartMenu.png");
        game_over_png = loadPNG(renderer, NULL, "GameOver.png");
        instruction_png = loadPNG(renderer, NULL, "Instruction.png");
        Werner_png = loadPNG_KeyColor(renderer, NULL, "Werner.png");
        enemy_png = loadPNG_KeyColor(renderer, NULL, "An_enemy.png");
        wall_png = loadPNG_KeyColor(renderer, NULL, "Brick.png");
        treasure_png = loadPNG_KeyColor(renderer, NULL, "Treasure.png");
        music = Mix_LoadMUS("NaturalSound.wav");
        ping = Mix_LoadWAV("ping.wav");
        bupp = Mix_LoadWAV("bupp.wav");
        font = TTF_OpenFont("LibraSans.ttf", 15);
    }
    ~Media() {
        quitSDL(window, renderer);
        window = NULL;              renderer = NULL;
        delete background_png;      delete start_menu_png;       delete game_over_png;
        delete Werner_png;          delete enemy_png;            delete wall_png;
        delete treasure_png;        delete font;
        delete music;               delete ping;                 delete bupp;

    }
};

#endif // _MEDIA_H_
