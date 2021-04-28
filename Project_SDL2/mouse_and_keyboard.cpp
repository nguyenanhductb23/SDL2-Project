#include "mouse_and_keyboard.h"

using namespace std;

void RandomMove(Object &enemy, const Object* wall, const int &WALLS, int** pos) {
    int step = 50;
    unsigned int dir = rand() % 4;
    SDL_Rect rect = enemy.getRect();
    pos[rect.x / SQ_SIZE][rect.y / SQ_SIZE] --;
    const int LEFT = 0, RIGHT = 1, DOWN = 2, UP = 3;
    switch (dir) {
        case LEFT: rect.x = rect.x - step;
            break;
        case RIGHT: rect.x = rect.x + step;
            break;
        case DOWN: rect.y = rect.y + step;
            break;
        case UP: rect.y = rect.y - step;
            break;
        default: break;
    }
    if (CanMove(rect, wall, WALLS)) {
        enemy.setRect(rect);
    }
    pos[enemy.getRect().x / SQ_SIZE][enemy.getRect().y / SQ_SIZE] ++;
}

void KeyboardMove(SDL_Event &e, Object& Werner, Object* wall, int &WALLS, int** pos) {
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
        case SDLK_SPACE: {
            int x_ = rect.x / SQ_SIZE;
            int y_ = rect.y / SQ_SIZE + 1;
            if (pos[x_][y_] == -1) {
                pos[x_][y_] = 0;
                vector<int> to_destroy(0);
                for (int i = 0; i < WALLS; i++) {
                    if (wall[i].getRect().x == rect.x && wall[i].getRect().y == SQ_SIZE * y_) {
                        to_destroy.push_back(i);
                    }
                }
                for (int i = 0; i < to_destroy.size(); i++) {
                    wall[to_destroy[i]] = wall[WALLS-1];
                    WALLS--;
                }
            }
            break;
        }
        default: break;
    }
    if (CanMove(rect, wall, WALLS))
        Werner.setRect(rect);
}

void startMenu(Media* media) {
    SDL_Event e;
    SDL_Texture* menu_texture = media->start_menu_png;
    SDL_RenderCopy(media->renderer, menu_texture, NULL, &BIG_RECT);
    SDL_RenderPresent(media->renderer);
    Mix_Chunk* ping = media->ping;
    const SDL_Rect PLAY_RECT = {235,200,545,95};
    const SDL_Rect INSTRUCTION_RECT = {235,350,545,90};

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type != SDL_MOUSEBUTTONDOWN || e.button.button != SDL_BUTTON_LEFT) {
                continue;
            }
            SDL_Point mouse_pos = {e.motion.x, e.motion.y};

            if (isIn(mouse_pos, PLAY_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                Play(media);
                return;
            }
            if (isIn(mouse_pos, INSTRUCTION_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                Instruction(media);
                return;
            }
        }
    }
}


void Replay(Media* media, int &score) {
    SDL_Renderer* renderer = media->renderer;
    SDL_Event e;
    Mix_Chunk* ping = media->ping;
    SDL_RenderCopy(renderer, media->game_over_png, NULL, &BIG_RECT);

    const SDL_Rect INSTRUCTION_RECT = {50,310,300,70};
    const SDL_Rect REPLAY_RECT = {370,310,300,70};
    const SDL_Rect QUIT_RECT = {690,310,290,70};

    int high_score = getHighScore();
    string high_score_str = intToString(high_score);
    string your_score_str = intToString(score);
    TTF_Font* font = media->font;
    SDL_Texture* your_score_text = loadFromRenderedText(your_score_str, {255,0,0}, font, renderer);
    SDL_Texture* high_score_text = loadFromRenderedText(high_score_str, {255,0,0}, font, renderer);

    const SDL_Rect YOUR_SCORE_RECT = {540, 135, 25* your_score_str.size(), 45};
    const SDL_Rect HIGH_SCORE_RECT = {540, 200, 25* high_score_str.size(), 45};

    copyText(your_score_text, YOUR_SCORE_RECT, renderer);
    copyText(high_score_text, HIGH_SCORE_RECT, renderer);
    SDL_RenderPresent(renderer);

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type != SDL_MOUSEBUTTONDOWN || e.button.button != SDL_BUTTON_LEFT) {
                continue;
            }
            SDL_Point mouse_pos = {e.motion.x, e.motion.y};

            if (isIn(mouse_pos, REPLAY_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                Play(media);
            }
            if (isIn(mouse_pos, INSTRUCTION_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                Instruction(media);
            }
            if (isIn(mouse_pos, QUIT_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                exit(0);
            }
        }
    }
}

