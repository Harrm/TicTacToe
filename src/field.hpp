#pragma once
#ifndef FIELD_HPP
#define FIELD_HPP
#include "support_structs.hpp"
#include <array>
#include <tuple>
using std::array;
enum class Player {X, O};



class Field {
public:
    enum class CellState {Empty, X, O};
    enum class GameState {Continues, Deadhead, XWin, OWin};

public:
    Field();

    void newGame();
    void selectCell(const Point& cell_coords);
    GameState getGameState() const;
    CellState getCellState(const Point& coords) const;
    const array<array<CellState, 3>, 3>& getCells() const;
    array<CellState, 3> getLine(int index) const;
    array<CellState, 3> getRow(int index) const;
    static constexpr Player nextPlayer(Player player);
    static constexpr Player cellStateToPlayer(CellState state);

private:
    bool checkDeadhead() const;
    std::tuple<bool, Player> checkVictory() const;
    void updateGameState();

    array<array<Field::CellState, 3>, 3> field;
    Player firstPlayer = Player::X;
    Player currentPlayer;
    GameState state;
};

#endif // FIELD_HPP
