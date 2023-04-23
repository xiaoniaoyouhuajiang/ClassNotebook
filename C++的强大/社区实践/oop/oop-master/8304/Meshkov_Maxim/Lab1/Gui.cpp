#include "Gui.hpp"

#include <optional>
#include <algorithm>

#include "Units/Knights/HeavyKnightUnit.hpp"
#include "Units/Knights/LightweightKnightUnit.hpp"
#include "Units/Archers/PowerfulArcherUnit.hpp"
#include "Units/Archers/DistanceArcherUnit.hpp"
#include "Units/Mages/IceMageUnit.hpp"
#include "Units/Mages/FireMageUnit.hpp"

Gui::Gui(const std::shared_ptr<Game> &game)
    : m_game(game)
{
    srand(time(0));
    newGame();

    m_newUnits.emplace_back(new HeavyKnightUnit);
    m_newUnits.emplace_back(new LightweightKnightUnit);
    m_newUnits.emplace_back(new PowerfulArcherUnit);
    m_newUnits.emplace_back(new DistanceArcherUnit);
    m_newUnits.emplace_back(new IceMageUnit);
    m_newUnits.emplace_back(new FireMageUnit);
}

void Gui::show() {
    InitWindow(800, 600, "Game");
    SetTargetFPS(60);
    SetExitKey(0);

    const int cellSize = 32;
    std::optional<FieldPosition> selectedCell;
    std::set<FieldPosition> possibleMoves;
    enum {
        USUAL,
        UNIT_INFO,
        NEW_UNIT_SELECTION
    } mode = USUAL;
    const Color backgroundColor = {50, 50, 50, 255 };
    const int borderWidth = 2;
    const Color borderColor = GRAY;
    const Color hoverColor = {255, 255, 255, 20};
    const Color possibleMoveColor = {255, 255, 255, 40};
    const Color selectionColor = BLUE;
    const int unitMarkFontSize = 20;
    const int healthBarOffset = borderWidth;// + 3;
    const int healthBarWidth = borderWidth;

    struct {
        int x = 0, y = 0;
    } fieldOffset;
    auto getCellRectangle = [&](int row, int col) -> Rectangle {
        float x = (float)(col * cellSize + fieldOffset.x);
        float y = (float)(row * cellSize + fieldOffset.y);
        return {x, y,cellSize + borderWidth, cellSize + borderWidth};
    };

    struct {
        int width = 0, height = 0;
    } fieldSizeInPixels;
    auto resizeWindow = [&] {
        fieldSizeInPixels.width = m_game->getFieldWidth() * cellSize + borderWidth;
        fieldSizeInPixels.height = m_game->getFieldHeight() * cellSize + borderWidth;
        fieldOffset = {cellSize / 2, cellSize * 3 / 2};
        SetWindowSize(fieldSizeInPixels.width + cellSize,
                fieldSizeInPixels.height + 2 * cellSize);
    };
    resizeWindow();

    auto getMouseCell = [&]() -> std::optional<FieldPosition> {
        if (GetMouseX() < fieldOffset.x || GetMouseX() > fieldOffset.x + fieldSizeInPixels.width ||
            GetMouseY() < fieldOffset.y || GetMouseY() > fieldOffset.y + fieldSizeInPixels.height)
            return {};
        return FieldPosition{
                std::clamp((GetMouseY() - fieldOffset.y) / cellSize, 0, m_game->getFieldHeight() - 1),
                std::clamp((GetMouseX() - fieldOffset.x) / cellSize, 0, m_game->getFieldWidth() - 1),
        };
    };

    while (!WindowShouldClose()) {
        if (mode == USUAL && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (auto mouseCell = getMouseCell()) {
                if (!selectedCell.has_value() || selectedCell.value() != mouseCell.value()) {
                    if (possibleMoves.find(mouseCell.value()) != possibleMoves.end()) {
                        m_game->move(selectedCell.value(), mouseCell.value());
                    }
                    selectedCell = mouseCell;
                    possibleMoves = m_game->findPossibleMoves(selectedCell.value());
                }
                else /* selectedCell = mouseCell */ {
                    if (m_game->cellHasUnit(selectedCell.value())) {
                        mode = UNIT_INFO;
                    }
                    else {
                        mode = NEW_UNIT_SELECTION;
                    }
                }
            }
        }
        else if (mode == UNIT_INFO && unitInfoNeedToClose()) {
            mode = USUAL;
        }
        else if (mode == NEW_UNIT_SELECTION && newUnitSelectionNeedToClose(selectedCell.value())) {
            mode = USUAL;
        }

        BeginDrawing();
        ClearBackground(backgroundColor);

        if (mode == USUAL || mode == UNIT_INFO || mode == NEW_UNIT_SELECTION) {
            DrawFPS(cellSize * 2 / 3, cellSize / 2);

            for (auto iter = m_game->getFieldBegin(); iter != m_game->getFieldEnd(); ++iter) {
                auto [unit, row, col] = *iter;
                auto cellRectangle = getCellRectangle(row, col);
                DrawRectangleLinesEx(cellRectangle, borderWidth, borderColor);
                if (m_game->cellHasUnit({row, col})) {
                    char text[] = " ";
                    text[0] = getUnitMark(*unit);
                    int textWidth = MeasureText(text, unitMarkFontSize);
                    int textOffsetX = (cellSize - textWidth) / 2;
                    int textOffsetY = (cellSize - unitMarkFontSize) / 2 + healthBarOffset;
                    DrawText(text, (int)cellRectangle.x + textOffsetX,
                             (int)cellRectangle.y + textOffsetY, unitMarkFontSize, GREEN); // TODO different color for players

                    DrawLineEx({cellRectangle.x + healthBarOffset, cellRectangle.y + healthBarOffset + healthBarWidth / 2.0f},
                               {cellRectangle.x + cellRectangle.width - healthBarOffset,
                                cellRectangle.y + healthBarOffset + healthBarWidth / 2.0f}, healthBarWidth, GREEN); // TODO color
                }
            }

            for (auto cell : possibleMoves) {
                auto cellRectangle = getCellRectangle(cell.row, cell.col);
                DrawRectangleRec(cellRectangle, possibleMoveColor);
            }

            if (auto mouseCell = getMouseCell(); mouseCell && mode == USUAL) {
                Rectangle mouseCellRectangle = getCellRectangle(mouseCell.value().row, mouseCell.value().col);
                DrawRectangleRec(mouseCellRectangle, hoverColor);
            }

            if (selectedCell) {
                auto cellRectangle = getCellRectangle(selectedCell.value().row, selectedCell.value().col);
                DrawRectangleLinesEx(cellRectangle, borderWidth, selectionColor);
            }
        }

        if (mode == UNIT_INFO) {
            drawUnitInfo(m_game->getUnit(selectedCell.value()));
        }
        else if (mode == NEW_UNIT_SELECTION) {
            drawNewUnitSelection();
        }

        EndDrawing();
    }

    CloseWindow();
}

