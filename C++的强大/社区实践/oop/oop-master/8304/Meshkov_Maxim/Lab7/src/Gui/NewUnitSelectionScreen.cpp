#include "NewUnitSelectionScreen.hpp"

#include <algorithm>

#include "GuiConstants.hpp"

#include "../Units/Knights/HeavyKnightUnit.hpp"
#include "../Units/Knights/LightweightKnightUnit.hpp"
#include "../Units/Archers/PowerfulArcherUnit.hpp"
#include "../Units/Archers/DistanceArcherUnit.hpp"
#include "../Units/Mages/IceMageUnit.hpp"
#include "../Units/Mages/FireMageUnit.hpp"

constexpr int cellSize = 48;
constexpr int markFontSize = cellSize * 2 / 3;

NewUnitSelectionScreen::NewUnitSelectionScreen(std::weak_ptr<const Base> base)
    : m_base(std::move(base))
{
    m_candidates.emplace_back(new HeavyKnightUnit);
    m_candidates.emplace_back(new LightweightKnightUnit);
    m_candidates.emplace_back(new PowerfulArcherUnit);
    m_candidates.emplace_back(new DistanceArcherUnit);
    m_candidates.emplace_back(new IceMageUnit);
    m_candidates.emplace_back(new FireMageUnit);
}

void NewUnitSelectionScreen::draw() {
    GuiTools::drawCurtain();

    int y = 0;

    if (auto base = m_base.lock()) {
        y += titleMarginTop;
        GuiTools::drawTextInHorizontalCenter("Base", titleFontSize, normalFontColor, y);
        y += standardMargin;
        auto description = "Health: " + std::to_string(base->getHealth()) + '\n' +
                "Creation ability: " + std::to_string(base->getCreationAbility());
        GuiTools::drawTextInHorizontalCenter(description, normalFontSize, normalFontColor, y);
    }

    y += titleMarginTop;
    GuiTools::drawTextInHorizontalCenter("Select unit to create", titleFontSize, normalFontColor, y);

    y += standardMargin;
    updateCandidatesListSizeAndOffset(y);
    for (int candidate = 0; candidate < m_candidates.size(); candidate++) {
        auto candidateSquare = getCandidateSquare(candidate);
        DrawRectangleRec(candidateSquare, backgroundColor);
        DrawRectangleLinesEx(candidateSquare, borderWidth, borderColor);
        GuiTools::drawCreatureInSquare(candidateSquare, *m_candidates[candidate], markFontSize, 0);
    }
    y += m_candidatesListSize.height;

    auto selectedCandidateSquare = getCandidateSquare(m_selectedCandidate);
    DrawRectangleLinesEx(selectedCandidateSquare, borderWidth, selectionColor);

    y += standardMargin;
    auto &selectedCandidate = *m_candidates[m_selectedCandidate];
    GuiTools::drawTextInHorizontalCenter(selectedCandidate.getName(), normalFontSize, normalFontColor, y);
    y += standardMargin;
    GuiTools::drawTextInHorizontalCenter(GuiTools::getUnitDescription(selectedCandidate), normalFontSize, normalFontColor, y);
    y += standardMargin;
    GuiTools::drawTextInHorizontalCenter("Click somewhere to close.", normalFontSize, subtleFontColor, y);

    m_isDrawn = true;
}

void NewUnitSelectionScreen::handleEvents() {
    if (m_isDrawn) {
        if (auto candidateUnderMouse = getCandidateUnderMouse()) {
            m_selectedCandidate = candidateUnderMouse.value();
            m_needToCreateUnit = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        }
        m_needToClose = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
}

bool NewUnitSelectionScreen::needToClose() const {
    return m_needToClose;
}

std::shared_ptr<UnitFactory> NewUnitSelectionScreen::getUnitToCreate() const {
    if (m_needToCreateUnit) {
        return m_candidates[m_selectedCandidate]->createUnitFactory();
    }
    return nullptr;
}

void NewUnitSelectionScreen::updateCandidatesListSizeAndOffset(int y) {
    if (m_isDrawn && GetScreenWidth() == m_screenSize.width && GetScreenWidth() == m_screenSize.width) {
        return;
    }
    m_candidatesListSize.width = (int)m_candidates.size() * cellSize + borderWidth;
    m_candidatesListSize.height = cellSize + borderWidth;
    m_candidatesListOffset.x = GetScreenWidth() / 2 - m_candidatesListSize.width / 2;
    m_candidatesListOffset.y = y;
}

std::optional<int> NewUnitSelectionScreen::getCandidateUnderMouse() const {
    if (GetMouseX() < m_candidatesListOffset.x ||
        GetMouseX() > m_candidatesListOffset.x + m_candidatesListSize.width ||
        GetMouseY() < m_candidatesListOffset.y ||
        GetMouseY() > m_candidatesListOffset.y + m_candidatesListSize.height)
    {
        return {};
    }
    return std::clamp((GetMouseX() - m_candidatesListOffset.x) / cellSize, 0, (int)m_candidates.size() - 1);
}

Rectangle NewUnitSelectionScreen::getCandidateSquare(int candidate) const {
    float x = (float)(candidate * cellSize + m_candidatesListOffset.x);
    float y = (float)m_candidatesListOffset.y;
    return {x, y,cellSize + borderWidth, cellSize + borderWidth};
}
