#include "Pentagon.h"

//Конструктор
Pentagon::Pentagon(Point &a0, Point &a1, Point &a2, Point &a3, Point &a4, Color &color) : Shape( color, Point((a0.x+a1.x+a2.x+a3.x+a4.x)/5,(a0.y+a1.y+a2.y+a3.y+a4.y)/5) )
{
	points[0] =  Point(a0);
	points[1] =  Point(a1);
	points[2] =  Point(a2);
	points[3] =  Point(a3);
	points[4] =  Point(a4);
}

// Узнать точки пятиугольника
const Point * Pentagon::Get_Points() const
{
	return points;
}


// Cмещение центра в (x;y)
void Pentagon::Move( double x, double y) 
{
	x -= centrum.x;		//
	y -= centrum.y;		// определяем смещение

	centrum.x += x;
	centrum.y += y;

	points[0].x +=  x; points[0].y +=  y;
	points[1].x +=  x; points[1].y +=  y;
	points[2].x +=  x; points[2].y +=  y;
	points[3].x +=  x; points[3].y +=  y;
	points[4].x +=  x; points[4].y +=  y;
}


// Вращение относительно центра масс
void Pentagon::Rotate( double angle)     
{
	for (int i=0; i<5; i++)
	{
		double r = sqrt( (points[i].x-centrum.x)*(points[i].x-centrum.x) + (points[i].y-centrum.y)*(points[i].y-centrum.y));
		double angle_0 = acos(  (points[i].x-centrum.x)/r  );

			if ( (points[i].y-centrum.y) < 0 ) angle_0 += 2*( acos((double)-1)-angle_0 ); 

		angle_0 += angle;

		points[i].x = r*cos(angle_0) + centrum.x;
		points[i].y = r*sin(angle_0) + centrum.y;
	}
}

// Масштабирование относительно центра масс
void Pentagon::Scale(double scale)     
{
	for (int i=0; i<5; i++)
	{
		double r = sqrt( (points[i].x-centrum.x)*(points[i].x-centrum.x) + (points[i].y-centrum.y)*(points[i].y-centrum.y));
		double angle_0 = acos(  (points[i].x-centrum.x)/r  );

			if ( (points[i].y-centrum.y) < 0 ) angle_0 += 2*( acos((double)-1)-angle_0 ); 

		points[i].x = r*cos(angle_0)*scale + centrum.x;
		points[i].y = r*sin(angle_0)*scale + centrum.y;
	}
}

// Вывод в поток инфорации о пятиугольнике
std::ostream &operator <<(std::ostream &out, const Pentagon &pentagon)
{
	const Point *points = pentagon.Get_Points();

	for (int i=0;i<5;i++)
		out<< "(" << points[i].x << " ; " << points[i].y << ") ";

	out << std::endl << (const Shape &)pentagon;

	return out;
}