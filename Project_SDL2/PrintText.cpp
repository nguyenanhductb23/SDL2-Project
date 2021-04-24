#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Utils.h"

using namespace std;

//TTF_Font* TTF_OpenFont(const char *file, int ptsize);

/**void printText(SDL_Renderer* renderer) {
    TTF_Font* Sans = TTF_OpenFont("Font.ttf", 20); //this opens a font style and sets a size

    SDL_Color White = {0xFF, 0xFF, 0xFF};

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Lewangoalski!!!!!!", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect;
    Message_rect.x = 20;
    Message_rect.y = 20;
    Message_rect.w = 100;
    Message_rect.h = 100;
    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
    SDL_Delay(2000);
}



void loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font* &textFont, SDL_Renderer* &renderer)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( textFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        logSDLError(cout, "Unable to render text surface!", true);
    }
    else
    {
        //Create texture from surface pixels
        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == NULL )
        {
            logSDLError(cout, "Unable to create texture from rendered text!", true);
        }
        else
        {
            //Get image dimensions
            int width = textSurface->w;
            int height = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
        SDL_Delay(2000);
    }
}*/
