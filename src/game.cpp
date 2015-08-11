#include "game.hpp"
#include <ctime>
#include <thread>
#include <SDL2/SDL.h>



void Game::run() {
    state = State::Field;
    cellBack.reset(new Sprite("../sprites/cell_back.png", window.getRenderer()));
    cellBack->resize({100, 100});
    X.reset(new Sprite("../sprites/X.png", window.getRenderer()));
    X->resize({100, 100});
    O.reset(new Sprite("../sprites/O.png", window.getRenderer()));
    O->resize({100, 100});
    field.newGame();

    while(isRun) {
        auto start = std::clock()/(double)CLOCKS_PER_SEC;

        proccessEvents();

        window.startDraw();
        switch(state) {
        case State::Field:
            renderField();
            break;
        case State::Menu:
            renderMenu();
            break;
        }
        window.endDraw();

        auto end = std::clock()/(double)CLOCKS_PER_SEC;
        auto diff = 1.0/30.0 - (end - start);
        if(diff > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(uintmax_t(diff*1000)));
        }
    }
}



void Game::renderField() {
    for(short c = 0; c < 3; c++) {
        for(short i = 0; i < 3; i++) {
            cellBack->move({150+100*c, 150+100*i});
            cellBack->draw();
            switch(field.getCellState({c, i})) {
            case Field::CellState::X:
                X->move({150+100*c, 150+100*i});
                X->draw();
                break;

            case Field::CellState::O:
                O->move({150+100*c, 150+100*i});
                O->draw();
                break;
            }
        }
    }
}



void Game::renderMenu() {

}



void Game::proccessEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
            proccessPlayerClick({event.button.x, event.button.y});
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                isRun = false;
            }
            break;

        case SDL_QUIT:
            isRun = false;
        }
    }
}



void Game::proccessPlayerClick(const Point& mouseCoords) {
    if(field.getGameState() == Field::GameState::Continues) {
        switch(state) {
        case State::Field:
            for(short c = 0; c < 3; c++) {
                for(short i = 0; i < 3; i++) {
                    Rect butt_rect = {{150+100*c, 150+100*i}, {100, 100}};
                    if(butt_rect.contain(mouseCoords)) {
                        if(field.getCellState({c, i}) == Field::CellState::Empty) {
                            field.selectCell({c, i});
                            goto victory_check;
                        }
                    }
                }
            }
            victory_check:
            if(field.getGameState() != Field::GameState::Continues) {
                string result;
                switch(field.getGameState()) {
                case Field::GameState::Deadhead:
                    result = "Deadhead!";
                    break;
                case Field::GameState::XWin:
                    result = "X victory!";
                    break;
                case Field::GameState::OWin:
                    result = "O victory!";
                    break;
                default:
                    result = "Shit happens";
                    break;
                }

                window.showMessageBox("Game over", result, {"New game"});
                SDL_PumpEvents();
                field.newGame();
            }

            break;
        }
    }
}
