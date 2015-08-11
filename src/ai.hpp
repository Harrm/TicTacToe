#pragma once
#ifndef AI_HPP
#define AI_HPP
#include <vector>
#include "support_structs.hpp"
#include "field.hpp"
using std::vector;



class Ai {
public:
    enum class Difficult {Easy, Mediun, Hard};

public:
    Ai(Player ai_player, Field* field);
    void setField(Field* field);
    void setPlayer(Player player);
    void setDifficult(Difficult new_difficult);

    void makeTurn();

private:
    bool checkFieldPointerValid() const;

    vector<Point>&& getVictoryCells(Player winner) const;
        vector<Point>&& getVictoryCellsInLines(Player winner) const;
        vector<Point>&& getVictoryCellsInRows(Player winner) const;
        vector<Point>&& getVictoryCellsInDiagonals(Player winner) const;

    vector<Point>&& getPins(Player pinner) const;
        vector<Point>&& getTrianglePins(Player pinner) const;
        vector<Point>&& getArrowPins(Player pinner) const;
        vector<Point>&& getPyramidPins(Player pinner) const;
        vector<Point>&& getAnglePins(Player pinner) const;

    Player ai;
    Field* field;
};

#endif // AI_HPP
