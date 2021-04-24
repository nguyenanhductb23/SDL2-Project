#include <iostream>
#include <SDL.h>
#include <ctime>
#include <SDL_mixer.h>
#include "Struct.h"
#include "Duc_s_algo.h"
#include "Utils.h"
#include "StandardObject.h"
#include "PrintText.h"

using namespace std;

void RandomMove(Object &enemy, const Object* wall, const int &WALLS) {
    unsigned int dir = rand() % 5;
    SDL_Rect rect = enemy.getRect();
    const int LEFT = 0, RIGHT = 1, DOWN = 2, UP = 3;
    switch (dir) {
        case LEFT: rect.x = rect.x - SQ_SIZE;
            break;
        case RIGHT: rect.x = rect.x + SQ_SIZE;
            break;
        case DOWN: rect.y = rect.y + SQ_SIZE;
            break;
        case UP: rect.y = rect.y - SQ_SIZE;
            break;
        default: break;
    }
    if (CanMove(rect, wall, WALLS))
        enemy.setRect(rect);
}

void KeyboardMove(SDL_Event &e, Object& Werner, const Object* wall, const int &WALLS) {
    SDL_Rect rect = Werner.getRect();
    const int SQ_SIZE = 50;
    switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_LEFT: rect.x = rect.x - SQ_SIZE;
            break;
        case SDLK_RIGHT: rect.x = rect.x + SQ_SIZE;
            break;
        case SDLK_DOWN: rect.y = rect.y + SQ_SIZE;
            break;
        case SDLK_UP: rect.y = rect.y - SQ_SIZE;
            break;
        default: break;
    }
    if (CanMove(rect, wall, WALLS))
        Werner.setRect(rect);
}

/**void mouse(SDL_Window* &window, SDL_Renderer* &renderer)
{
    bool isRunning = true;
    SDL_Event mainEvent;
    while (isRunning) {
        while (SDL_PollEvent(&mainEvent)) {
            time_t timer = clock();
            switch (mainEvent.type) {
                case SDL_QUIT: {
                    isRunning = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (mainEvent.button.button == SDL_BUTTON_LEFT) {
                        printf("Left Mouse Clicked\n");
                    }
                    else if (mainEvent.button.button == SDL_BUTTON_RIGHT) {
                        printf("Right Mouse Clicked\n");
                    }
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    std::cout << timer << std::endl;
                    timer = clock() - timer;
                    std::cout << timer;
                    if (mainEvent.button.button == SDL_BUTTON_LEFT) {
                        printf("Left Mouse Released\n");
                    }
                    else if (mainEvent.button.button == SDL_BUTTON_RIGHT) {
                        printf("Right Mouse Released\n");
                    }
                    break;
                }
                case SDL_MOUSEMOTION: {
                    printf("Current Position Mouse: (%d, %d)\n", mainEvent.motion.x, mainEvent.motion.y);
                    break;
                }
                case SDL_MOUSEWHEEL: {
                    printf("Mouse Wheel Motion\n");
                    break;
                }
                case SDL_KEYDOWN: {
                    std::cout << (char)mainEvent.key.keysym.sym << " pressed " << timer << std::endl;
                    break;
                }
                case SDL_KEYUP: {
                    std::cout << (char)mainEvent.key.keysym.sym << " released " << std::endl;
                    break;
                }
                default: break;
            }
        }
    }
}*/


void startMenu(SDL_Renderer* &renderer) {
    SDL_Event e;
    SDL_Texture* menu_texture = loadPNG(renderer, NULL, "StartMenu.png");
    SDL_RenderCopy(renderer, menu_texture, NULL, &big_rect);
    SDL_RenderPresent(renderer);
    Mix_Chunk* gScratch = Mix_LoadWAV( "ting.wav" );

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type != SDL_MOUSEBUTTONDOWN || e.button.button != SDL_BUTTON_LEFT) {
                continue;
            }
            SDL_Point mouse_pos;//(e.motion.x, e.motion.y);
            mouse_pos.x = e.motion.x;
            mouse_pos.y = e.motion.y;
            const SDL_Rect rect1 = {235,200,545,95};
            const SDL_Rect rect2 = {235,350,545,90};
            if (isIn(mouse_pos, rect1)) {
                Mix_PlayChannel( -1, gScratch, 0 );
                return;
            }
            if (isIn(mouse_pos, rect2)) {
                Mix_PlayChannel( -1, gScratch, 0 );
                int i = 0;
                GameOver(renderer, i);
            }
        }
    }
}



