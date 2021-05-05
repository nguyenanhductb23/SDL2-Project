#include "Headers/StandardObject.h"

Object::Object() {
    texture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

void Object::setTexture(SDL_Renderer* renderer, SDL_Surface* image, const char* path) {
    IMG_Init(IMG_INIT_PNG);
    image = IMG_Load(path);
    if (image == NULL)  std::cerr << "Can't load image. Error: " << SDL_GetError();
    else {
        SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB( image->format, 0xFF, 0xFF, 0xFF ) );
        this->texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
    }
}

void Object::setTexture(SDL_Texture* loaded_texture) {
    this->texture = loaded_texture;
}

void Object::Render(SDL_Renderer* renderer, const SDL_Rect &rect) const {
    SDL_RenderCopy(renderer, this->texture, NULL, &rect);
}

void Object::setRect(const int& x, const int& y, const int& w, const int& h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Object::setRect(const SDL_Rect& _rect) {
    rect.x = _rect.x;
    rect.y = _rect.y;
    rect.w = _rect.w;
    rect.h = _rect.h;
}

Object::~Object() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}
