#pragma once

#include <raylib.h>
#include <string>

#include "GuiConstants.hpp"

class TextButton {
public:
    TextButton(float x, float y, float width, float height, std::string title);

    void draw() const;
    void handleEvents();

    bool isClicked() const {
        return m_isClicked;
    }

private:
    float m_x, m_y;
    float m_width, m_height;
    std::string m_title;
    bool m_isClicked = false;
    bool m_isHovered = false;
};