#include "TextButton.hpp"

TextButton::TextButton(float x, float y, float width, float height, std::string title)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_title(std::move(title))
{}

void TextButton::draw() const {
    if (m_isHovered)
        DrawRectangleRec({m_x, m_y, m_width, m_height}, hoverColor);
    DrawRectangleLinesEx({m_x, m_y, m_width, m_height}, borderWidth, borderColor);
    int textWidth = MeasureText(m_title.c_str(), buttonFontSize);
    int textOffsetX = ((int)m_width - textWidth) / 2;
    int textOffsetY = ((int)m_height - buttonFontSize) / 2;
    DrawText(m_title.c_str(), m_x + textOffsetX,
             m_y + textOffsetY, buttonFontSize, normalFontColor);
}

void TextButton::handleEvents() {
    if (GetMouseX() < m_x || GetMouseX() > m_x + m_width ||
        GetMouseY() < m_y || GetMouseY() > m_y + m_height)
    {
        m_isHovered = false;
        m_isClicked = false;
    }
    else {
        m_isHovered = true;
        m_isClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
}
