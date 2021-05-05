#include "Headers/Duc_s_algo.h"

void moveTreasure(const int& mode, Object& treasure, int** pos) {
    SDL_Rect rect = treasure.getRect();
    srand(time(0));
    int x_ = rand() % NUM_OF_SQ_BY_X[mode];
    srand(time(0)+1);
    int y_ = rand() % (NUM_OF_SQ_BY_Y[mode] -1) +1;
    while (pos[x_][y_] == -1) {
        x_ = (x_ + 1) % NUM_OF_SQ_BY_X[mode];
        while (pos[x_][y_] == -1) {
            y_ = (y_ + 1) % (NUM_OF_SQ_BY_Y[mode] -1) +1;
        }
    }
    int x = x_ * SQ_SIZE[mode] + 10;
    int y = y_ * SQ_SIZE[mode] + 15;
    treasure.setRect(x, y, rect.w, rect.h);
}

void freeFalling(Media* media, Object &Werner) {//, Object* wall, const int WALLS) {
    const int FPS = 50;
    SDL_Renderer* renderer = media->renderer;
    SDL_Rect rect = Werner.getRect();
    while (rect.y < SCREEN_HEIGHT) {
        SDL_RenderClear(renderer);
        rect.y += 10;
        Werner.setRect(rect);
        Werner.Render(renderer, Werner.getRect());
        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
}

bool isIn(const SDL_Point& point, const SDL_Rect &rect) {
    if (point.x >= rect.x && point.x <= rect.x + rect.w
        && point.y >= rect.y && point.y <= rect.y + rect.h) return true;
    return false;
}

bool Captured(const int& mode, const Object &Werner, const Object &enemy_i) {
    SDL_Rect w_rect = Werner.getRect();
    SDL_Rect e_rect = enemy_i.getRect();
    SDL_Point w_point[4];
    w_point[0] = {w_rect.x, w_rect.y};
    w_point[1] = {w_rect.x + SQ_SIZE[mode], w_rect.y};
    w_point[2] = {w_rect.x, w_rect.y + SQ_SIZE[mode]};
    w_point[3] = {w_rect.x + SQ_SIZE[mode], w_rect.y + SQ_SIZE[mode]};
    int count = 0;
    for (int j = 0; j < 4; j++) {
        if (isIn(w_point[j], e_rect)) count++;
    }
    if (count >= 2) return true;
    //if (w_rect.x == e_rect.x && w_rect.y == e_rect.y) return true;
    return false;
}

bool RectHitsRect(const SDL_Rect& rect1, const SDL_Rect& rect2) {
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

bool ReachTreasure(const Object& Werner, const Object& treasure) {
    SDL_Point treasure_point = {treasure.getRect().x, treasure.getRect().y};
    if (isIn(treasure_point, Werner.getRect())) {
        return true;
    }
    return false;
}

void playerHitAnObject(Media* media, const int& mode, Object& Werner, Object& treasure,
                       const Object* enemy, int** pos, int& score) {
    const SDL_Rect Wnrect =  Werner.getRect();
    for (int i = 0; i < ENEMIES; i++) {
        if (Captured(mode, Werner, enemy[i])) {
            Mix_PlayChannel( -1, media->bupp, 0 );
            Mix_HaltMusic();
            SDL_RenderPresent(media->renderer);
            SDL_Delay(2000);
            freeFalling(media, Werner);
            GameOver(media, mode, score);
            return;
        }
    }
    if (ReachTreasure(Werner, treasure)) {
        Mix_PlayChannel( -1, media->ping, 0 );
        score += 10;
        moveTreasure(mode, treasure, pos);
        return;
    }
}

bool CanMove(const SDL_Rect& rect, const Object* wall, const int& WALLS) {
    if (rect.x < 0 || rect.x >= SCREEN_WIDTH) return false;
    if (rect.y < 0 || rect.y >= SCREEN_HEIGHT) return false;

    for (int i = 0; i < WALLS; i++) {
        SDL_Rect wall_i = wall[i].getRect();
        if (wall_i.x == rect.x && wall_i.y == rect.y) return false;
    }
    return true;
}

bool CanMove(const int& mode, const SDL_Rect& rect, int** pos) {
    if (rect.x < 0 || rect.x >= SCREEN_WIDTH) return false;
    if (rect.y < 0 || rect.y >= SCREEN_HEIGHT) return false;
    if (rect.y == 0 && rect.x + SQ_SIZE[mode] >= PAUSE_RECT.x) return false;
    int x_ = rect.x / SQ_SIZE[mode];
    int y_ = rect.y / SQ_SIZE[mode];
    if (pos[x_][y_] == -1) return false;
    return true;
}

void GameOver(Media* media, const int& mode, int& score) {
    SDL_RenderPresent(media->renderer);
    SDL_Delay(1000);
    int* high_score = new int [NUM_OF_MODES];
    high_score = getHighScore();
    if (score > high_score[mode]) {
        high_score[mode] = score;
        setHighScore(high_score);
    }
    delete high_score;
    playAgain(media, mode, score);
}

string intToString(const int &num) {
    if (num == 0) return "0";
    int tmp = num;
    string str = "";
    while (tmp > 0) {
        int dig = tmp % 10;
        str = (char)(dig + 48) + str;
        tmp /= 10;
    }
    return str;
}

bool isIn(const SDL_Point& point, const Object* objs, const int& NUM_OF_OBJS, int& i) {
    //i là chỉ số của object có chứa điểm point
    for (int j = 0; j < NUM_OF_OBJS; j++)
        if (isIn(point, objs[j].getRect())) {
            i = j;
            return true;
        }
    return false;
}

void laserShoot(Media* media, const int& mode, SDL_Renderer* renderer, SDL_Point& des,
                const Object& Werner, Object* wall, int& WALLS, int** pos) {
    SDL_Rect rect = Werner.getRect();
    Point laser_point(rect.x + SQ_SIZE[mode]*4/5,  rect.y + SQ_SIZE[mode]*3/5);
    SDL_Point appr = {laser_point.x, laser_point.y};
    int dif_x = des.x - laser_point.x;
    int dif_y = des.y - laser_point.y;
    if (dif_x == 0 && dif_y == 0) return;
    double vx = 0, vy = 0;
    if (abs(dif_x) >= abs(dif_y)) {
        vx = 5.0;
        vy = abs(vx / dif_x * dif_y);
    }
    else {
        vy = 5.0;
        vx = abs(vy / dif_y * dif_x);
    }
    if (dif_x < 0) vx = -vx;
    if (dif_y < 0) vy = -vy;
    int i = -1;
    while (!isIn(appr, wall, WALLS, i) && isIn(appr, BIG_RECT)) {
        laser_point.x += vx;
        laser_point.y += vy;
        appr = {(int)(laser_point.x), (int)(laser_point.y)};
    }
    Werner.Render(renderer, Werner.getRect());
    SDL_RenderDrawLine(renderer, rect.x + SQ_SIZE[mode]*4/5, rect.y + SQ_SIZE[mode]*3/5, laser_point.x, laser_point.y);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    if (i != -1) {
        Mix_PlayChannel(-1, media->explode, 0);
        int x_ = wall[i].getRect().x / SQ_SIZE[mode];
        int y_ = wall[i].getRect().y / SQ_SIZE[mode];
        pos[x_][y_] = 0;
        wall[i] = wall[WALLS-1];
        WALLS--;
    }
}


