#pragma once

#include <memory>
#include <string>
#include <raylib.h>
#include <vector>
#include <optional>

#include "../GameInterface.hpp"
#include "GuiTools.hpp"
#include "NewUnitSelectionScreen.hpp"
#include "UnitInfoScreen.hpp"
#include "TextButton.hpp"

class Gui {
public:
    explicit Gui(const  std::shared_ptr<GameInterface> &game);
    Gui &operator=(const Gui&) = delete;

    void show();

private:
    std::shared_ptr<GameInterface> m_game;
    void newGame();

    std::optional<FieldPosition> m_selectedCell;
    std::set<FieldPosition> m_possibleMoves;
    std::set<FieldPosition> m_possibleAttacks;

    std::shared_ptr<TextButton> m_newGameButton;
    std::shared_ptr<TextButton> m_saveGameButton;
    std::shared_ptr<TextButton> m_loadGameButton;

    GuiTools::Offset m_fieldOffset;
    GuiTools::AreaSize m_fieldSizeInPixels;
    void updateFieldSizeAndOffset();
    void updatePossibleMoves();
    void updatePossibleAttacks();
    void resetSelection();
    void handleEvents();
    Rectangle getCellSquare(FieldPosition position) const;
    std::optional<FieldPosition> getCellUnderMouse() const;
    void drawMainScreen();

    std::shared_ptr<UnitInfoScreen> m_unitInfoScreen;
    std::shared_ptr<NewUnitSelectionScreen> m_newUnitSelectionScreen;
};
