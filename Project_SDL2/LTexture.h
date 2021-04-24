#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

class LTexture {
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile(string path, SDL_Renderer* &gRenderer);

        //Creates image from font string
        bool loadFromRenderedText(SDL_Renderer* &gRenderer, string textureText, SDL_Color textColor );

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Renders texture at given point
        void render(SDL_Renderer* &gRenderer, int x, int y, SDL_Point* center, const SDL_Rect* clip = NULL, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Gets image dimensions
        int getWidth();
        int getHeight();
        SDL_Texture* get_mTexture();

    //private:
        //The actual hardware texture
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};
