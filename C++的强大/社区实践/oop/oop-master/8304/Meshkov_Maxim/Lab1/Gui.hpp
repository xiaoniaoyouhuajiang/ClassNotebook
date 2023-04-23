#pragma once

#include <memory>
#include <string>
#include <raylib.h>
#include <vector>

#include "Game.hpp"

class Gui {
public:
    explicit Gui(const  std::shared_ptr<Game> &game);
    Gui &operator=(const Gui&) = delete;

    void show();

private:
    std::shared_ptr<Game> m_game;

    void newGame();

    char getUnitMark(const Unit &unit) const;
    std::string getUnitDescription(const Unit &unit, bool withIsIced = false) const;

    void drawTextInHorizontalCenter(const std::string &text, int fontSize, Color color, int &y);

    void drawUnitInfo(const Unit &unit);
    bool unitInfoNeedToClose() const;

    int m_selectedNewUnit = 0; // TODO rename
    std::vector<std::shared_ptr<Unit>> m_newUnits;
    void drawNewUnitSelection();
    bool newUnitSelectionNeedToClose(FieldPosition selectedCell); // TODO remove FieldPosition
};
