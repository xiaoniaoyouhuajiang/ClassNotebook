#pragma once

#include <raylib.h>
#include <string>

typedef enum {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    CENTER,
} position;

class Positioner {
    int screen_width;
    int screen_height;

    int spacing;
    int margins;
    int box_width;

    int top_left_taken;
    int top_right_taken;
    int bottom_left_taken;
    int bottom_right_taken;

public:
    Positioner(int width, int height);
    void resize(int width, int height);
    void reset();
    Rectangle rect_for_text(std::string text, position box_position);
    Rectangle rect_with_size(int width, int height, position box_position);

    static Vector2 center_of_rect(Rectangle rect);
};
