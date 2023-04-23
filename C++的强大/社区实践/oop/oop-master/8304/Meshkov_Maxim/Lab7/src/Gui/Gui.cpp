#include "Gui.hpp"

#include <algorithm>

#include "GuiConstants.hpp"

constexpr int cellSize = 32;
constexpr int markFontSize = cellSize * 2 / 3;
constexpr int healthBarWidth = borderWidth;
constexpr Color possibleMoveColor = {255, 255, 255, 40};
constexpr Color attackColor = RED;

Gui::Gui(const std::shared_ptr<GameInterface> &game)
    : m_game(game)
{
    srand(time(0));
    newGame();
}

void Gui::show() {
    InitWindow(800, 600, "Game");
    SetTargetFPS(60);
    SetExitKey(0);

//    m_game->getField()->getCell({1000,1000});

    while (!WindowShouldClose()) {
        handleEvents();

        BeginDrawing();
        drawMainScreen();
        EndDrawing();
    }

    CloseWindow();
}

void Gui::newGame() {
    m_game->start(rand() % 8 + 15, rand() % 5 + 15);
}

void Gui::updateFieldSizeAndOffset() {
    GuiTools::AreaSize fieldSizeInPixels;
    fieldSizeInPixels.width = m_game->getField()->getWidth() * cellSize + borderWidth;
    fieldSizeInPixels.height = m_game->getField()->getHeight() * cellSize + borderWidth;
    if (m_fieldSizeInPixels.width == fieldSizeInPixels.width &&
        m_fieldSizeInPixels.height == fieldSizeInPixels.height)
    {
        return;
    }
    m_fieldSizeInPixels = fieldSizeInPixels;
    m_fieldOffset = {cellSize / 2, cellSize * 3 / 2};
    const int windowWidth = fieldSizeInPixels.width + cellSize;
    const int windowHeight = fieldSizeInPixels.height + 2 * cellSize;
    SetWindowSize(windowWidth, windowHeight);

    const int newGameButtonWidth = 110;
    const int newGameButtonXPosition = windowWidth - cellSize / 2.0 - newGameButtonWidth;
    const int loadSaveButtonsWidth = 64;
    const int loadButtonXPosition = newGameButtonXPosition - loadSaveButtonsWidth - inlineMargin;
    const int saveButtonXPosition = loadButtonXPosition - loadSaveButtonsWidth - inlineMargin;
    m_newGameButton.reset(new TextButton(newGameButtonXPosition, cellSize / 3.0, newGameButtonWidth, cellSize, "New game"));
    m_loadGameButton.reset(new TextButton(loadButtonXPosition, cellSize / 3.0, loadSaveButtonsWidth, cellSize, "Load"));
    m_saveGameButton.reset(new TextButton(saveButtonXPosition, cellSize / 3.0, loadSaveButtonsWidth, cellSize, "Save"));
}

void Gui::updatePossibleMoves() {
    m_possibleMoves = m_game->findPossibleMoves(m_selectedCell.value());
}

void Gui::updatePossibleAttacks() {
    m_possibleAttacks = m_game->findPossibleAttacks(m_selectedCell.value());
}

void Gui::resetSelection() {
    m_selectedCell.reset();
    m_possibleMoves = {};
    m_possibleAttacks = {};
}

void Gui::handleEvents() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        resetSelection();
    }

    if (!m_unitInfoScreen && !m_newUnitSelectionScreen) {
        if (m_newGameButton != nullptr) {
            m_newGameButton->handleEvents();
            if (m_newGameButton->isClicked())
                newGame();
        }
        try {
            if (m_loadGameButton != nullptr) {
                m_loadGameButton->handleEvents();
                if (m_loadGameButton->isClicked()) {
                    auto memento = GameMemento::loadFromFile("save.gm");
                    if (memento != nullptr)
                        m_game->restoreFromMemento(*memento);
                }
            }
            if (m_saveGameButton != nullptr) {
                m_saveGameButton->handleEvents();
                if (m_saveGameButton->isClicked()) {
                    auto memento = m_game->createMemento();
                    memento->saveToFile("save.gm");
                }
            }
        }
        catch (const GameMemento::FileError &e) {
            std::cerr << "Warning: " << e.what() << std::endl;
        }
    }

    int winner;
    if (m_game->gameOver(winner))
        return;

    if (!m_unitInfoScreen && !m_newUnitSelectionScreen && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (auto cellUnderMouse = getCellUnderMouse()) {
            if (!m_selectedCell.has_value() || m_selectedCell.value() != cellUnderMouse.value()) {
                bool goodUnit;
                if (m_selectedCell.has_value()) {
                    auto unit = m_game->getField()->getCell(m_selectedCell.value())->getUnit();
                    goodUnit = (unit != nullptr && unit->getPlayer() == m_game->getCurrentPlayer());
                }
                else {
                    goodUnit = false;
                }
                if (goodUnit && m_possibleMoves.find(cellUnderMouse.value()) != m_possibleMoves.end()) {
                    m_game->move(m_selectedCell.value(), cellUnderMouse.value());
                    resetSelection();
                }
                else if (goodUnit && m_possibleAttacks.find(cellUnderMouse.value()) != m_possibleAttacks.end()) {
                    m_game->attack(m_selectedCell.value(), cellUnderMouse.value());
                    resetSelection();
                }
                else {
                    m_selectedCell = cellUnderMouse;
                    updatePossibleMoves();
                    updatePossibleAttacks();
                }
            }
            else /* m_selectedCell = cellUnderMouse */ {
                if (auto unit = m_game->getField()->getCell(m_selectedCell.value())->getUnit()) {
                    m_unitInfoScreen.reset(new UnitInfoScreen(unit));
                }
                else if (auto base = m_game->getField()->getCell(m_selectedCell.value())->getBase()) {
                    if (base->getPlayer() == m_game->getCurrentPlayer())
                        m_newUnitSelectionScreen.reset(new NewUnitSelectionScreen(base));
                }
            }
        }
        else {
            resetSelection();
        }
    }
    else if (m_unitInfoScreen) {
        m_unitInfoScreen->handleEvents();
        if (m_unitInfoScreen->needToClose()) {
            m_unitInfoScreen.reset();
        }
    }
    else if (m_newUnitSelectionScreen) {
        m_newUnitSelectionScreen->handleEvents();
        if (m_newUnitSelectionScreen->needToClose()) {
            if (auto unitFactory = m_newUnitSelectionScreen->getUnitToCreate()) {
                m_game->createUnit(unitFactory, m_selectedCell.value());
                updatePossibleMoves();
                updatePossibleAttacks();
            }
            m_newUnitSelectionScreen.reset();
        }
    }
}

