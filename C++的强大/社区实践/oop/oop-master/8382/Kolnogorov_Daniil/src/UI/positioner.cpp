#include "positioner.hpp"
#include <algorithm>

Positioner::Positioner(int width, int height) {
    screen_width = width;
    screen_height = height;

    spacing = 10;
    margins = 10;
    box_width = 190;
}

void Positioner::resize(int width, int height) {
    screen_width = width;
    screen_height = height;
}

void Positioner::reset() {
    top_left_taken = margins;
    top_right_taken = margins;
    bottom_left_taken = margins;
    bottom_right_taken = margins;
}

Rectangle Positioner::rect_for_text(std::string text, position box_position) {
    unsigned lines = 1 + std::count(text.begin(), text.end(), '\n');
    // int box_height = lines * 40;
    int box_height = lines * 30 + 15;
    return rect_with_size(box_width, box_height, box_position);
}

Rectangle Positioner::rect_with_size(int width, int height,
                                     position box_position) {
    switch (box_position) {
    case TOP_LEFT: {
        Rectangle rect = {(float)(spacing), (float)(top_left_taken),
                          (float)(width), (float)(height)};
        top_left_taken += rect.height + spacing;
        return rect;
    }
    case TOP_RIGHT: {
        Rectangle rect = {(float)(screen_width - (width + spacing)),
                          (float)(top_right_taken), (float)width,
                          (float)(height)};
        top_right_taken += rect.height + spacing;
        return rect;
    }
    case BOTTOM_LEFT: {
        Rectangle rect = {(float)(spacing),
                          (float)(screen_height - bottom_left_taken - height),
                          (float)(width), (float)(height)};
        bottom_left_taken += rect.height + spacing;
        return rect;
    }
    case BOTTOM_RIGHT: {
        Rectangle rect = {(float)(screen_width - (width + spacing)),
                          (float)(screen_height - bottom_right_taken - height),
                          (float)(width), (float)(height)};
        bottom_right_taken += rect.height + spacing;
        return rect;
    }
    case CENTER: {
        Rectangle rect = {(float)(screen_width - width) / 2.0f,
                          (float)(screen_height - height) / 2.0f,
                          (float)(width), (float)(height)};
        return rect;
    }
    default:
        return {0, 0, 0, 0};
    }
}

Vector2 Positioner::center_of_rect(Rectangle rect) {
    Vector2 center = {(float)rect.x + rect.width / 2.0f,
                      (float)rect.y + rect.height / 2.0f};
    return center;
}
