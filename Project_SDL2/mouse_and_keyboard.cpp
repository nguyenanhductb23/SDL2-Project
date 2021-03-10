#include <iostream>
#include <SDL.h>
#include <ctime>

void mouse(SDL_Window* &window, SDL_Renderer* &renderer)
{
    bool isRunning = true;
    SDL_Event mainEvent;
    while (isRunning) {
        while (SDL_PollEvent(&mainEvent)) {
            time_t timer = clock();
            switch (mainEvent.type) {
                case SDL_QUIT: {
                    isRunning = false;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (mainEvent.button.button == SDL_BUTTON_LEFT) {
                        printf("Left Mouse Clicked\n");
                    }
                    else if (mainEvent.button.button == SDL_BUTTON_RIGHT) {
                        printf("Right Mouse Clicked\n");
                    }
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    std::cout << timer << std::endl;
                    timer = clock() - timer;
                    std::cout << timer;
                    if (mainEvent.button.button == SDL_BUTTON_LEFT) {
                        printf("Left Mouse Released\n");
                    }
                    else if (mainEvent.button.button == SDL_BUTTON_RIGHT) {
                        printf("Right Mouse Released\n");
                    }
                    break;
                }
                case SDL_MOUSEMOTION: {
                    printf("Current Position Mouse: (%d, %d)\n", mainEvent.motion.x, mainEvent.motion.y);
                    break;
                }
                case SDL_MOUSEWHEEL: {
                    printf("Mouse Wheel Motion\n");
                    break;
                }
                case SDL_KEYDOWN: {
                    std::cout << (char)mainEvent.key.keysym.sym << " pressed " << timer << std::endl;
                    break;
                }
                case SDL_KEYUP: {
                    std::cout << (char)mainEvent.key.keysym.sym << " released " << std::endl;
                    break;
                }
                default: break;
            }
        }
    }
}
