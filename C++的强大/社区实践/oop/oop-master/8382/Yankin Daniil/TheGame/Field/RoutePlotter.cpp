#include "RoutePlotter.h"
#include "Field.h"
#include "Landscape/LandscapeHeader.h"
#include "Base/Base.h"
#include "Unit/IUnit.h"


std::map <Cell*, std::pair<Cell*, uint16_t>> RoutePlotter::getCellMovementMap(Field& field, IUnit* unit) {
    std::map <Cell*, std::pair<Cell*, uint16_t>> cellMovementMap;

    Cell* cell = field.getCell(unit->getPoint());
    Cell* prevCell = nullptr;
    uint16_t balance = unit->getMovePoints();

    std::vector <std::pair<Cell*, std::pair<Cell*, uint16_t>>> cellQueue;
    cellQueue.push_back(std::make_pair(cell, std::make_pair(prevCell, balance)));

    while (!cellQueue.empty()) {
        cell = cellQueue.back().first;
        std::tie(prevCell, balance) = cellQueue.back().second;
        cellQueue.pop_back();

        cellMovementMap.insert(std::make_pair(cell, std::make_pair(prevCell, balance)));


        if (cell->getPoint() != unit->getPoint() &&
                (!cell->isUnitFree() || (cell->getBuildingGroupType() == BASE && cell->getBase()->getPlayer() != unit->getPlayer())))
        {
            continue;
        }


        Point currentPoint = cell->getPoint();
        uint16_t x = currentPoint.getX();
        uint16_t y = currentPoint.getY();

        Point newPoint(0, 0);

        if (balance > 0) {
            newPoint = Point(x - 1, y);
            if (x > 0 && field.getLandscape(newPoint)->movementAccess()) {
                cellMovementProcessing(field, cellMovementMap, cellQueue, balance, currentPoint, newPoint);
            }

            newPoint = Point(x + 1, y);
            if (x < field.getWidth() - 1 && field.getLandscape(newPoint)->movementAccess()) {
                cellMovementProcessing(field, cellMovementMap, cellQueue, balance, currentPoint, newPoint);
            }

            newPoint = Point(x, y - 1);
            if (y > 0 && field.getLandscape(newPoint)->movementAccess()) {
                cellMovementProcessing(field, cellMovementMap, cellQueue, balance, currentPoint, newPoint);
            }

            newPoint = Point(x, y + 1);
            if (y < field.getHeight() - 1 && field.getLandscape(newPoint)->movementAccess()) {
                cellMovementProcessing(field, cellMovementMap, cellQueue, balance, currentPoint, newPoint);
            }


            if (y % 2 == 0) {
                newPoint = Point(x - 1, y - 1);
                if (x > 0 && y > 0 && field.getLandscape(newPoint)->movementAccess()) {
                    cellMovementProcessing(field, cellMovementMap, cellQueue, balance, currentPoint, newPoint);
                }

                newPoint = Point(x - 1, y + 1);
                if (x > 0 && y < field.getHeight() - 1 && field.getLandscape(newPoint)->movementAccess()) {
                    cellMovementProcessing(field, cellMovementMap, cellQueue, balance, currentPoint, newPoint);
                }
            }
            else {
                newPoint = Point(x + 1, y - 1);
                if (x < field.getWidth() - 1 && y > 0 && field.getLandscape(newPoint)->movementAccess()) {
                    cellMovementProcessing(field, cellMovementMap, cellQueue, balance, currentPoint, newPoint);
                }

                newPoint = Point(x + 1, y + 1);
                if (x < field.getWidth() - 1 && y < field.getHeight() - 1 && field.getLandscape(newPoint)->movementAccess()) {
                    cellMovementProcessing(field, cellMovementMap, cellQueue, balance, currentPoint, newPoint);
                }
            }
        }
        std::sort(cellQueue.begin(), cellQueue.end(), RoutePlotter::cellMovementComparator);
    }

    return cellMovementMap;
}

void RoutePlotter::cellMovementProcessing(Field& field, std::map <Cell*, std::pair<Cell*, uint16_t>>& cellMovementMap,
                                          std::vector <std::pair<Cell*, std::pair<Cell*, uint16_t>>>& cellQueue,
                                          uint16_t balance, Point oldPoint, Point newPoint)
{
    uint16_t movementCost = field.getLandscape(newPoint)->getMovementCost();

    Cell* oldCell = field.getCell(oldPoint);
    Cell* newCell = field.getCell(newPoint);

    if (cellMovementMap.find(newCell) != cellMovementMap.end())
        return;

    for (auto elem = cellQueue.begin(); elem != cellQueue.end(); elem++) {
        if (elem->first == newCell) {
            if (elem->second.second < balance - movementCost) {
                elem->second = std::make_pair(oldCell, std::max(balance - movementCost, 0));
            }
            return;
        }
    }

    cellQueue.push_back(std::make_pair(newCell, std::make_pair(oldCell, std::max(balance - movementCost, 0))));
}

bool RoutePlotter::cellMovementComparator(std::pair <Cell*, std::pair<Cell*, uint16_t>>& one, std::pair <Cell*, std::pair<Cell*, uint16_t>>& two) {
    if (one.second.second < two.second.second)
        return true;
    return false;
}
