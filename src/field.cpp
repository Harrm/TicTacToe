#include "field.hpp"
#include <stdexcept>



Field::Field() {
    for(auto& c: field) {
        c.fill(CellState::Empty);
    }
}



void Field::newGame() {
    state = GameState::Continues;

    for(auto& c: field) {
        c.fill(CellState::Empty);
    }
    firstPlayer = nextPlayer(firstPlayer);
    currentPlayer = firstPlayer;
}



void Field::selectCell(const Point& cell_coords) {
    if(cell_coords.x > 2 or cell_coords.y > 2 or
       cell_coords.x < 0 or cell_coords.y < 0) {
        std::invalid_argument e("Coords out of field");
        throw e;
    }

    auto& cell = field.at(cell_coords.x).at(cell_coords.y);

    switch(cell) {
    case CellState::Empty:
        cell = (currentPlayer == Player::X) ? CellState::X : CellState::O;
        currentPlayer = nextPlayer(currentPlayer);
        updateGameState();
        break;

    case CellState::X:case CellState::O:
        std::invalid_argument e("Cell is occupied");
        throw e;
        break;
    }
}



Field::GameState Field::getGameState() const {
    return state;
}



bool Field::checkDeadhead() const {
    short emptyCellsCount = 9;

    for(auto& line: field) {
        for(auto& cell: line) {
            if(cell != CellState::Empty) {
                emptyCellsCount--;
            }
        }
    }
    if(emptyCellsCount == 0) {
        return true;
    }
    return false;
}



std::tuple<bool, Player> Field::checkVictory() const {
    Player winner;
    bool isVictory = false;

    for(short c = 0; c < 3; c++) {
        auto line = getLine(c);
        if(line[0] != CellState::Empty and
           line[0] == line [1] and
           line[1] == line[2]) {
            return std::make_tuple(true, cellStateToPlayer(line[0]));
        }

        auto row = getRow(c);
        if(row[0] != CellState::Empty and
           row[0] == row[1] and
           row[1] == row[2]) {
            return std::make_tuple(true, cellStateToPlayer(row[0]));
        }
    }

    if((field[1][1] != CellState::Empty) and
       ((field[0][0] == field[2][2] and
         field[0][0] == field[1][1]) or
        (field[0][2] == field[2][0] and
         field[0][2] == field[1][1]))) {
        return std::make_tuple(true, cellStateToPlayer(field[1][1]));
    }

    return std::make_tuple(false, Player());
}



void Field::updateGameState() {
    auto victoryCheckResult = checkVictory();
    if(std::get<0>(victoryCheckResult) == true) {
        state = (std::get<1>(victoryCheckResult) == Player::X)
                 ? GameState::XWin
                 : GameState::OWin;

    } else if(checkDeadhead()) {
        state = GameState::Deadhead;

    } else {
        state = GameState::Continues;
    }
}



Field::CellState Field::getCellState(const Point& coords) const {
    return field.at(coords.x).at(coords.y);
}



const array<array<Field::CellState, 3>, 3>& Field::getCells() const {
    return field;
}



array<Field::CellState, 3> Field::getLine(int index) const {
    return field.at(index);
}



array<Field::CellState, 3> Field::getRow(int index) const {
    array<Field::CellState, 3> row;
    for(short c = 0; c < 3; c++) {
        row.at(c) = field.at(c).at(index);
    }
    return row;
}



constexpr Player Field::nextPlayer(Player player) {
    return (player == Player::X) ? Player::O : Player::X;
}



constexpr Player Field::cellStateToPlayer(CellState state) {
    return (state == CellState::X) ? Player::X : Player::O;
}
