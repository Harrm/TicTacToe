#include "window.hpp"
#include <SDL2/SDL.h>
#include "sprite.hpp"



Window::Window() {
    window = SDL_CreateWindow("Game",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              600, 600,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
}



Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}



void Window::startDraw() {
    SDL_RenderClear(renderer);
}



void Window::endDraw() {
    SDL_RenderPresent(renderer);
}



void Window::drawSprite(const Sprite* sprite) {
    sprite->draw();
}



SDL_Renderer* Window::getRenderer() const {
    return renderer;
}



int Window::showMessageBox(const string& title,
                           const string& text,
                           const vector<string>& buttons) const {
    SDL_MessageBoxButtonData buttons_data[buttons.size()];
    for(short c = 0; c < buttons.size(); c++) {
        buttons_data[c] = {
            0,
            c,
            buttons.at(c).c_str()
        };
    }

    SDL_MessageBoxData data = {
        SDL_MESSAGEBOX_INFORMATION,
        window,
        title.c_str(),
        text.c_str(),
        buttons.size(),
        buttons_data,
        nullptr
    };
    int result = 0xCC;
    SDL_ShowMessageBox(&data, &result);
    return result;
}
