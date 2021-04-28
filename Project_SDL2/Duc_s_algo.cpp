#include "Duc_s_algo.h"

void moveTreasure(Object& treasure, int** pos) {
    SDL_Rect rect = treasure.getRect();
    srand(time(0));
    int x_ = rand() % NUM_OF_SQ_BY_X;
    srand(time(0)+1);
    int y_ = rand() % NUM_OF_SQ_BY_Y;
    while (pos[x_][y_] == -1) {
        x_ = (x_ + 1) % NUM_OF_SQ_BY_X;
        while (pos[x_][y_] == -1) {
            y_ = (y_ + 1) % NUM_OF_SQ_BY_Y;
        }
    }
    int x = x_ * SQ_SIZE + 10;
    int y = y_ * SQ_SIZE + 15;
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
        Werner.presentPNG(renderer, Werner.getRect());
        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
}

bool isIn(const SDL_Point point, const SDL_Rect &rect) {
    if (point.x >= rect.x && point.x <= rect.x + rect.w
        && point.y >= rect.y && point.y <= rect.y + rect.h) return true;
    return false;
}

bool Captured(const Object &Werner, const Object &enemy_i) {
    SDL_Rect w_rect = Werner.getRect();
    SDL_Rect e_rect = enemy_i.getRect();
    SDL_Point w_point[4];
    w_point[0] = {w_rect.x, w_rect.y};
    w_point[1] = {w_rect.x + SQ_SIZE, w_rect.y};
    w_point[2] = {w_rect.x, w_rect.y + SQ_SIZE};
    w_point[3] = {w_rect.x + SQ_SIZE, w_rect.y + SQ_SIZE};
    int count = 0;
    for (int j = 0; j < 4; j++) {
        if (isIn(w_point[j], e_rect)) count++;
    }
    if (count >= 2) return true;
    //if (w_rect.x == e_rect.x && w_rect.y == e_rect.y) return true;
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

bool ReachTreasure(const Object &obj, const Object &treasure) {
    SDL_Point treasure_point = {treasure.getRect().x, treasure.getRect().y};
    if (isIn(treasure_point, obj.getRect())) return true;
    return false;
}

void playerHitAnObject(Media* media, Object& Werner, Object& treasure,
                       const Object* enemy, int** pos, int &score) {
    const SDL_Rect Wnrect =  Werner.getRect();
    for (int i = 0; i < ENEMIES; i++) {
        if (Captured(Werner, enemy[i])) {
            Mix_PlayChannel( -1, media->bupp, 0 );
            Mix_HaltMusic();
            SDL_Delay(2000);
            freeFalling(media, Werner);
            GameOver(media, score);
            return;
        }
    }
    if (ReachTreasure(Werner, treasure)) {
        Mix_PlayChannel( -1, media->ping, 0 );
        score++;
        moveTreasure(treasure, pos);
        return;
    }
}

bool CanMove(const SDL_Rect &rect, const Object* wall, const int &WALLS) {
    if (rect.x < 0 || rect.x >= SCREEN_WIDTH) return false;
    if (rect.y < 0 || rect.y >= SCREEN_HEIGHT) return false;

    for (int i = 0; i < WALLS; i++) {
        SDL_Rect wall_i = wall[i].getRect();
        if (wall_i.x == rect.x && wall_i.y == rect.y) return false;
    }
    return true;
}

void GameOver(Media* media, int &score) {
    SDL_RenderPresent(media->renderer);
    SDL_Delay(1000);
    std::cout << "GAME OVER!!" << std::endl << "Your score: " << score << std::endl;
    int high_score = getHighScore();
    if (score > high_score) {
        cerr << std::endl << "New high score!!!!!";
        setHighScore(score);
    }
    Replay(media, score);
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

void Instruction(Media* media) {
    const SDL_Rect RECT = {0,0,1000,600};
    SDL_Event e;
    Mix_Chunk* ping = media->ping;
    SDL_Texture* menu_texture = media->instruction_png;
    SDL_RenderCopy(media->renderer, menu_texture, NULL, &BIG_RECT);
    SDL_RenderPresent(media->renderer);
    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type != SDL_MOUSEBUTTONDOWN || e.button.button != SDL_BUTTON_LEFT) {
                continue;
            }
            SDL_Point mouse_pos = {e.motion.x, e.motion.y};

            if (isIn(mouse_pos, RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                startMenu(media);
                Play(media);
            }
        }
    }
}

