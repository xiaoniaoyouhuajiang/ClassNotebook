
#include <iostream>
#include <cmath>
#include <string>



class Colour
{
private:
	int red;
	int green;
	int blue;
public:
	Colour(int _red=0, int _green=0, int _blue=0) : red(_red), green(_green), blue(_blue)
	{}

	int get_red()
	{
		return red;
    }
    
    int get_green()
	{
		return green;
    }
    
    int get_blue()
	{
		return blue;
    }
};


class Point
{
private:
	double x, y;
public:
    	
    	Point(double _x=0, double _y=0) : x(_x), y(_y)
    	{}
        	

    	void setx(double _x) 
    	{
    		x=_x;
		}
        	
    	void sety(double _y) 
    	{
    		y=_y;
		}

    	double getx() 
    	{
        	return x;
    	}

    	double gety()
    	{
        	return y;
    	}
};


class Shape
{
protected:
static int _id;
Point center;
Point top_point;
Colour colour;

  	public:
  		Shape(Colour clr) : colour(clr)
    	{
        	id = _id;
        	_id++;
    	}
    	
    	int id;
    	virtual void move(double, double) = 0;
    	virtual void scalling(double) = 0;
    	virtual void turn(double) = 0;
    	friend std::ostream& operator<<(std::ostream& stream, Shape& object);
};

std::ostream& operator<<(std::ostream& stream, Shape& object)
{
        stream << "Figure id(Square):" << object.id << std::endl
               << "Colour: R - " << object.colour.get_red() << ", G - " << object.colour.get_green() << ", B - " << object.colour.get_blue() << std::endl
               << "Center: (" << object.center.getx() << ", "<<object.center.gety() << ")" << std::endl
               << "Top1: (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
        object.turn(atan(1)*2);
        stream << "Top2: (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
		object.turn(atan(1)*2);
		stream << "Top3: (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
		object.turn(atan(1)*2);
		stream << "Top4: (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
		object.turn(atan(1)*2);       
        return stream;
}

class Square : public Shape
{
protected:
		double Square_sqr;
public:
    	double distance(Point a, Point b)
    	{
        	return sqrt((a.getx() - b.getx()) * (a.getx() - b.getx()) + (a.gety() - b.gety()) * (a.gety() - b.gety()));
    	}

    	Square(Colour color,Point centr={0,0}, Point anypoint={0,1}) : Shape(color)
    	{
        	center = centr;
        	top_point = anypoint;
    	}

    	void move(double offsetx, double offsety) 
    	{
        	center.setx(center.getx() + offsetx);
        	center.sety(center.gety() + offsety);
        	top_point.setx(top_point.getx() + offsetx);
        	top_point.sety(top_point.gety() + offsety);
    	}

		double Sqr()
		{
			return 	distance(center, top_point)*distance(center, top_point)*2;
		}
		

    	void scalling(double k) 
    	{
        	top_point.setx(center.getx()+k*(top_point.getx()-center.getx()));
        	top_point.sety(center.gety()+k*(top_point.gety()-center.gety()));
    	}

    	void turnPoint(double a,Point &b)
    	{
		double radian;
		if(b.gety()==center.gety())
			radian=atan(1)*2*(b.getx()-center.getx()>0 ? 1 : -1);
		else
		{
			radian=atan((b.getx()-center.getx())/(b.gety()-center.gety()));
			if(b.gety()-center.gety()<0)
				radian=radian+4*atan(1);
		}
		double line=distance(b,center);
		b.setx(center.getx()+line*sin(radian-a));
		b.sety(center.gety()+line*cos(radian-a));
	}

	void turn(double a) 
	{
		turnPoint(a,top_point);
	}
};

class Ellipse : public Square
{
protected:
	Point focus;
	double Ellipse_sqr;
public:
    	friend std::ostream& operator<<(std::ostream& stream, Ellipse& object);


    	Ellipse(Colour clrr, Point cen, Point foc, Point top): Square(clrr,cen,top)
    	{
		Point secfoc(center.getx()-focus.getx(),center.gety()-focus.gety());
		if(distance(foc,top)+distance(secfoc,top)>distance(foc,secfoc))
			focus=foc;
		else
		{
			center={0,0};
			top_point={0,1};
			focus.setx(0);
			focus.sety(0);
		}
    	}
		
		
		
    	void scalling(double k) 
    	{
			Square::scalling(k);
        	focus.setx(center.getx()+k*(focus.getx()-center.getx()));
        	focus.sety(center.gety()+k*(focus.gety()-center.gety()));
    	}

    	void move(double offsetx,double offsety) 
    	{
			Square::move(offsetx,offsety);
        	focus.setx(focus.getx() + offsetx);
        	focus.sety(focus.gety() + offsety);
    	}

    	void turn(double a) 
    	{
			Square::turn(a);
			turnPoint(a,focus);
    	}
};

std::ostream& operator<<(std::ostream& stream, Ellipse& object)
{
        stream << "Figure id(Ellipse):" << object.id << std::endl
               << "Colour: R - " << object.colour.get_red() << ", G - " << object.colour.get_green() << ", B - " << object.colour.get_blue() << std::endl
               << "Centre: (" << object.center.getx() << ", "<<object.center.gety() << ")" << std::endl
               << "Top: (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl
			   << "Focus: (" << object.focus.getx() << "," << object.focus.gety() << ")" << std::endl;
        return stream;
}

class Pentagon :  public Square
{
protected:
	double Pentagon_sqr;
public:
	Pentagon(Colour clor,Point cent, Point anypoin) : Square(clor, cent, anypoin)
	{}
	
	double Sqr()
	{
		Point a=top_point;
		Square::turn(atan(1)*8/5);
		double b=distance(a, top_point);
		return 5*b*b/4*tan(atan(1)*8/10);
	}
	
    	friend std::ostream& operator<<(std::ostream& stream, Pentagon& object);
};

std::ostream& operator<<(std::ostream& stream, Pentagon& object)
{
        stream << "Figure id(Pentagon):" << object.id << std::endl
               << "Colour: R - " << object.colour.get_red() << ", G - " << object.colour.get_green() << ", B - " << object.colour.get_blue() << std::endl
               << "Center: (" << object.center.getx() << ", "<<object.center.gety() << ")" << std::endl
               << "Top1 : (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
        object.turn(atan(1)*8/5);
        stream << "Top2 : (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
		object.turn(atan(1)*8/5);
		stream << "Top3 : (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
		object.turn(atan(1)*8/5);
		stream << "Top4 : (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
		object.turn(atan(1)*8/5);  
		stream << "Top5 : (" << object.top_point.getx() << ", " << object.top_point.gety() << ")" << std::endl;
		object.turn(atan(1)*8/5);     
        return stream;
}

int Shape::_id=0;

int main(){
	Square a({1,1,1},{0,0}, {1,2});
	std::cout << a.Sqr() << std::endl;
	Ellipse b({1,1,2},{0,0}, {0,1},{0,2});
	
	Pentagon c({1,1,3},{0,0}, {1,2});
	std::cout << c.Sqr() << std::endl;
	std::cout << a << b << c << std::endl;
	return 0;
}
