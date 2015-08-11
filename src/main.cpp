#include "game.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



int main() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    Game game;
    game.run();

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
