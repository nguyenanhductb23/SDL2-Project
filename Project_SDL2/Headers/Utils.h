void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void setBkg(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* bkg);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

void VeHinh(SDL_Window* window, SDL_Renderer* renderer);

void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect, const SDL_Rect* rectt, const int ENEMIES);

bool loadMedia();

void GameOver(SDL_Window* window, SDL_Renderer* renderer);