Rectangle Gui::getCellSquare(FieldPosition position) const {
    float x = (float)(m_fieldOffset.x + position.col * cellSize);
    float y = (float)(m_fieldOffset.y + position.row * cellSize);
    return {x, y, cellSize + borderWidth, cellSize + borderWidth};
}

std::optional<FieldPosition> Gui::getCellUnderMouse() const {
    if (GetMouseX() < m_fieldOffset.x || GetMouseX() > m_fieldOffset.x + m_fieldSizeInPixels.width ||
        GetMouseY() < m_fieldOffset.y || GetMouseY() > m_fieldOffset.y + m_fieldSizeInPixels.height)
    {
        return {};
    }
    return FieldPosition{
            std::clamp((GetMouseY() - m_fieldOffset.y) / cellSize, 0, m_game->getField()->getHeight() - 1),
            std::clamp((GetMouseX() - m_fieldOffset.x) / cellSize, 0, m_game->getField()->getWidth() - 1),
    };
}

void Gui::drawMainScreen() {
    updateFieldSizeAndOffset();

    ClearBackground(backgroundColor);

    int winner;
    std::string gameStatus;
    Color gameStatusColor;
    if (!m_game->gameOver(winner)) {
        gameStatus = "Turn of player " + std::to_string(m_game->getCurrentPlayer() + 1);
        gameStatusColor = GuiTools::getPlayerColor(m_game->getCurrentPlayer());
    }
    else {
        gameStatus = "Player " + std::to_string(winner + 1) + " is won!";
        gameStatusColor = GuiTools::getPlayerColor(winner);
    }
    DrawText(gameStatus.c_str(), cellSize / 2.0, cellSize / 2.0, normalFontSize, gameStatusColor);

    if (m_newGameButton != nullptr)
        m_newGameButton->draw();
    if (m_loadGameButton != nullptr)
        m_loadGameButton->draw();
    if (m_saveGameButton != nullptr)
        m_saveGameButton->draw();

    for (auto [cell, position] : *(m_game->getField())) {
        auto cellRectangle = getCellSquare({position.row, position.col});
        DrawRectangleRec(cellRectangle, GuiTools::getTerrainColor(*cell->getTerrain()));
        DrawRectangleLinesEx(cellRectangle, borderWidth, borderColor);

        if (auto thing = cell->getThing()) {
            GuiTools::drawThingInSquare(cellRectangle, *thing);
        }
        if (auto creature = cell->getCreature()) {
            GuiTools::drawCreatureInSquare(cellRectangle, *creature, markFontSize, healthBarWidth);
        }
    }

    for (auto cell : m_possibleMoves) {
        auto cellRectangle = getCellSquare(cell);
        DrawRectangleRec(cellRectangle, possibleMoveColor);
    }

    if (auto mouseCell = getCellUnderMouse(); mouseCell && !m_unitInfoScreen && !m_newUnitSelectionScreen) {
        Rectangle mouseCellRectangle = getCellSquare(mouseCell.value());
        DrawRectangleRec(mouseCellRectangle, hoverColor);
    }

    if (m_selectedCell) {
        auto cellRectangle = getCellSquare(m_selectedCell.value());
        DrawRectangleLinesEx(cellRectangle, borderWidth, selectionColor);
    }

    for (auto cell : m_possibleAttacks) {
        auto cellRectangle = getCellSquare(cell);
        DrawRectangleLinesEx(cellRectangle, borderWidth, attackColor);
    }

    if (m_unitInfoScreen != nullptr) {
        m_unitInfoScreen->draw();
    }
    if (m_newUnitSelectionScreen != nullptr) {
        m_newUnitSelectionScreen->draw();
    }
}
