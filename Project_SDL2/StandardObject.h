#ifndef _STANDARD_OBJECT_
#define _STANDARD_OBJECT_

#include <SDL.h>
#include <SDL_image.h>

class StandardObject {
    SDL_Texture* texture;
    SDL_Rect rect;
public:
    StandardObject();
    ~StandardObject();
    //StandardObject(string, int, int, int, int);
    SDL_Rect getRect() {return rect;}
    SDL_Texture* getTexture() {return texture;}
    void setRect(const int&, const int&, const int&, const int&);
    SDL_Texture* loadPNG(SDL_Renderer*, SDL_Surface*, const char*);
    void presentPNG(SDL_Renderer*, SDL_Texture*, const SDL_Rect&);
    void Free();
    void Render(SDL_Renderer*, const SDL_Rect*);
};

#endif