void Gui::newGame() {
    m_game->start(rand() % 15 + 20, rand() % 10 + 15); // TODO
}

char Gui::getUnitMark(const Unit &unit) const {
    return unit.getName().front();
}

std::string Gui::getUnitDescription(const Unit &unit, bool withIsIced) const {
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

void Gui::drawTextInHorizontalCenter(const std::string &text, int fontSize, Color color, int &y) {
    float spacing = (float)fontSize / 5.0f;//10.0f;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), (float)fontSize, spacing);
    DrawTextEx(GetFontDefault(), text.c_str(),
               {(float)GetScreenWidth() / 2 - textSize.x / 2, (float)y}, (float)fontSize, spacing, color);
    y += (int)textSize.y;
}

void Gui::drawUnitInfo(const Unit &unit) {
    const Color shadowColor = {0, 0, 0, 200};
    DrawRectangleRec({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, shadowColor);

    int y = 0;
    y += 70;
    drawTextInHorizontalCenter(unit.getName(), 30, WHITE, y);
    y += 30;
    drawTextInHorizontalCenter(getUnitDescription(unit, true), 20, WHITE, y);
    y += 30;
    drawTextInHorizontalCenter("Click somewhere to close.", 20, DARKGRAY, y);
}

bool Gui::unitInfoNeedToClose() const {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Gui::drawNewUnitSelection() {
    const Color shadowColor = {0, 0, 0, 200};
    DrawRectangleRec({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, shadowColor);

    int y = 0;

    y += 70;
    drawTextInHorizontalCenter("Select unit to create", 30, WHITE, y);

    const Color backgroundColor = {50, 50, 50, 255 };
    const int cellSize = 48;
    const int borderWidth = 2;
    const Color borderColor = GRAY;
    //const Color hoverColor = {255, 255, 255, 20};
    const Color selectionColor = BLUE;
    const int unitMarkFontSize = 30;

    struct {
        int x = 0, y = 0;
    } fieldOffset;
    auto getCellRectangle = [&](int row, int col) -> Rectangle {
        float x = (float)(col * cellSize + fieldOffset.x);
        float y = (float)(row * cellSize + fieldOffset.y);
        return {x, y,cellSize + borderWidth, cellSize + borderWidth};
    };

    struct {
        int width = 0, height = 0;
    } fieldSizeInPixels;
    fieldSizeInPixels.width = m_newUnits.size() * cellSize + borderWidth;
    fieldSizeInPixels.height = cellSize + borderWidth;
    y += 30;
    fieldOffset = {GetScreenWidth() / 2 - fieldSizeInPixels.width / 2, y};
    y += fieldSizeInPixels.height;

    for (int col = 0; col < m_newUnits.size(); col++) {
        auto cellRectangle = getCellRectangle(0, col);
        DrawRectangleRec(cellRectangle, backgroundColor);
        DrawRectangleLinesEx(cellRectangle, borderWidth, borderColor);
        char text[] = " ";
        text[0] = getUnitMark(*m_newUnits[col]);
        int textWidth = MeasureText(text, unitMarkFontSize);
        int textOffsetX = (cellSize - textWidth) / 2;
        int textOffsetY = (cellSize - unitMarkFontSize) / 2;
        DrawText(text, (int)cellRectangle.x + textOffsetX,
                 (int)cellRectangle.y + textOffsetY, unitMarkFontSize, GREEN); // TODO different color for players
    }

    auto cellRectangle = getCellRectangle(0, m_selectedNewUnit);
    DrawRectangleLinesEx(cellRectangle, borderWidth, selectionColor);

    y += 30;
    drawTextInHorizontalCenter(m_newUnits[m_selectedNewUnit]->getName(), 20, WHITE, y);
    y += 30;
    drawTextInHorizontalCenter(getUnitDescription(*m_newUnits[m_selectedNewUnit]), 20, WHITE, y);
    y += 30;
    drawTextInHorizontalCenter("Click somewhere to close.", 20, DARKGRAY, y);
}

bool Gui::newUnitSelectionNeedToClose(FieldPosition selectedCell) {
    const int borderWidth = 2;
    const int cellSize = 48;
    struct {
        int x = 0, y = 0;
    } fieldOffset;

    struct {
        int width = 0, height = 0;
    } fieldSizeInPixels;
    fieldSizeInPixels.width = m_newUnits.size() * cellSize + borderWidth;
    fieldSizeInPixels.height = cellSize + borderWidth;
    int y = 70 + 30 + 30;
    fieldOffset = {GetScreenWidth() / 2 - fieldSizeInPixels.width / 2, y};

    auto getMouseCell = [&]() -> std::optional<FieldPosition> {
        if (GetMouseX() < fieldOffset.x || GetMouseX() > fieldOffset.x + fieldSizeInPixels.width ||
            GetMouseY() < fieldOffset.y || GetMouseY() > fieldOffset.y + fieldSizeInPixels.height)
            return {};
        return FieldPosition{
                0,
                std::clamp((GetMouseX() - fieldOffset.x) / cellSize, 0, (int)m_newUnits.size() - 1),
        };
    };

    if (auto mouseCell = getMouseCell()) {
        m_selectedNewUnit = mouseCell.value().col;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            m_game->addUnitOfSameType(*m_newUnits[m_selectedNewUnit], selectedCell);
            return true;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return true;
    }

    return false;
}



