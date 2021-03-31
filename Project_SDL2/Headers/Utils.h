void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void loadBackground(SDL_Renderer*, const char*, SDL_Rect);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void VeHinh(SDL_Window* window, SDL_Renderer* renderer);

void refreshScreen(SDL_Window*, SDL_Renderer*, const SDL_Rect&, const SDL_Rect&,
                   const SDL_Rect*, const int, const SDL_Rect*, const int);

bool loadMedia();

void moveTreasure(SDL_Rect&);

void GameOver(SDL_Window*, SDL_Renderer*, int &);
