#include <iostream>
#include <SDL.h>
#include <ctime>
#include "Struct.h"
#include "Duc_s_algo.h"
#include "Utils.h"
#include "StandardObject.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";
const char* PATH = "Background.png";

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

void KeyboardMove(SDL_Rect& rect, SDL_Event e) {
    int step = 10;
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
        default: break;
    }
}

/*void mouse(SDL_Window* &window, SDL_Renderer* &renderer)
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

void move(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* image, SDL_Surface* Wnimg, SDL_Texture* texture, SDL_Texture* Wntexture, StandardObject& Werner, SDL_Rect& treasure,
          SDL_Rect* rectt, const int ENEMIES, SDL_Rect* wall, const int WALLS, int &score) {
    int step = 20;
    SDL_Event e;
    SDL_Rect Wnrect = Werner.getRect();
    while (true) {
        for (int i = 0; i < ENEMIES; i++) {
            srand(time(0)+i);
            RandomMove(rectt[i]);
        }
        refreshScreen(window, renderer, image, Wnimg, texture, Wntexture, Werner, treasure, rectt, ENEMIES, wall, WALLS);
        playerHitAnObject(window, renderer, Werner.getRect(), treasure, rectt, ENEMIES, score);
        if (SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
            KeyboardMove(Wnrect, e);
            Werner.setRect(Wnrect.x, Wnrect.y, Wnrect.w, Wnrect.h);
        }

    }
}

void determine(SDL_Window* &window, SDL_Renderer* &renderer, int &score) {
    StandardObject Werner;
    Werner.setRect(100, 100, 50, 50);

    SDL_Surface* image = NULL;
    SDL_Surface* Wnimg = NULL;
    const SDL_Rect big_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Texture* texture = loadPNG(renderer, image, "Background.png");
    SDL_Texture* Wntexture = loadPNG(renderer, Wnimg, "Werner.png");
    presentPNG(renderer, texture, big_rect);

    SDL_Event e;
    const int ENEMIES = 5;
    SDL_Rect rectt[ENEMIES];
    for (int i = 0; i < ENEMIES; i++) {
        rectt[i].x = 300 + 20*i;
        rectt[i].y = 300 + 15*i;
        rectt[i].w = 25;
        rectt[i].h = 25;
    }
    const int WALLS = 100;
    SDL_Rect wall[WALLS];
    srand(time(0));
    int horizontal = 57;//rand() % WALLS;
    for (int i = 0; i < horizontal; i++) {
        wall[i].w = 100;
        wall[i].h = 10;
        wall[i].x = (wall[i].w * rand()) % SCREEN_WIDTH;
        wall[i].y = (wall[i].w * rand()) % SCREEN_HEIGHT;
    }
    for (int i = horizontal+1; i < WALLS; i++) {
        wall[i].w = 10;
        wall[i].h = 100;
        wall[i].x = (wall[i].h * rand()) % SCREEN_WIDTH;
        wall[i].y = (wall[i].h * rand()) % SCREEN_HEIGHT;
    }

    SDL_Rect treasure;
    treasure.x = rand() % SCREEN_WIDTH;
    treasure.y = rand() % SCREEN_HEIGHT;
    treasure.w = 30;
    treasure.h = 20;
    SDL_SetRenderDrawColor(renderer,0,255,0,255);
    SDL_RenderFillRect(renderer, &treasure);
    SDL_RenderPresent(renderer);
    move(window, renderer, image, Wnimg, texture, Wntexture, Werner, treasure, rectt, ENEMIES, wall, WALLS, score);
}

//void mainLoop(StandardObject Werner, )
