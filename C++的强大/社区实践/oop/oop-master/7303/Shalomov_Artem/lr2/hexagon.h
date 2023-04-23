#include "shape.h"
class Hexagon : public Shape{
protected:
	void print(ostream &out){
		out << "id: " << id  <<", Hexagon inscribed in circle of radius " << scaleFactor << " with center in (" << x << "; " << y << ") ";
        out << "colored 0x" << std::hex
            << ((color.r&(unsigned char)0xf0)>>4) << (color.r&(unsigned char)0x0f)
            << ((color.g&(unsigned char)0xf0)>>4) << (color.g&(unsigned char)0x0f)
            << ((color.b&(unsigned char)0xf0)>>4) << (color.b&(unsigned char)0x0f);
        if(angle!=0) out << "  rotated on " << angle << " degrees (clockwise)";
		out << "\nvertices:\n";
		for(int i = 0; i < 6; i++)
            out << '(' << vertices[i].x << "; " << vertices[i].y << ")\n";
	}
	void calcCoords(){
		for(int i = 0; i < 6; i++){
            vertices[i].x = x + sin(M_PI/3 * i + toRadian(angle))*scaleFactor;
			vertices[i].y = y + cos(M_PI/3 * i + toRadian(angle))*scaleFactor;
		}
	}	

public:
    Hexagon(float centerX,float centerY,float radius)
        : Shape(centerX, centerY){
        this->scaleFactor = radius;
		vertices = new Point2f[6];
		calcCoords();
    }

};