#include "Headers/Utils.h"

using namespace std;

void logSDLError(ostream& os,
                 const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
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
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font* &textFont, SDL_Renderer* &renderer) {
    SDL_Surface* textSurface = TTF_RenderText_Solid( textFont, textureText.c_str(), textColor );
    if( textSurface == NULL ) {
        logSDLError(cout, "Unable to render text surface!", true);
    }
    else {
        //Create texture from surface pixels
        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_FreeSurface(textSurface);
        if (texture == NULL) {
            logSDLError(cout, "Unable to create texture from rendered text!", true);
        }
        return texture;
    }
}

void copyText(SDL_Texture* texture, const SDL_Rect &RECT, SDL_Renderer* &renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &RECT);
}


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

void PlaySound(Mix_Music* gMusic) {
    if( Mix_PlayingMusic() == 0 ) {
        Mix_PlayMusic( gMusic, -1 );
    }
    else {
        if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
        else {
            Mix_PauseMusic();
        }
    }
}
