#include <iostream>
#include <math.h>
#include <limits>

#include "bitmap_image.hpp"
#include "shape.h"

using namespace std;



void draw_shape(bitmap_image& image, const Shape& shape)
{
    //double max_x = shape.get_center().x, max_y = shape.get_center().y;
    //double min_x = shape.get_center().x, min_y = shape.get_center().y;
    /*
    for (size_t i = 0; i < shape.get_total_vertices(); i++)
    {
        if (shape.get_vertex(i).x > max_x) max_x = shape.get_vertex(i).x;
        if (shape.get_vertex(i).y > max_y) max_y = shape.get_vertex(i).y;
        if (shape.get_vertex(i).x < min_x) min_x = shape.get_vertex(i).x;
        if (shape.get_vertex(i).y < min_y) min_y = shape.get_vertex(i).y;
    }

    size_t width  = size_t(max_x - min_x + 1.0);
    size_t height = size_t(max_y - min_y + 1.0);
    */
    //bitmap_image image(width, height);
    //image.set_all_channels(255, 255, 255);
    image_drawer drawer(image);

    unsigned char red = shape.get_color().r, green = shape.get_color().b, blue = shape.get_color().b;

    drawer.pen_width(1);
    drawer.pen_color(red, green, blue);

    size_t mx = shape.get_center().x;
    size_t my = shape.get_center().y;

    size_t n = shape.get_total_vertices();

    for (size_t i = 0; i < n-1; i++)
    {
        //image.set_pixel( (shape.get_vertex(i).x-min_x), (shape.get_vertex(i).y-min_y), red, green, blue );
        drawer.line_segment((shape.get_vertex(i).x), (shape.get_vertex(i).y), (shape.get_vertex(i+1).x), (shape.get_vertex(i+1).y));
    }

    drawer.line_segment((shape.get_vertex(n-1).x), (shape.get_vertex(n-1).y), (shape.get_vertex(1).x), (shape.get_vertex(1).y));

    //image.save_image("out.bmp");

}

int main() {
    size_t n = 10;
    double x = 50.0, y = 50.0, da = 3.14159265/n;
    Trapezoid trapezoid({x, y}, 50.0, 50.0, 100.0, 50.0);
    cout << trapezoid << endl;
    trapezoid.set_color({255, 0, 0});
    bitmap_image image(1000, 1000);
    image.set_all_channels(255, 255, 255);

    for (size_t i = 1; i < n; i++)
    {
        trapezoid.move_to({x, y});
        trapezoid.rotate(3.1415926535/n);
        x += 100.0; y += 100.0;
        draw_shape(image, trapezoid);
    }

    image.save_image("result.bmp");
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}
