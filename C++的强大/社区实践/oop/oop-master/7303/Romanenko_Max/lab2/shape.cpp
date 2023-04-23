#include "shape.h"


unsigned int Shape::id_counter = 1;

    void Shape::move(const Point& p){
        double x_diff = p.x - pos.x;
        double y_diff = p.y - pos.y;
        pos.x += x_diff;
        pos.y += y_diff;
        for(auto& el : points){
            el.x += x_diff;
            el.y += y_diff;
        }
    }

    void Shape::scale(double scale){
        this->Scale *= scale;
        for(auto& el : points){
            double x = el.x - pos.x;
            double y = el.y - pos.y;
            el.x = pos.x + x*scale;
            el.y = pos.y + y*scale;
        }
    }

    void Shape::turn(double angle){

        this->angle = fmod((this->angle + angle),360);
        for(auto& el : points){
            double x = el.x - pos.x;
            double y = el.y - pos.y;
            el.x =pos.x + x*cos(this->angle*M_PI/180) - y*sin(this->angle*M_PI/180);
            el.y =pos.y + x*sin(this->angle*M_PI/180) + y*cos(this->angle*M_PI/180);
        }
    }

     std::ostream& operator<<(std::ostream& out, Shape& shape){
        out << "Id: " << shape.id << std::endl;
        out << "Coordinates of extreme points: ";
        for(auto& el : shape.points){
           out << el << " ";
        }
        out << std::endl << "Color: " << shape.color;
        out << std::endl << "Scale: " << shape.Scale << "x";
        out << std::endl << "Angle: " << shape.angle << " degree";
        return out;


    }

    void Shape::setColor(Color color) {
      this->color.set(color.red,color.green,color.blue);
    }
    Color Shape::getColor() {
      return color;
    }

    Shape::Shape(const Point& position)
        :pos(position), id(id_counter){
        id_counter++;

    }

    std::ostream& operator<<(std::ostream& out, Point& p) {
      return out << "{x:" << p.x << ", y:" << p.y << "}";
    }

    std::ostream& operator<<(std::ostream& out, Color& n) {
      return out << "(" << (int)n.red << "," << (int)n.green << "," << (int)n.blue << ")";
    }
