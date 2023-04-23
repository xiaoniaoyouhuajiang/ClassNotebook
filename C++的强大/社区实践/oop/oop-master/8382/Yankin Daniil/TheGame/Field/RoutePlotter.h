#pragma once

#include <map>
#include <vector>
#include "Trivia/Point.h"

class Cell;
class Field;
class IUnit;


class RoutePlotter
{
public:
    RoutePlotter() = default;

    std::map <Cell*, std::pair<Cell*, uint16_t>> getCellMovementMap(Field& field, IUnit* unit);
    static bool cellMovementComparator(std::pair <Cell*, std::pair<Cell*, uint16_t>>& one, std::pair <Cell*, std::pair<Cell*, uint16_t>>& two);

private:
    void cellMovementProcessing(Field& field, std::map <Cell*, std::pair<Cell*, uint16_t>>& cellMovementMap,
                                              std::vector <std::pair<Cell*, std::pair<Cell*, uint16_t>>>& cellQueue,
                                              uint16_t balance, Point oldPoint, Point newPoint);
};
