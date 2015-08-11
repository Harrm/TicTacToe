#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <vector>
using std::string;
using std::vector;
class SDL_Renderer;
class SDL_Window;
class Sprite;



class Window {
public:
    Window();
    ~Window();

    void startDraw();
    void endDraw();
    void drawSprite(const Sprite* sprite);

    SDL_Renderer* getRenderer() const;

    int showMessageBox(const string& title,
                       const string& text,
                       const vector<string>& buttons) const;

private:
    void showGameOverMessageBox(const string& result);

    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // WINDOW_HPP
