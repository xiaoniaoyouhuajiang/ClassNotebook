#include <iostream>
#include <cstdlib>
#include <algorithm>

int global_id=0;

struct colorShape{
	int r;
	int g;
	int b;
	friend std::ostream& operator<< (std::ostream &out, const colorShape &color){
		out << color.r << ", " << color.g << ", " << color.b
		<< "\n";
		return out;
	}
};

class Shape{
public:
	Shape(int x=0, int y=0): x(x), y(y){
		color= {0,0,0};
		angle=0;
		id=global_id++;
	}
	virtual ~Shape(){}
	void move(int x, int y){
		this->x=x;
		this->y=y;
	}
	virtual void rotate(int angle=0){
		angle = angle % 360;
		if (angle<0) angle+=360;
		this->angle += angle;
		if (this->angle >= 360) this->angle %= 360;
	}
	virtual void scale(int size)= 0;
	void setColor(colorShape color){
		this->color = color;
	}
	colorShape getColor(){
		return color;
	}
protected:
int x;
int y;
int angle;
colorShape color;
int id;
};

class Rectangle: public Shape {
public:
	Rectangle(int x=0, int y=0, int length=1, int width=1):
	Shape(x,y), length(length), width(width){
	}
	~Rectangle(){}
	void scale(int size=1) override{
		length*=size;
		width*=size;
	}
	friend std::ostream& operator<< (std::ostream& out, const Rectangle& some_rect){
		out <<"Rectangle:\nID =  "<< some_rect.id<<
		"\nCentre coordinates = "<< some_rect.x <<
		"," << some_rect.y << "\nAngle of rotation = "
		<< some_rect.angle << "\nColor(R,G,B) = " <<some_rect.color
		<< "Length = " << some_rect.length <<"\nWidth = "
		<< some_rect.width
		<< "\n\n";
		return out;
	}
protected:
int length;
int width;
};

class Ellipse: public Shape {
public:
	Ellipse(int x=0, int y=0, int big_semiaxis=2, int small_semiaxis=1):
	Shape(x,y),big_semiaxis(big_semiaxis), small_semiaxis(small_semiaxis){
		if (this->big_semiaxis < this->small_semiaxis)
			std::swap(this->small_semiaxis,this->big_semiaxis);
	}
	~Ellipse(){}
	void scale(int size=1) override{
		big_semiaxis*=size;
		small_semiaxis*=size;
	}
	friend std::ostream& operator<< (std::ostream& out, const Ellipse& some_ell){
		out <<"Ellipse:\nID =  "<< some_ell.id<<
		"\nCentre coordinates = "<< some_ell.x <<
		"," << some_ell.y << "\nAngle of rotation = "
		<< some_ell.angle << "\nColor(R,G,B) = " <<some_ell.color
		<< "Big_semiaxis = " << some_ell.big_semiaxis
		<<"\nSmall_semiaxis = "<< some_ell.small_semiaxis
		<< "\n\n";
		return out;
	}
protected:
int big_semiaxis;
int small_semiaxis;
};

class ellipseSector: public Ellipse{
public:
	ellipseSector(int x=0, int y=0, int b_semi=2, int s_semi=1, int angle_start=0, int angle_finish=360):
	Ellipse(x,y,b_semi,s_semi),angle_start(angle_start), angle_finish(angle_finish){
		if (this->angle_finish > 360) this->angle_finish%=360;
		if (this->angle_start > 360) this->angle_finish%=360;
	}
	~ellipseSector(){}
	void rotate (int angle=0) override{
		Shape::rotate(angle);
		angle_start+=angle;
		angle_finish+=angle;
		if (angle_finish > 360) angle_finish%=360;
		if (angle_start > 360) angle_finish%=360;
	}
	friend std::ostream& operator<< (std::ostream& out, const ellipseSector& some_ell){
		out <<"Ellipse sector:\nID =  "<< some_ell.id<<
		"\nCentre coordinates = "<< some_ell.x <<
		"," << some_ell.y << "\nAngle of rotation = "
		<< some_ell.angle << "\nColor(R,G,B) = " <<some_ell.color
		<< "Big_semiaxis = " << some_ell.big_semiaxis
		<<"\nSmall_semiaxis = "<< some_ell.small_semiaxis
		<<"\nStart of the sector(angle) = "<< some_ell.angle_start
		<<"\nEnd of the sector(angle) = " << some_ell.angle_finish
		<< "\n\n";
		return out;
	}
protected:
int angle_start;
int angle_finish;
};
