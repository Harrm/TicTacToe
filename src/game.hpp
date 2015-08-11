#pragma once
#ifndef GAME_H
#define GAME_H
#include "window.hpp"
#include "field.hpp"
#include "text_sprite.hpp"
#include <memory>



class Game {
public:
    void run();

private:
    template <typename T>
    using ptr = std::unique_ptr<T>;

    enum class State {Field, Menu};

    void renderField();
    void renderMenu();
    void proccessEvents();
    void proccessPlayerClick(const Point& mouseCoords);

    bool isRun = true;
    ptr<Sprite> background;
    ptr<Sprite> cellBack;
    ptr<Sprite> X;
    ptr<Sprite> O;
    State state;
    Window window;
    Field field;
};

#endif // GAME_H
