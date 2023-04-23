#include "shape.h" 
#pragma once
class Rectangle : public Shape {
protected:
    float width, height;
    void print(ostream &out){
		out << "id: " << id  <<", Rectangle " << width*scaleFactor << "X" << height*scaleFactor << " with center in (" << x << "; " << y << ") ";
        out << "colored " << color;
        if(angle!=0) out << "  rotated on " << angle << " degrees (clockwise)";
		out << "\nvertices:\n";
		for(int i = 0; i < 4; i++)
			out << '(' << vertices[i].x << "; " << vertices[i].y << ")\n";
    }
	void calcCoords(){
		for(int i=0; i<4 ;i++){
			vertices[i].x = x - sign(cos(M_PI_4+i*M_PI_2))*(cos(toRadian(angle))*width - sin(toRadian(angle))*height)*scaleFactor/2;
			vertices[i].y = y + sign(sin(M_PI_4+i*M_PI_2))*(sin(toRadian(angle))*width + cos(toRadian(angle))*height)*scaleFactor/2;
		}
	}	
public:
    Rectangle(float centerX, float centerY, float width, float height)
        : Shape(centerX, centerY){
        scaleFactor = sqrt(width*width + height*height);
        this->width = width/scaleFactor;
        this->height = height/scaleFactor;
		vertices = new Point2f[4];
		calcCoords();
    }
};