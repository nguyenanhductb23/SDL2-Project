#include "MainEngine.h"

void Play(Media* media, const int& mode) {
    SDL_Renderer* renderer = media->renderer;
    int score = 0;
    SDL_Texture* score_text = NULL;
    SDL_Point mouse_pos = {0, 0};
    int WALLS = MAX_WALLS[mode];
    Object treasure, Werner, enemy[ENEMIES], wall[WALLS];
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

    int** pos = new int* [NUM_OF_SQ_BY_X[mode]];
    for (int i = 0; i < NUM_OF_SQ_BY_X[mode]; i++) {
        pos[i] = new int [NUM_OF_SQ_BY_Y[mode]];
        for (int j = 0; j < NUM_OF_SQ_BY_Y[mode]; j++)
            pos[i][j] = 0;
    }

    PlaySound(media->music);
    SDL_RenderCopy(renderer, media->background_png, NULL, &BIG_RECT);

    Werner.setTexture(media->Werner_png);
    Werner.setRect(0, 0, SQ_SIZE[mode], SQ_SIZE[mode]);

    treasure.setTexture(media->treasure_png);
    treasure.setRect(610, 10, 30, 20);

    for (int i = 0; i < WALLS; i++) {
        int x = 0, y = 0;
        do {
            srand(time(0)+i*20);
            x = rand() % (SCREEN_WIDTH / SQ_SIZE[mode]);
            y = rand() % (SCREEN_HEIGHT / SQ_SIZE[mode] - 1) + 1;
        } while (pos[x][y] == -1);

        wall[i].setRect(x* SQ_SIZE[mode], y* SQ_SIZE[mode], SQ_SIZE[mode], SQ_SIZE[mode]);
        wall[i].setTexture(media->wall_png);
        pos[x][y] = -1;
    }

    for (int i = 0; i < ENEMIES; i++) {
        int x = 6 + i;
        int y = 4 + i;
        while (pos[x][y] < 0) {
            if (x+1 == NUM_OF_SQ_BY_X[mode]) {
                y++;        x = 0;
            }
            else x++;
        }
        pos[x][y] = 1;
        enemy[i].setRect(x*SQ_SIZE[mode], y*SQ_SIZE[mode], SQ_SIZE[mode], SQ_SIZE[mode]);
        enemy[i].setTexture(media->enemy_png);
    }
    SDL_RenderPresent(renderer);

///MAIN LOOP--------------------------------------------------------
    SDL_Event e;
    if (e.type == SDL_QUIT) exit(0);

    while (true) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, media->background_png, NULL, &BIG_RECT);
        SDL_RenderFillRect(renderer, &GREEN_RECT);
        SDL_RenderCopy(renderer, media->pause_button_png, NULL, &PAUSE_RECT);
        treasure.Render(renderer, treasure.getRect());

        for (int i = 0; i < ENEMIES; i++) {
            srand(time(0)+i);
            RandomMove(mode, enemy[i], wall, WALLS, pos);
            SDL_Delay(20);
            enemy[i].Render(renderer, enemy[i].getRect());
        }
        for (int k = 0; k < NUM_OF_SQ_BY_X[mode]; k++)
            for (int j = 0; j < NUM_OF_SQ_BY_Y[mode]; j++)
                if (pos[k][j] >= 2) {
                    SDL_Texture* text = loadFromRenderedText(intToString(pos[k][j]), {255,0,255}, media->font, renderer);
                    SDL_Rect rect = {SQ_SIZE[mode] * k, SQ_SIZE[mode] * j, 10, 18};
                    copyText(text, rect, renderer);
                }


        for (int i = 0; i < WALLS; i++) {
            wall[i].Render(renderer, wall[i].getRect());
        }

        score_text = loadFromRenderedText("Score: "+ intToString(score), {255,200,200}, media->font, renderer);
        copyText(score_text, SCORE_RECT, renderer);

        while (SDL_PollEvent(&e)) {
            mouse_pos = {e.motion.x, e.motion.y};
            if (e.type == SDL_MOUSEBUTTONDOWN && isIn(mouse_pos, PAUSE_RECT)) {
                pauseMenu(media, score);
            }
            else {
                KeyboardMove(mode, e, Werner, wall, WALLS, pos);
                if (e.type == SDL_MOUSEBUTTONDOWN && score > 0) {
                    SDL_Point des = {e.motion.x, e.motion.y};
                    score--;
                    laserShoot(media, mode, renderer, des, Werner, wall, WALLS, pos);
                }
            }
        }
        Werner.Render(renderer, Werner.getRect());
        SDL_RenderPresent(renderer);
        playerHitAnObject(media, mode, Werner, treasure, enemy, pos, score);
    }
//------------------------------------------------------------------------
    for (int i = 0; i < NUM_OF_SQ_BY_X[mode]; i++) {
        delete []pos[i];
    }
    delete []pos;
}

