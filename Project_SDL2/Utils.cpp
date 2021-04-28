#include "Utils.h"

using namespace std;

SDL_Texture* loadPNG(SDL_Renderer* renderer, SDL_Surface* image, const char* path) {
    SDL_Texture* texture = NULL;
    image = IMG_Load(path);
    if (image == NULL)  cerr << "Couldn't load background. Error: " << SDL_GetError();
    else {
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
    }
    return texture;
}

SDL_Texture* loadPNG_KeyColor(SDL_Renderer* renderer, SDL_Surface* image, const char* path) {
    SDL_Texture* texture = NULL;
    image = IMG_Load(path);
    if (image == NULL)  cerr << "Couldn't load background. Error: " << SDL_GetError();
    else {
        SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB( image->format, 0xFF, 0xFF, 0xFF ) );
        texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
    }
    return texture;
}

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

    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
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



/*void loadSound() {
    Mix_Music*
}*/


