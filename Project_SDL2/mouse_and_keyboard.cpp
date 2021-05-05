#include "Headers/mouse_and_keyboard.h"

using namespace std;

void RandomMove(const int& mode, Object& enemy, const Object* wall, const int& WALLS, int** pos) {
    int step = SQ_SIZE[mode];
    unsigned int dir = rand() % 4;
    SDL_Rect rect = enemy.getRect();
    pos[rect.x / SQ_SIZE[mode]][rect.y / SQ_SIZE[mode]] --;
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
    }
    //if (CanMove(rect, wall, WALLS)) {
    if (CanMove(mode, rect, pos)) {
        enemy.setRect(rect);
    }
    pos[enemy.getRect().x / SQ_SIZE[mode]][enemy.getRect().y / SQ_SIZE[mode]] ++;
}

void KeyboardMove(const int& mode, SDL_Event &e, Object& Werner, Object* wall, int &WALLS, int** pos) {
    SDL_Rect rect = Werner.getRect();
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT: rect.x = rect.x - SQ_SIZE[mode];
                break;
            case SDLK_RIGHT: rect.x = rect.x + SQ_SIZE[mode];
                break;
            case SDLK_DOWN: rect.y = rect.y + SQ_SIZE[mode];
                break;
            case SDLK_UP: rect.y = rect.y - SQ_SIZE[mode];
                break;
            default: break;
        }
    }
    //if (CanMove(rect, wall, WALLS))
    if (CanMove(mode, rect, pos)) {
        Werner.setRect(rect);
    }
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
                int mode = chooseMode(media);
                Play(media, mode);
                return;
            }
            if (isIn(mouse_pos, INSTRUCTION_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                Instruction(media);
            }
        }
    }
}


void playAgain(Media* media, const int& mode, const int& score) {
    SDL_Renderer* renderer = media->renderer;
    SDL_Event e;
    Mix_Chunk* ping = media->ping;
    SDL_RenderCopy(renderer, media->game_over_png, NULL, &BIG_RECT);

    const SDL_Rect MAIN_MENU_RECT = {50,310,300,70};
    const SDL_Rect PLAY_AGAIN_RECT = {370,310,300,70};
    const SDL_Rect QUIT_RECT = {690,310,290,70};

    int* high_score = new int [NUM_OF_MODES];
    high_score = getHighScore();
    string high_score_str = intToString(high_score[mode]);
    string your_score_str = intToString(score);
    delete high_score;
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

            if (isIn(mouse_pos, PLAY_AGAIN_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                int mode = chooseMode(media);
                Play(media, mode);
            }
            if (isIn(mouse_pos, MAIN_MENU_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                startMenu(media);
            }
            if (isIn(mouse_pos, QUIT_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                exit(0);
            }
        }
    }
}

void pauseMenu(Media* media, const int& score) {
    SDL_Event e;
    SDL_Renderer* renderer = media->renderer;
    SDL_Texture* menu_texture = media->pause_png;
    SDL_RenderCopy(media->renderer, menu_texture, NULL, &BIG_RECT);
    SDL_RenderPresent(renderer);
    Mix_Chunk* ping = media->ping;
    const SDL_Rect MAIN_MENU_RECT = {50,310,300,70};
    const SDL_Rect RESUME_RECT = {370,310,300,70};
    const SDL_Rect QUIT_RECT = {690,310,290,70};

    string your_score_str = intToString(score);
    TTF_Font* font = media->font;

    SDL_Texture* your_score_text = loadFromRenderedText(your_score_str, {255,0,0}, font, renderer);
    const SDL_Rect YOUR_SCORE_RECT = {540, 155, 25* your_score_str.size(), 45};
    copyText(your_score_text, YOUR_SCORE_RECT, renderer);

    SDL_RenderPresent(renderer);

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type != SDL_MOUSEBUTTONDOWN || e.button.button != SDL_BUTTON_LEFT) {
                continue;
            }
            SDL_Point mouse_pos = {e.motion.x, e.motion.y};

            if (isIn(mouse_pos, RESUME_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                return;
            }
            if (isIn(mouse_pos, MAIN_MENU_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                startMenu(media);
                return;
            }
            if (isIn(mouse_pos, QUIT_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                exit(0);
            }
        }
    }
}


void Instruction(Media* media) {
    SDL_Event e;
    Mix_Chunk* ping = media->ping;
    SDL_Texture* menu_texture = media->instruction_png;
    SDL_Texture* menu_texture2 = media->instruction2_png;
    SDL_RenderCopy(media->renderer, menu_texture, NULL, &BIG_RECT);
    SDL_RenderPresent(media->renderer);
    SDL_Delay(5000);
    SDL_RenderCopy(media->renderer, menu_texture2, NULL, &BIG_RECT);
    SDL_RenderPresent(media->renderer);
    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type != SDL_MOUSEBUTTONDOWN || e.button.button != SDL_BUTTON_LEFT) {
                continue;
            }
            SDL_Point mouse_pos = {e.motion.x, e.motion.y};
            if (isIn(mouse_pos, BIG_RECT)) {
                Mix_PlayChannel( -1, ping, 0 );
                startMenu(media);
            }
        }
    }
}

int chooseMode(Media* media) {
    SDL_Renderer* renderer = media->renderer;
    SDL_Event e;
    const SDL_Rect BUTTON_RECT[3] = { {50,250,300,150}, {370,250,300,150}, {690,250,265,150} };
    const SDL_Rect TEXT_RECT = {400, 500, 280, 35};
    SDL_RenderCopy(renderer, media->choose_mode_png, NULL, &BIG_RECT);
    SDL_RenderPresent(renderer);

    while (true) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type != SDL_MOUSEBUTTONDOWN || e.button.button != SDL_BUTTON_LEFT) {
                continue;
            }
            SDL_Point mouse_pos = {e.motion.x, e.motion.y};

            for (int i = 0; i < 3; i++) {
                if (isIn(mouse_pos, BUTTON_RECT[i])) {
                    Mix_PlayChannel( -1, media->ping, 0 );
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                    SDL_RenderDrawRect(renderer, &BUTTON_RECT[i]);
                    SDL_Texture* text = loadFromRenderedText("Loading, please wait ...", {255,0,0}, media->font, renderer);
                    copyText(text, TEXT_RECT, renderer);
                    SDL_RenderPresent(renderer);
                    return i;
                }
            }
        }
    }
}

