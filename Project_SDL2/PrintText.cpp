#include "PrintText.h"

SDL_Texture* loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font* &textFont, SDL_Renderer* &renderer) {
    SDL_Surface* textSurface = TTF_RenderText_Solid( textFont, textureText.c_str(), textColor );
    if( textSurface == NULL ) {
        logSDLError(cout, "Unable to render text surface!", true);
    }
    else {
        //Create texture from surface pixels
        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_FreeSurface(textSurface);
        if( texture == NULL ) {
            logSDLError(cout, "Unable to create texture from rendered text!", true);
        }
        return texture;
    }
}

void copyText(SDL_Texture* texture, const SDL_Rect &RECT, SDL_Renderer* &renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &RECT);
}
