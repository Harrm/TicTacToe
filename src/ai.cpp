#include "ai.hpp"
#include <random>

Ai::Ai(Player ai_player, Field* field):
    ai(ai_player) {


}



void Ai::makeTurn() {
    vector<Point> turns(getVictoryCells(ai));
    if(turns.size() > 0) {
        field->selectCell(turns.at(0));
        return ;
    }

    turns = getVictoryCells(Field::nextPlayer(ai));
    if(turns.size() > 0) {
        field->selectCell(turns.at(0));
        return ;
    }

    turns = getPins(ai);
    if(turns.size() > 0) {
        field->selectCell(turns.at(0));
        return;
    }

    turns = getPins(Field::nextPlayer(ai));
    if(turns.size() > 0) {
        field->selectCell(turns.at(0));
        return;
    }

    std::random_device r;
    vector<Point> freeCells;
    for(short c = 0; c < 3; c++) {
        for(short i = 0; i < 3; i++) {
            if(field->getCellState({c, i}) == Field::CellState::Empty) {
                freeCells.push_back({c, i});
            }
        }
    }

    field->selectCell(freeCells.at(r()%freeCells.size()));
}



bool Ai::checkFieldPointerValid() const {
    return (field == nullptr);
}



vector<Point>&& Ai::getVictoryCells(Player winner) const {
    vector<Point> victoryCells;



    return std::move(victoryCells);
}



vector<Point>&& Ai::getVictoryCellsInLines(Player winner) const {
    vector<Point> victoryCells;

    for(short c = 0; c < 3; c++) {
        char cellsToVictory = 3;

        for(auto cell: field->getLine(c)) {
            if(Field::cellStateToPlayer(cell) == winner) {
                cellsToVictory--;
            }
        }

        if(cellsToVictory == 1) {
            for(short i = 0; i < 3; i++) {
                if(field->getCellState({c, i}) == Field::CellState::Empty) {
                    victoryCells.push_back({c, i});
                }
            }
        }
    }

    return std::move(victoryCells);
}



vector<Point>&& Ai::getVictoryCellsInRows(Player winner) const {
    vector<Point> victoryCells;

    for(short c = 0; c < 3; c++) {
        char cellsToVictory = 3;

        for(auto cell: field->getRow(c)) {
            if(Field::cellStateToPlayer(cell) == winner) {
                cellsToVictory--;
            }
        }

        if(cellsToVictory == 1) {
            for(short i = 0; i < 3; i++) {
                if(field->getCellState({i, c}) == Field::CellState::Empty) {
                    victoryCells.push_back({i, c});
                }
            }
        }
    }

    return std::move(victoryCells);
}



vector<Point>&& Ai::getVictoryCellsInDiagonals(Player winner) const {
    vector<Point> victoryCells;
    int rightDiagonalCellsToVictory = 3;
    int leftDiagonalCellsToVictory = 3;

    for(short c = 0; c < 3; c++) {
        if(Field::cellStateToPlayer(field->getLine(c).at(2-c)) == winner) {
            rightDiagonalCellsToVictory--;
        }
        if(Field::cellStateToPlayer(field->getLine(c).at(c)) == winner) {
            leftDiagonalCellsToVictory--;
        }
    }
    if(rightDiagonalCellsToVictory)

    return std::move(victoryCells);
}



vector<Point>&& Ai::getPins(Player pinner) const {

}



vector<Point>&& Ai::getTrianglePins(Player pinner) const {

}



vector<Point>&& Ai::getArrowPins(Player pinner) const {

}



vector<Point>&& Ai::getPyramidPins(Player pinner) const {

}



vector<Point>&& Ai::getAnglePins(Player pinner) const {

}
