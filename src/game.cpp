#include "game.hpp"
#include <ctime>
#include <thread>



void Game::run() {    
    while(window.isRunning()) {
        auto start = std::clock()/(double)CLOCKS_PER_SEC;

        window.drawFrame();

        auto end = std::clock()/(double)CLOCKS_PER_SEC;
        auto diff = 1/30.0 - (end - start);
        if(diff > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(uintmax_t(diff*1000)));
        }
    }
}
