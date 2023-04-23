#include <iostream>
#include <cmath>
#include <string>
#define STANDART_CENTRE 0
#define STANDART_TOP 1
//static int general_id=0;

class Colour
{
private:
	int red;
	int green;
	int blue;
public:
	Colour()
	{
		red=0;
		green=0;
		blue=0;
	}

    	void setcolour(int red_,int green_,int blue_)
    	{
		red=red_%255;
		green=green_%255;
		blue=blue_%255;
	}

	int getcolour()
	{
		return red*255*255+green*255+blue;
    	}
};

//одна точка
class Point
{
private:
	double x, y;
public:
    	Point()
    	{
        	x = 0;
        	y = 0;
    	}

    	Point(double _x, double _y)
    	{
        	x = _x;
        	y = _y;
    	}

    	void setx(double _x)
    	{
        	x = _x;
    	}

    	void sety(double _y)
    	{
        	y = _y;
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

//круг
//элипс
//сектор элипса

class Shape
{
protected:
static int general_id;
  	public:
  	Shape()
    	{
        	id = general_id;
        	general_id++;
    	}
    	int id;
    	Point centre;
    	Point topvertex;
    	Colour colour;
    	virtual void move(double, double) = 0;
    	virtual void resize(double) = 0;
    	virtual void turn(double) = 0;
    	friend std::ostream& operator<<(std::ostream& stream, Shape& object);
};

std::ostream& operator<<(std::ostream& stream, Shape& object)
{
        stream << "figure id:" << object.id << std::endl
               << "Color:red - " << object.colour.getcolour()/(255*255) << ",green - " << (object.colour.getcolour()%(255*255))/255 << ",blue - " << object.colour.getcolour()%255 << std::endl
               << "Centre: (" << object.centre.getx() << ", "<<object.centre.gety() << ")" << std::endl
               << "toppoint: (" << object.topvertex.getx() << ", " << object.topvertex.gety() << ")" << std::endl;
        return stream;
}

class Circle : public Shape
{
public:
    	double calculaterad(Point a, Point b)
    	{
        	return sqrt((a.getx() - b.getx()) * (a.getx() - b.getx()) + (a.gety() - b.gety()) * (a.gety() - b.gety()));
    	}

	void nana()
	{
	centre.setx(10);
	}

    	Circle()
    	{
        	centre.setx(STANDART_CENTRE);
        	centre.sety(STANDART_CENTRE);
        	topvertex.setx(STANDART_CENTRE);
        	topvertex.sety(STANDART_TOP);
    	}

    	Circle(Point centr, Point anypoint)
    	{
        	centre = centr;
        	topvertex = anypoint;
    	}

    	void move(double offsetx, double offsety) override
    	{
        	centre.setx(centre.getx() + offsetx);
        	centre.sety(centre.gety() + offsety);
        	topvertex.setx(topvertex.getx() + offsetx);
        	topvertex.sety(topvertex.gety() + offsety);
    	}

    	void resize(double k) override
    	{
        	topvertex.setx(centre.getx()+k*(topvertex.getx()-centre.getx()));
        	topvertex.sety(centre.gety()+k*(topvertex.gety()-centre.gety()));
    	}

    	void turnPoint(double a,Point &b)
    	{
		double radian;
		if(b.gety()==centre.gety())
			radian=atan(1)*2*(b.getx()-centre.getx()>0 ? 1 : -1);
		else
		{
			radian=atan((b.getx()-centre.getx())/(b.gety()-centre.gety()));
			if(b.gety()-centre.gety()<0)
				radian=radian+4*atan(1);
		}
		double radius=calculaterad(b,centre);
		b.setx(centre.getx()+radius*sin(radian-a));
		b.sety(centre.gety()+radius*cos(radian-a));
	}

	void turn(double a) override
	{
		turnPoint(a,topvertex);
	}
};

class Ellipse : public Circle
{
protected:
	Point focus;
public:
    	friend std::ostream& operator<<(std::ostream& stream, Ellipse& object);
    	Ellipse()
    	{
		Circle();
		focus.setx(STANDART_CENTRE);
		focus.sety(STANDART_CENTRE);
    	}
	void nana()
	{
	centre.setx(20);
	}

    	Ellipse(Point cen, Point foc, Point top): Circle(cen,top)
    	{
		Point secfoc(centre.getx()-focus.getx(),centre.gety()-focus.gety());
		if(calculaterad(foc,top)+calculaterad(secfoc,top)>calculaterad(foc,secfoc))
			focus=foc;
		else
		{
			centre={STANDART_CENTRE,STANDART_CENTRE};
			topvertex={STANDART_CENTRE,STANDART_TOP};
		}
    	}

    	void resize(double k) override
    	{
		Circle::resize(k);
        	focus.setx(centre.getx()+k*(focus.getx()-centre.getx()));
        	focus.sety(centre.gety()+k*(focus.gety()-centre.gety()));
    	}

    	void move(double offsetx,double offsety) override
    	{
		Circle::move(offsetx,offsety);
        	focus.setx(focus.getx() + offsetx);
        	focus.sety(focus.gety() + offsety);
    	}

    	void turn(double a) override
    	{
		Circle::turn(a);
		turnPoint(a,focus);
    	}
};

std::ostream& operator<<(std::ostream& stream, Ellipse& object)
{
        stream << "figure id:" << object.id << std::endl
               << "Color:red - " << object.colour.getcolour()/(255*255) << ",green - " << (object.colour.getcolour()%(255*255))/255 << ",blue - " << object.colour.getcolour()%255 << std::endl
               << "Centre: (" << object.centre.getx() << ", "<<object.centre.gety() << ")" << std::endl
               << "toppoint: (" << object.topvertex.getx() << ", " << object.topvertex.gety() << ")" << std::endl
		<< "focus: (" << object.focus.getx() << "," << object.focus.gety() << ")" << std::endl;
        return stream;
}

class Sector :  public Ellipse
{
public:
	Sector()
	{
		Ellipse();
        	lowpoint.setx(STANDART_CENTRE);
        	lowpoint.sety(STANDART_TOP);
	}

	Sector(Point cen, Point foc, Point top,Point low):Ellipse(cen,foc,top)
	{
		Point secfoc(centre.getx()-focus.getx(),centre.gety()-focus.gety());
		if(calculaterad(foc,top)+calculaterad(secfoc,top)>calculaterad(foc,secfoc) &&
	   	calculaterad(foc,top)+calculaterad(secfoc,top)==calculaterad(foc,low)+calculaterad(secfoc,low))
			lowpoint=low;
		else
		{
			cen={STANDART_CENTRE,STANDART_CENTRE};
			focus={STANDART_CENTRE,STANDART_CENTRE};
			topvertex={STANDART_CENTRE,STANDART_TOP};
		}
	}

    	void resize(double k) override
    	{
		Ellipse::resize(k);
        	lowpoint.setx(centre.getx()+k*(lowpoint.getx()-centre.getx()));
        	lowpoint.sety(centre.gety()+k*(lowpoint.gety()-centre.gety()));
    	}

    	void move(double offsetx,double offsety) override
	{
		Ellipse::move(offsetx,offsety);
        	lowpoint.setx(lowpoint.getx() + offsetx);
        	lowpoint.sety(lowpoint.gety() + offsety);
    	}

    	void turn(double a) override
    	{
		Ellipse::turn(a);
		turnPoint(a,lowpoint);
    	}

	friend std::ostream& operator<<(std::ostream& stream, Sector& object);

protected:
	Point lowpoint;
};

std::ostream& operator<<(std::ostream& stream, Sector& object)
{
	stream << "figure id:" << object.id << std::endl
               << "Color:red - " << object.colour.getcolour()/(255*255) << ",green - " << (object.colour.getcolour()%(255*255))/255 << ",blue - " << object.colour.getcolour()%255 << std::endl
               << "Centre: (" << object.centre.getx() << ", "<<object.centre.gety() << ")" << std::endl
               << "toppoint: (" << object.topvertex.getx() << ", " << object.topvertex.gety() << ")" << std::endl
		<< "focus: (" << object.focus.getx() << "," << object.focus.gety() << ")" << std::endl
		<< "lowpoint: (" << object.lowpoint.getx() << "," << object.lowpoint.gety() << ")" << std::endl;
        return stream;
}

int Shape::general_id=0;

int main(int argc, char const *argv[])
{
//	general_id=0;
	Circle circle({0,0}, {1,2});
/*    	Circle circle2({0,0},{1,0});
    	Circle circle3({0,0},{-2,-1});
    	Circle circle4({0,0},{-1,0});
    	Circle circle5({0,0},{1,1});
    	Circle circle6({0,0},{1,-1});
    	Circle circle7({0,0},{-1,-1});
   	Circle circle8({0,0},{-1,1});*/
   	std::cout << circle << std::endl;
	circle.colour.setcolour(12,9,234);
    	circle.turn(atan(1)*4);
    	std::cout << circle << std::endl << std::endl;
/*    	std::cout << circle2 << std::endl;
    	circle2.turn(atan(1)*4);
    	std::cout << circle2 << std::endl << std::endl;
    	std::cout << circle3 << std::endl;
    	circle3.turn(atan(1)*2);
    	std::cout << circle3 << std::endl << std::endl;
    	std::cout << circle4 << std::endl;
    	circle4.turn(atan(1)*4);
    	std::cout << circle4 << std::endl << std::endl;
    	std::cout << circle5 << std::endl;
    	circle5.turn(atan(1)*4);
    	std::cout << circle5 << std::endl << std::endl;
    	std::cout << circle6 << std::endl;
    	circle6.turn(atan(1)*4);
    	std::cout << circle6 << std::endl << std::endl;
    	std::cout << circle7 << std::endl;
    	circle7.turn(atan(1)*4);
    	std::cout << circle7 << std::endl << std::endl;
    	std::cout << circle8 << std::endl;
    	circle8.turn(atan(1)*4);
    	std::cout << circle8 << std::endl << std::endl;*/
//	Shape::general_id=0;

    	Ellipse ellipse({1,1},{0,1},{1,2});
    	ellipse.colour.setcolour(0,254,255);
    	std::cout << ellipse << std::endl;
	circle.nana();
    	std::cout << "!" << circle << std::endl << std::endl;
        ellipse.Circle::nana();
	    	std::cout << ellipse << std::endl;

    	Sector sixstar({0,0},{1,0},{0,1},{0,-1});
    	std::cout << sixstar << std::endl;

    	sixstar.colour.setcolour(0,0,254);
    	sixstar.move( -1, 6);
    	std::cout << sixstar << std::endl;
    	sixstar.turn(4*atan(1));
    	std::cout << sixstar << std::endl;
    	return 0;
}
