#include "Rectangle.h"
#include <math.h>
#include <iostream>


void Print() {
    for (int i = 0; i < 4; i++)
    {
        std::cout << "coordinates of angle: " << coordinates[i][0] << ' ' << coordinates[i][1] << std::endl;
    }
    std::cout << "coordinates of the opper-left corner: " << left_x << ' ' << left_y << std::endl;
    std::cout << "coordinates of the bottom right corner: " << right_x << ' ' << right_y << std::endl;
    std::cout << "color: " << color << std::endl;
}
Rectangle(float(&coord)[4][2], int c = 0)
{
    float x1 = coord[0][0], x2 = coord[0][0],
            y1 = coord[0][1], y2 = coord[0][1];
    for (int i = 0; i<4; i++)
    {
        coordinates[i][0] = coord[i][0]; coordinates[i][1] = coord[i][1];
        if (x1>coord[i][0]) x1 = coord[i][0];
        if (x2<coord[i][0]) x2 = coord[i][0];
        if (y1<coord[i][1]) y1 = coord[i][1];
        if (y2>coord[i][1]) y2 = coord[i][1];
    }
    left_x = x1; left_y = y1;
    right_x = x2; right_y = y2;
    color = c;
}
void Move(float new_x, float new_y)
{
    for (int i = 4; i>0; i--)
    {
        coordinates[i][0] = new_x + (coordinates[i][0] - coordinates[0][0]);
        coordinates[i][1] = new_y + (coordinates[i][1] - coordinates[0][1]);
    }

    if ((left_x == coordinates[0][0]) && (left_y == coordinates[0][1])) { left_x = new_x; left_y = new_y; }
    else { left_x = new_x + (left_x - coordinates[0][0]); left_y = new_y + (left_y - coordinates[0][1]); }

    if ((right_x == coordinates[0][0]) && (right_y == coordinates[0][1])) { right_x = new_x; right_y = new_y; }
    else { right_x = new_x + (right_x - coordinates[0][0]); right_y = new_y + (right_y - coordinates[0][1]); }

    coordinates[0][0] = new_x; coordinates[0][1] = new_y;
}
void Scale(float k)
{
    for (int i = 3; i>0; i--)
    {
        coordinates[i][0] = coordinates[i][0] * k;
        coordinates[i][1] = coordinates[i][1] * k;
    }

    if ((left_x == coordinates[0][0]) && (left_y != coordinates[0][1])) { left_y = left_y * k; }
    if ((left_x != coordinates[0][0]) && (left_y == coordinates[0][1])) { left_x = left_x * k; }
    if ((left_x != coordinates[0][0]) && (left_y != coordinates[0][1])) { left_x = left_x * k; left_y = left_y * k; }

    if ((right_x == coordinates[0][0]) && (right_y != coordinates[0][1])) { right_y = right_y * k; }
    if ((right_x != coordinates[0][0]) && (right_y == coordinates[0][1])) { right_x = right_x * k; }
    if ((right_x != coordinates[0][0]) && (right_y != coordinates[0][1])) { right_x = right_x * k; right_y = right_y * k; }

}
void Turn(float angle)
{
    float x, y;

    for (int i = 3; i>0; i--)
    {
        x = coordinates[i][0] * cos(angle) + coordinates[i][1] * sin(angle);
        y = -coordinates[i][0] * sin(angle) + coordinates[i][1] * cos(angle);
        coordinates[i][0] = x; coordinates[i][1] = y;
    }

    x = left_x*cos(angle) + left_y*sin(angle);
    y = -left_x*sin(angle) + left_y*cos(angle);
    left_x = x; left_y = y;

    x = right_x*cos(angle) + right_y*sin(angle);
    y = -right_x*sin(angle) + right_y*cos(angle);
    right_x = x; right_y = y;
}