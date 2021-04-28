#include "MainEngine.h"

void Play(Media* media) {
    SDL_Renderer* renderer = media->renderer;
    int score = 0;
    int WALLS = 60;
    Object treasure, Werner, enemy[ENEMIES], wall[WALLS];

    int** pos = new int* [NUM_OF_SQ_BY_X];
    for (int i = 0; i < NUM_OF_SQ_BY_X; i++) {
        pos[i] = new int [NUM_OF_SQ_BY_Y];
        for (int j = 0; j < NUM_OF_SQ_BY_Y; j++)
            pos[i][j] = 0;
    }

    PlaySound(media->music);
    SDL_RenderCopy(renderer, media->background_png, NULL, &BIG_RECT);

    Werner.setTexture(media->Werner_png);
    Werner.setRect(0, 0, SQ_SIZE, SQ_SIZE);

    treasure.setTexture(media->treasure_png);
    treasure.setRect(765, 10, 30, 20);

    for (int i = 0; i < WALLS; i++) {
        srand(time(0)+i*20);
        int x = (SQ_SIZE * rand()) % SCREEN_WIDTH;
        int y = (rand() % (SCREEN_HEIGHT / SQ_SIZE - 1) + 1) * SQ_SIZE;
        wall[i].setRect(x, y, SQ_SIZE, SQ_SIZE);
        wall[i].setTexture(media->wall_png);
        pos[x/SQ_SIZE][y/SQ_SIZE] = -1;
    }

    for (int i = 0; i < ENEMIES; i++) {
        int x = 6 + i;
        int y = 4 + i;
        while (pos[x][y] == -1) {
            if (x >= NUM_OF_SQ_BY_X - 1) {
                y++;        x = 0;
            }
            else x++;
        }
        enemy[i].setRect(x*SQ_SIZE, y*SQ_SIZE, SQ_SIZE, SQ_SIZE);
        enemy[i].setTexture(media->enemy_png);
    }
    SDL_RenderPresent(renderer);

///MAIN LOOP--------------------------------------------------------
    SDL_Event e;
    while (true) {
        if (e.type == SDL_QUIT) exit(0);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, media->background_png, NULL, &BIG_RECT);
        treasure.presentPNG(renderer, treasure.getRect());

        for (int i = 0; i < ENEMIES; i++) {
            srand(time(0)+i);
            RandomMove(enemy[i], wall, WALLS, pos);
            SDL_Delay(10);
            enemy[i].presentPNG(renderer, enemy[i].getRect());

            for (int i = 0; i < NUM_OF_SQ_BY_X; i++)
                for (int j = 0; j < NUM_OF_SQ_BY_Y; j++)
                    if (pos[i][j] >= 2) {
                        SDL_Texture* text = loadFromRenderedText(intToString(pos[i][j]), {255,0,255}, media->font, renderer);
                        SDL_Rect rect = {SQ_SIZE * i, SQ_SIZE * j, 10, 18};
                        copyText(text, rect, renderer);
                    }
        }

        while (SDL_PollEvent(&e)) {
            if (SDL_WaitEvent(&e) == 0) continue;
            else {
                KeyboardMove(e, Werner, wall, WALLS, pos);
            }
        }

        Werner.presentPNG(renderer, Werner.getRect());

        for (int i = 0; i < WALLS; i++) {
            wall[i].presentPNG(renderer, wall[i].getRect());
        }

        SDL_Texture* score_text = loadFromRenderedText("Score: "+ intToString(score), {255,200,200}, media->font, renderer);
        SDL_Rect score_rect = {880, 10, 100, 20};
        copyText(score_text, score_rect, renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        playerHitAnObject(media, Werner, treasure, enemy, pos, score);
    }
///------------------------------------------------------------------------
    for (int i = 0; i < NUM_OF_SQ_BY_X; i++) {
        delete []pos[i];
    }
    delete []pos;
}

