#include <iostream>
#include <SDL.h>

#ifndef _Utils_
    #include "Utils.h"
    #define _Utils_ "Utils.h"

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

void playerHitAnEntity(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect rect,
                       SDL_Rect& treasure, const SDL_Rect* rectt, const int ENEMIES) {
    for (int i = 0; i < ENEMIES; i++) {
        if (RectHitsRect(rect, rectt[i])) {
            GameOver(window, renderer);
            return;
        }
    }
    if (RectHitsRect(rect, treasure)) {
        moveTreasure(treasure);
        return;
    }
}

bool hitTheWall(const SDL_Rect rect, const SDL_Rect* rectt, const int ENEMIES, const SDL_Rect* wall, const int WALLS) {
    return true;
}

#endif
