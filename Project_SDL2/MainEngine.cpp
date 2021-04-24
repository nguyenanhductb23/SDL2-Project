#include <SDL.h>
#include <SDL_mixer.h>
#include <ctime>
#include "mouse_and_keyboard.h"
#include "Utils.h"
#include "Duc_s_algo.h"
#include "StandardObject.h"
#include "PrintText.h"
#include "LTexture.h"
#include "Sound.h"

void determine(SDL_Window* &window, SDL_Renderer* &renderer, int &score) {
    //printText(renderer);
    LTexture text;

    //SDL_Point point = {50,50};
	//SDL_Point* center = &point;

    //text.loadFromRenderedText(renderer, "Lewy", {255,0,22});//, font, renderer);
    //text.render(renderer, 50, 50, center );
    //text.render(renderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, ( SCREEN_HEIGHT - text.getHeight() ) / 2 );


    Mix_Music* gMusic = Mix_LoadMUS( "beat.wav" );

    PlaySound(gMusic);

    //SDL_Delay(2000);
    const int ENEMIES = 10;
    const int WALLS = 50;
    const int SQ_SIZE = 50;
    Object treasure, Werner, enemy[ENEMIES], wall[WALLS];

    SDL_Surface* image = NULL;

    const SDL_Rect big_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    startMenu(renderer);

    SDL_Event e;

    SDL_Texture* background = loadPNG(renderer, image, "Sky.png");
    SDL_RenderCopy(renderer, background, NULL, &big_rect);

    Werner.setTexture(renderer, image, "Cute.png");
    Werner.setRect(50, 50, SQ_SIZE, SQ_SIZE);

    treasure.setTexture(renderer, image, "Treasure.png");
    treasure.setRect((SQ_SIZE * rand()) % SCREEN_WIDTH + 10,
                      (SQ_SIZE * rand()) % SCREEN_HEIGHT + 15, 30, 20);

    for (int i = 0; i < ENEMIES; i++) {
        enemy[i].setRect(300+50*i, 200+50*i, SQ_SIZE, SQ_SIZE);
        enemy[i].setTexture(renderer, image, "An_enemy.png");
    }

    for (int i = 0; i < WALLS; i++) {
        srand(time(0)+i);
        int x = (SQ_SIZE * rand()) % SCREEN_WIDTH;
        int y = (SQ_SIZE * rand()) % SCREEN_HEIGHT;
        wall[i].setRect(x, y, SQ_SIZE, SQ_SIZE);
        wall[i].setTexture(renderer, image, "Brick.png");
    }

    SDL_RenderPresent(renderer);

    SDL_Rect Wnrect = Werner.getRect();
    //SDL_Texture* Wntexture = Werner.getTexture();
    while (true) {
        if (SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type != SDL_KEYDOWN) continue;
        else {
            KeyboardMove(e, Werner, wall, WALLS);
            for (int i = 0; i < ENEMIES; i++) {
                srand(time(0)+i);
                RandomMove(enemy[i], wall, WALLS);
            }
        }
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, &big_rect);
        treasure.presentPNG(renderer, treasure.getRect());
        Werner.presentPNG(renderer, Werner.getRect());

        for (int i = 0; i < ENEMIES; i++) {
            enemy[i].presentPNG(renderer, enemy[i].getRect());
        }
        for (int i = 0; i < WALLS; i++) {
            wall[i].presentPNG(renderer, wall[i].getRect());
        }
        SDL_RenderPresent(renderer);
        //refreshScreen(renderer, background, Werner, treasure, enemy, ENEMIES, wall, WALLS);
        playerHitAnObject(renderer, Werner, treasure, enemy, ENEMIES, score);
    }
}

