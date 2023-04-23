#pragma once

#include <string>
#include <raylib.h>

#include "../Units/Unit.hpp"
#include "../Creature.hpp"
#include "../Terrains/Terrain.hpp"
#include "../Things/Thing.hpp"

class GuiTools {
public:
    static std::string getMark(const Creature &creature);
    static std::string getUnitDescription(const Unit &unit, bool withIsIced = false);
    static Color getTerrainColor(const Terrain &terrain);
    static Color getPlayerColor(std::optional<int> player);

    static void drawTextInHorizontalCenter(const std::string &text, int fontSize, Color color, int &y);
    static void drawCurtain();

    struct Offset {
        int x = 0, y = 0;
    };
    struct AreaSize {
        int width = 0, height = 0;
    };

    // TODO delete fontSize
    static void drawCreatureInSquare(Rectangle square, const Creature &creature, int fontSize, float healthBarWidth);
    static void drawThingInSquare(Rectangle square, const Thing &thing);
};
