#include <iostream>
#include <SDL.h>
#include "StandardObject.h"
#include "Utils.h"

void freeFalling(SDL_Renderer* &renderer, Object &Werner) {//, Object* wall, const int WALLS) {
    const int FPS = 50;
    for (int i = 0; i < FPS; i++) {
        SDL_RenderClear(renderer);
        SDL_Rect rect = Werner.getRect();
        rect.y += 10;
        Werner.setRect(rect);
        Werner.presentPNG(renderer, Werner.getRect());
        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
}

bool isIn(const SDL_Point point, SDL_Rect rect) {
    if (point.x >= rect.x && point.x <= rect.x + rect.w
        && point.y >= rect.y && point.y <= rect.y + rect.h) return true;
    return false;
}

bool RectHitsRect(const SDL_Rect rect1, const SDL_Rect rect2) {
    SDL_Point point[4];
    point[1].x = rect1.x;
    point[3].x = rect1.x;
    point[0].x = rect1.x + rect1.w;
    point[2].x = point[0].x;
    point[1].y = rect1.y;
    point[2].y = rect1.y;
    point[3].y = rect1.y + rect1.h;
    point[0].y = point[3].y;
    for (int j = 0; j < 4; j++) {
        if (isIn(point[j], rect2)) return true;
    }
    return false;
}

void playerHitAnObject(SDL_Renderer* renderer, Object& Werner, Object& treasure,
                       const Object* enemy, const int ENEMIES, int &score) {
    const SDL_Rect Wnrect =  Werner.getRect();
    for (int i = 0; i < ENEMIES; i++) {
        if (RectHitsRect(enemy[i].getRect(), Wnrect)) {
            freeFalling(renderer, Werner);
            //Mix_PlayMusic(crash_sound, 1);
            //Mix_SetMusicPosition(musicPosition/1000);
            SDL_Delay(1000);
            GameOver(renderer, score);
            return;
        }
    }
    if (RectHitsRect(treasure.getRect(), Wnrect)) {
        score++;
        moveTreasure(treasure);
        return;
    }
}

bool EnemiesSelfCrash(SDL_Rect* rectt, int moved, SDL_Rect rect) {
    for (int i = 0; i < moved; i++) {
        if (RectHitsRect(rect, rectt[i]))
            return true;
    }
    return false;
}

bool CanMove(const SDL_Rect &rect, const Object* wall, const int WALLS) {\
    if (rect.x < 0 || rect.x >= SCREEN_WIDTH) return false;
    if (rect.y < 0 || rect.y >= SCREEN_HEIGHT) return false;

    for (int i = 0; i < WALLS; i++) {
        SDL_Rect rect_i = wall[i].getRect();
        if (rect_i.x == rect.x && rect_i.y == rect.y) return false;
    }
    return true;
}


