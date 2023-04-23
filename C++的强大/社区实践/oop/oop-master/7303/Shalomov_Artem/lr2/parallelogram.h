#include "rectangle.h"

class Parallelogram : public Rectangle{
protected:
    float theta;
    void print(ostream &out){
        out << "id: " << id  <<", Parallelogram " << width*scaleFactor << "X" << height*scaleFactor << " theta: " << theta<< " with center in (" << x << "; " << y << ") ";
        out << "colored " << color;
        if(angle!=0) out << "  rotated on " << angle << " degrees (clockwise)";
		out << "\nvertices:\n";
		for(int i = 0; i < 4; i++)
			out << '(' << vertices[i].x << "; " << vertices[i].y << ")\n"; 
    }
	void calcCoords(){
		for(int i = 0; i < 4; i++){
			vertices[i].x =  x - sign(cos(M_PI_4+i*M_PI_2))*(cos(toRadian(angle))*scaleFactor/2*
							(width-sign(tan(M_PI_4+i*M_PI_2))*height*(theta!=0?1/tan(toRadian(theta)):0))
							 - sin(toRadian(angle))*height*scaleFactor/2);
			vertices[i].y = y + sign(sin(M_PI_4+i*M_PI_2))*(sin(toRadian(angle))*scaleFactor/2*
							(width-sign(tan(M_PI_4+i*M_PI_2))*height*(theta!=0?1/tan(toRadian(theta)):0))
			 				+ cos(toRadian(angle))*height*scaleFactor/2);
		}
	}
public:
    Parallelogram(float centerX, float centerY, float width, float height, float theta)
        : Rectangle(centerX, centerY, width, height)
        , theta(theta){
		vertices = new Point2f[4];	
		calcCoords();
	}
};