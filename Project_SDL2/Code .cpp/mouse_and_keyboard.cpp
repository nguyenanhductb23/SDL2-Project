#include <iostream>
#include <SDL.h>
#include <ctime>

#ifndef _Utils_
    #define _Utils_
    #include "Utils.h"

#ifndef _Algos_
    #define _Algos_
    #include "Duc_s_algo.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";

void RandomMove(SDL_Rect &rect) {
    int stepp = 10;
    unsigned int dir = rand() % 5;
    const int LEFT = 0, RIGHT = 1, DOWN = 2, UP = 3;
    switch (dir) {
        case LEFT: rect.x = (rect.x + SCREEN_WIDTH - stepp) % SCREEN_WIDTH;
            break;
        case RIGHT: rect.x = (rect.x + stepp) % SCREEN_WIDTH;
            break;
        case DOWN: rect.y = (rect.y + stepp) % SCREEN_HEIGHT;
            break;
        case UP: rect.y = (rect.y + SCREEN_HEIGHT - stepp) % SCREEN_HEIGHT;
            break;
        default: break;
    }
}

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

void move(SDL_Window* window, SDL_Renderer* renderer, SDL_Rect& rect, SDL_Rect& treasure,
          SDL_Rect* rectt, const int ENEMIES, SDL_Rect* wall, const int WALLS, int &score) {
    int step = 20;
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) == 0) continue;
        SDL_Delay(10);
        for (int i = 0; i < ENEMIES; i++) {
            srand(time(0)+i);
            /**unsigned int dir = rand() % 5;
            const int LEFT = 0, RIGHT = 1, DOWN = 2, UP = 3;
            switch (dir) {
                case LEFT: rectt[i].x = (rectt[i].x + SCREEN_WIDTH - stepp) % SCREEN_WIDTH;
                    break;
                case RIGHT: rectt[i].x = (rectt[i].x + stepp) % SCREEN_WIDTH;
                    break;
                case DOWN: rectt[i].y = (rectt[i].y + stepp) % SCREEN_HEIGHT;
                    break;
                case UP: rectt[i].y = (rectt[i].y + SCREEN_HEIGHT - stepp) % SCREEN_HEIGHT;
                    break;
                default: break;
            }*/
            RandomMove(rectt[i]);
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
                case SDLK_SPACE: GameOver(window, renderer, score);
                    return;
                default: break;
            }
            playerHitAnEntity(window, renderer, rect, treasure, rectt, ENEMIES, score);
            SDL_Delay(10);
            refreshScreen(window, renderer, rect, treasure, rectt, ENEMIES, wall, WALLS);
        }
    }
}

void determine(SDL_Window* &window, SDL_Renderer* &renderer, int &score) {
    SDL_Event e;
    const int ENEMIES = 25;
    SDL_Rect rectt[ENEMIES];
    for (int i = 0; i < ENEMIES; i++) {
        rectt[i].x = 300 + 20*i;
        rectt[i].y = 300 + 20*i;
        rectt[i].w = 25;
        rectt[i].h = 25;
    }
    const int WALLS = 25;
    SDL_Rect wall[WALLS];
    srand(time(0));
    int vertical = rand() % WALLS;
    for (int i = 0; i < vertical; i++) {
        wall[i].x = rand() % SCREEN_WIDTH;
        wall[i].y = rand() % SCREEN_HEIGHT;
        wall[i].w = 100;
        wall[i].h = 10;
    }
    for (int i = vertical+1; i < WALLS; i++) {
        wall[i].x = rand() % SCREEN_WIDTH;
        wall[i].y = rand() % SCREEN_HEIGHT;
        wall[i].w = 10;
        wall[i].h = 100;
    }
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 15;
    rect.h = 15;
    SDL_Rect treasure;
    treasure.x = rand() % SCREEN_WIDTH;
    treasure.y = rand() % SCREEN_HEIGHT;
    treasure.w = 30;
    treasure.h = 20;
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_Delay(10);
    SDL_RenderPresent(renderer);
    move(window, renderer, rect, treasure, rectt, ENEMIES, wall, WALLS, score);
}

#endif
#endif
