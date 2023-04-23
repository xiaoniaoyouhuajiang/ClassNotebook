#include <cmath>
#pragma once
#define toRadian(x) x*6.28/360
//#define PI2 1.57
//#define PI4 0.785
using namespace std;
inline int sign(float x){
	if(x==0)return 0;
	return (x>0)?1:-1;
}
struct Point2f{
	float x,y;
	Point2f(float x=0,float y=0)
		:x(x)
		,y(y){}
};
class Shape{
protected:
    int id;
    float x, y;
    float angle = 0;
    float scaleFactor = 1;
	Point2f *vertices = nullptr;
    struct Color{
        unsigned char r,g,b;
		friend ostream& operator<<(ostream& out, const Color& c){
		out << "0x" << std::hex
        << ((c.r&(unsigned char)0xf0)>>4) << (c.r&(unsigned char)0x0f)
        << ((c.g&(unsigned char)0xf0)>>4) << (c.g&(unsigned char)0x0f)
        << ((c.b&(unsigned char)0xf0)>>4) << (c.b&(unsigned char)0x0f);		
		}
    } color;
    virtual void print(ostream &out)=0;
	virtual void calcCoords() = 0;
    Shape(float centerX, float centerY)
        : x(centerX)
        , y(centerY){
		static int ID_COUNTER = 1;
        id = ID_COUNTER++;
	}
public:
	~Shape(){
		delete [] vertices;
	};
    void moveTo(float centerX, float centerY){
        x = centerX;
        y = centerY;
		calcCoords();
    }
    void setRotation(float degrees){
        this->angle = degrees;
		calcCoords();
    }
    void scale(float scaleFactor){
        if(isnan(scaleFactor) || isinf(scaleFactor) || scaleFactor<=0) return;//minus
        this->scaleFactor *= scaleFactor;
		calcCoords();
    }
    Color getColor(){ return color;}
    void setColor(Color color){
        this->color = color;
    }
    int getId(){return id;}
	ostream& operator<<(ostream &out){
	out << "HELLO WORLD!\n";	
	}
    friend ostream& operator<<(ostream &out,Shape &shape){
        shape.print(out);
        return out;
    }
};