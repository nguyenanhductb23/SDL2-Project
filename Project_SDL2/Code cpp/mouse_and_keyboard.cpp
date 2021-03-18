#include <iostream>
#include <SDL.h>
#include <ctime>

#ifndef _Utils_
    #define _Utils_ "Utils.h"
    #include "Utils.h"
#endif

#ifndef _Algos_
    #define _Algos_ "Duc_s_algo.h"
    #include "Duc_s_algo.h"
#endif

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";

void mouse(SDL_Window* &window, SDL_Renderer* &renderer)
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
}

void move(SDL_Window* window, SDL_Renderer* renderer, SDL_Rect& rect, SDL_Rect* rectt, const int ENEMIES) {
    int step = 10;
    int stepp = 20;
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) == 0) continue;
        SDL_Delay(10);
        for (int i = 0; i < ENEMIES; i++) {
            srand(time(0)+i);
            int dir = rand() % 4;
            const int LEFT = 0, RIGHT = 1, DOWN = 2;
            switch (dir) {
                case LEFT: rectt[i].x = (rectt[i].x + SCREEN_WIDTH - stepp) % SCREEN_WIDTH;
                    break;
                case RIGHT: rectt[i].x = (rectt[i].x + stepp) % SCREEN_WIDTH;
                    break;
                case DOWN: rectt[i].y = (rectt[i].y + stepp) % SCREEN_HEIGHT;
                    break;
                default: rectt[i].y = (rectt[i].y + SCREEN_HEIGHT - stepp) % SCREEN_HEIGHT;
                    break;
            }
        }
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE: break;
                case SDLK_LEFT: rect.x = (rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
                    break;
                case SDLK_RIGHT: rect.x = (rect.x + step) % SCREEN_WIDTH;
                    break;
                case SDLK_DOWN: rect.y = (rect.y + step) % SCREEN_HEIGHT;
                    break;
                case SDLK_UP: rect.y = (rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
                    break;
                case SDLK_SPACE: GameOver(window, renderer);
                    return;
                default: break;
            }
            if (playerHitAnEnemy(rect, rectt, ENEMIES)) GameOver(window, renderer);
            SDL_Delay(10);
            refreshScreen(window, renderer, rect, rectt, ENEMIES);
        }
    }
}

void determine(SDL_Window* &window, SDL_Renderer* &renderer) {
    SDL_Event e;
    const int ENEMIES = 25;
    SDL_Rect rectt[ENEMIES];
    for (int i = 0; i < ENEMIES; i++) {
        rectt[i].x = 300 + 30*i;
        rectt[i].y = 300 + 30*i;
        rectt[i].w = 25;
        rectt[i].h = 25;
    }

    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 15;
    rect.h = 15;
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
    move(window, renderer, rect, rectt, ENEMIES);
}
