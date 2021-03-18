#include <iostream>
#include <SDL.h>

bool isIn(const SDL_Point point, SDL_Rect rect) {
    if (point.x >= rect.x && point.x <= rect.x + rect.w
        && point.y >= rect.y && point.y <= rect.y + rect.h) return true;
    return false;
}

bool playerHitAnEnemy(const SDL_Rect rect, const SDL_Rect* rectt, const int ENEMIES) {
    SDL_Point point[4];
    point[1].x = rect.x;
    point[3].x = rect.x;
    point[0].x = rect.x + rect.w;
    point[2].x = point[0].x;
    point[1].y = rect.y;
    point[2].y = rect.y;
    point[3].y = rect.y + rect.h;
    point[0].y = point[3].y;
    for (int i = 0; i < ENEMIES; i++) {
        for (int j = 0; j < 4; j++)
            if (isIn(point[j], rectt[i])) return true;
    }
    return false;
}

