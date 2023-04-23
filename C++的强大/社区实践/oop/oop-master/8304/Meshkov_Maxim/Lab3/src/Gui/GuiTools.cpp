#include "GuiTools.hpp"

#include "GuiConstants.hpp"
#include "../Terrains/GroundTerrain.hpp"
#include "../Terrains/StoneTerrain.hpp"
#include "../Terrains/WaterTerrain.hpp"
#include "../Base.hpp"
#include "../Things/MedicineThing.hpp"
#include "../Things/MicroMedicineThing.hpp"
#include "../Things/PowerfulMedicineThing.hpp"
#include "../Things/SmallMedicineThing.hpp"

std::string GuiTools::getMark(const Creature &creature) {
    return creature.getName().substr(0, 1);
}

std::string GuiTools::getUnitDescription(const Unit &unit, bool withIsIced) {
    std::string description =
            "Health: " + std::to_string(unit.getHealth()) + "\n" +
            "Hit: " + std::to_string(unit.getHit()) + "\n" +
            "Ices when attacks: " + (unit.icesWhenAttacks() ? "yes" : "no") + "\n" +
            "Armor: " + std::to_string(unit.getArmor()) + "\n" +
            "Move range: " + std::to_string(unit.getMoveRange()) + "\n" +
            "Attack range: " + std::to_string(unit.getAttackRange());
    if (withIsIced) {
        description += std::string("\n") + "Is iced: " + (unit.isIced() ? "yes" : "no");
    }
    return description;
}

Color GuiTools::getTerrainColor(const Terrain &terrain) {
    if (dynamic_cast<const GroundTerrain *>(&terrain)) {
        return groundColor;
    }
    if (dynamic_cast<const StoneTerrain *>(&terrain)) {
        return stoneColor;
    }
    if (dynamic_cast<const WaterTerrain *>(&terrain)) {
        return waterColor;
    }
    return BLANK;
}

Color GuiTools::getPlayerColor(std::optional<int> player) {
    if (player.has_value()) {
        switch (player.value()) {
            case 0:
                return YELLOW;
            case 1:
                return SKYBLUE;
        }
    }
    return normalFontColor;
}

void GuiTools::drawTextInHorizontalCenter(const std::string &text, int fontSize, Color color, int &y) {
    float spacing = (float)fontSize / 5.0f;//10.0f;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), (float)fontSize, spacing);
    DrawTextEx(GetFontDefault(), text.c_str(),
               {(float)GetScreenWidth() / 2 - textSize.x / 2, (float)y}, (float)fontSize, spacing, color);
    y += (int)textSize.y;
}

void GuiTools::drawCurtain() {
    DrawRectangleRec({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, curtainColor);
}

void GuiTools::drawCreatureInSquare(Rectangle square, const Creature &creature, int fontSize, float healthBarWidth) {
    auto mark = GuiTools::getMark(creature);
    auto playerColor = GuiTools::getPlayerColor(creature.getPlayer());
    int textWidth = MeasureText(mark.c_str(), fontSize);
    int textOffsetX = (square.width - textWidth) / 2;
    int textOffsetY = (square.height - fontSize) / 2;
    DrawText(mark.c_str(), square.x + textOffsetX,
             square.y + textOffsetY, fontSize, playerColor);

    Vector2 healthLineStart = {square.x + healthBarWidth,
                               square.y + healthBarWidth + healthBarWidth / 2.0f};
    float healthProportion = (float)creature.getHealth() / (float)creature.getMaxHealth();
    Vector2 healthLineEnd = { square.x + healthProportion * square.width - healthBarWidth,
                              healthLineStart.y};
    DrawLineEx(healthLineStart, healthLineEnd, healthBarWidth, playerColor);
}

void GuiTools::drawThingInSquare(Rectangle square, const Thing &thing) {
    std::string mark;
    if (dynamic_cast<const MedicineThing *>(&thing))
        mark = "+10";
     if (dynamic_cast<const MicroMedicineThing *>(&thing))
        mark = "+2";
    else if (dynamic_cast<const PowerfulMedicineThing *>(&thing))
        mark = "+F";
    else if (dynamic_cast<const SmallMedicineThing *>(&thing))
        mark = "+5";

    float fontSize = square.height / 3.f;

    int textWidth = MeasureText(mark.c_str(), fontSize);
    int textOffsetX = (square.width - textWidth) / 2;
    int textOffsetY = (square.height - fontSize) / 2;
    DrawText(mark.c_str(), square.x + textOffsetX,
             square.y + textOffsetY, fontSize, normalFontColor);
}
