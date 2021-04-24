#include <SDL_ttf.h>

void printText(SDL_Renderer*);

void loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* &textFont, SDL_Renderer* &renderer);
