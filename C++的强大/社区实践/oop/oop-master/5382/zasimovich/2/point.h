#ifndef _POINT_
#define _POINT_
#include <cmath>
const double PI = 4*atan(1.0);
class Point
{
public:
		double X;double Y;
		Point(double x = 0, double y = 0)
		{X = x; Y = y;};

		//double getX()
		//{ return X;}
		//double getY()
		//{ return Y;}
		//void setX(double x)
		//{ X = x;}
		//void setY(double y)
		//{ Y = y;}
		friend Point Mahtabus(const double& P,const Point& point,const Point& centre){//маштабирование в P раз точки point относительно центра
		     Point point1;
			 point1.X = centre.X+(point.X-centre.X )* P ;
             point1.Y = centre.Y+(point.Y-centre.Y )* P ;
		     return point1;
		}
		friend Point Movus(const double& x,const double& y,const Point& point,const Point& centre){//перемещение точки, анологичное перемещению центра
		    Point point1;
			point1.X =point.X + x-centre.X ;
	        point1.Y =point.Y+ y-centre.Y;
		    return point1;
		
		}
		friend Point Turnus(const double& angle,const Point& point,const Point& centre){//поворот точки относительно центра
			Point point1;
		    point1.X =centre.X+(point.X-centre.X)*cos((angle)*PI/180)-(point.Y-centre.Y)*sin((angle)*PI/180);	
	        point1.Y = centre.Y+ (point.X-centre.X)*sin((angle)*PI/180)+(point.Y-centre.Y)*cos((angle)*PI/180);
		    return point1;
		}

		friend double Distance(const Point& point,const Point& centre){//поворот точки относительно центра
			
		    return sqrt(pow((point.X-centre.X),2)+pow((point.Y-centre.Y ),2));
		}



};

#endif
