#include "UnitInfoScreen.hpp"

#include "GuiConstants.hpp"
#include "GuiTools.hpp"

UnitInfoScreen::UnitInfoScreen(std::shared_ptr<const Unit> unit)
    : m_unit(unit)
{}

void UnitInfoScreen::draw() const {
    if (m_unit) {
        GuiTools::drawCurtain();

        int y = 0;
        y += titleMarginTop;
        GuiTools::drawTextInHorizontalCenter(m_unit->getName(), titleFontSize, normalFontColor, y);
        y += standardMargin;
        GuiTools::drawTextInHorizontalCenter(GuiTools::getUnitDescription(*m_unit, true), normalFontSize, normalFontColor, y);
        y += standardMargin;
        GuiTools::drawTextInHorizontalCenter("Click somewhere to close.", normalFontSize, subtleFontColor, y);
    }
}

void UnitInfoScreen::handleEvents() {
    m_needToClose = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool UnitInfoScreen::needToClose() const {
    return m_needToClose;
}
