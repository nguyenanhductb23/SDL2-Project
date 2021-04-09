#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <SDL_ttf.h>
#include "PrintText.h"
#include "StandardObject.h"
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SCREEEEEEEN";
const SDL_Rect big_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};


SDL_Texture* loadPNG(SDL_Renderer* renderer, SDL_Surface* image, const char* path) {
    SDL_Texture* texture = NULL;
    IMG_Init(IMG_INIT_PNG);
    image = IMG_Load(path);
    if (image == NULL)  cerr << "Can't load background. Error: " << SDL_GetError();
    else {
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
    }
    return texture;
}

void presentPNG(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect &rect) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

/**SDL_Texture* loadPNG(SDL_Renderer* renderer, const char* path) {
    SDL_Texture* newTexture = NULL;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
    }
    return newTexture;
}

bool loadMedia(SDL_Renderer* renderer) {
    SDL_Texture* gTexture = NULL;
    bool success = true;
    //Load PNG texture
    gTexture = loadPNG(renderer, "Background.png");
    if (gTexture == NULL) {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    return success;
}*/

void logSDLError(ostream& os,
                 const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(1000);
    }
}

void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* image, SDL_Surface* Wnimg, SDL_Texture* texture, SDL_Texture* Wntexture,
                StandardObject& Werner, const SDL_Rect& treasure, const SDL_Rect* rectt, const int ENEMIES, const SDL_Rect* wall, const int WALLS) {
    SDL_RenderClear(renderer);

    presentPNG(renderer, texture, big_rect);

    //SDL_SetColorKey(Wnimg, SDL_TRUE, SDL_MapRGB( Wnimg->format, 0xFF, 0xFF, 0xFF ) );
    presentPNG(renderer, Wntexture, Werner.getRect());
    //SDL_Texture* texttttt = loadPNG(renderer, "Background.png");
    //Werner.loadPNG(renderer);
    //Werner.Render(renderer, &Wnrect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(renderer, &treasure);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < ENEMIES; i++) {
        SDL_RenderFillRect(renderer, &rectt[i]);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int i = 0; i < WALLS; i++) {
        SDL_RenderFillRect(renderer, &wall[i]);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

void GameOver(SDL_Window* window, SDL_Renderer* renderer, int &score) {
    SDL_SetRenderDrawColor(renderer, 57, 127, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    printText(window, renderer);
    cout << "GAME OVER!!" << endl << "Your score: " << score;
    exit(0);
}

void moveTreasure(SDL_Rect& treasure) {
    treasure.x = rand() % (SCREEN_WIDTH - treasure.w);
    treasure.y = rand() % (SCREEN_HEIGHT - treasure.h);
}
