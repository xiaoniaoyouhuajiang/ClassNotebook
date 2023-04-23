#include <iostream>
#include <cmath>
 
class Shapes                                           
 { protected:
   // static int count;
    int color;
    float left_x, left_y, right_x, right_y;
   // Shapes()  { count++; }

   public:
   // virtual ~Shapes() { count--; }                  

   // static int GetCount() { return count;  }
    virtual void Print() = 0;        
    void Draw(int new_color = 0) {color = new_color;}   
    int getDraw() { return color;  }                
    virtual void Move(float new_x, float new_y) = 0;
    virtual void Scale(float k) = 0;
    virtual void Turn(float angle) = 0;
  };

class Ellipse : public Shapes
 { private:
    float ex, ey, ea, eb;
   public:
   
   void Print() {
	   std::cout<<"Координаты центра: "<<ex<<' '<<ey<<std::endl;
	   std::cout<<"Радиусы: "<<ea<<' '<<eb<<std::endl;
	   std::cout<<"Координаты верхнего левого угла: "<<left_x<<' '<<left_y<<std::endl;
	   std::cout<<"Координаты нижнего правого угла: "<<right_x<<' '<<right_y<<std::endl;
	   std::cout<<"Цвет: "<<color<<std::endl;}
   
    Ellipse(float x = 0, float y = 0, float a = 0, float b = 0, int c = 0)
    {
		ex = x; ey = y;   
		ea = a; eb = b;
		left_x = x - a; left_y = y + b; 
		right_x = x + a; right_y = y - b;
	    color = c;
	}
	
    //~Ellipse() { }
	
    void Move(float new_x, float new_y)
    {
		ex = new_x; ey = new_y;
		left_x = new_x - ea; left_y = new_y + eb; 
		right_x = new_x + ea; right_y = new_y - eb;
	}
	
	void Scale(float k)
	{
		ea = ea * k; eb = eb * k;
		left_x = left_x * k; left_y = left_y * k; 
		right_x = right_x * k; right_y = right_y * k;
	}
	
	void Turn(float angle)
	{
		float x, y;
		x = left_x*cos(angle)+left_y*sin(angle);
		y = -left_x*sin(angle)+left_y*cos(angle);
		left_x = x; left_y = y;
		x = right_x*cos(angle)+right_y*sin(angle);
		y = -right_x*sin(angle)+right_y*cos(angle);
		right_x = x; right_y = y;
	}
  };
 
 class Trapeze : public Shapes
 { private:
    float tx, ty, ta1, ta2, height, side;
   public:
   
   void Print() {
	   std::cout<<"Координаты крайней точки: "<<tx<<' '<<ty<<std::endl;
	   std::cout<<"Высота и сторона: "<<height<<' '<<side<<std::endl;
	   std::cout<<"Углы при основании: "<<ta1<<' '<<ta2<<std::endl;
	   std::cout<<"Координаты верхнего левого угла: "<<left_x<<' '<<left_y<<std::endl;
	   std::cout<<"Координаты нижнего правого угла: "<<right_x<<' '<<right_y<<std::endl;
	   std::cout<<"Цвет: "<<color<<std::endl;}
   
    Trapeze(float x = 0, float y = 0, float s = 0, float h = 0, float a1 = 0, float a2 = 0, int c = 0)
    {
		tx = x; ty = y;   
		ta1 = a1; ta2 = a2;
		side = s; height = h;
		left_x = x; left_y = y + h; 
		right_x = x + s; right_y = y;
	    color = c;
	}
	
    //~Trapeze() { }
	
    void Move(float new_x, float new_y)
    {
		tx = new_x; ty = new_y;
		left_x = new_x; left_y = new_y + height; 
		right_x = new_x + side; right_y = new_y;
	}
	
	void Scale(float k)
	{
		side = side * k; height = height * k;
		left_x = left_x; left_y = left_y * k; 
		right_x = right_x * k; right_y = right_y;
	}
	
	void Turn(float angle)
	{
		float x, y;
		x = left_x*cos(angle)+left_y*sin(angle);
		y = -left_x*sin(angle)+left_y*cos(angle);
		left_x = x; left_y = y;
		x = right_x*cos(angle)+right_y*sin(angle);
		y = -right_x*sin(angle)+right_y*cos(angle);
		right_x = x; right_y = y;
	}
  };
 
 class Pentagon : public Shapes
 { private:
    float coordinates[5][2];
   public:
   
   void Print() {
	   for (int i = 0; i < 5; i++)
	   {
		   std::cout<<"Координаты углов: "<<coordinates[i][0]<<' '<<coordinates[i][1]<<std::endl;
	   }
	   std::cout<<"Координаты верхнего левого угла: "<<left_x<<' '<<left_y<<std::endl;
	   std::cout<<"Координаты нижнего правого угла: "<<right_x<<' '<<right_y<<std::endl;
	   std::cout<<"Цвет: "<<color<<std::endl;}
   
    Pentagon(float (&coord)[5][2], int c = 0)
    {
		float x1 = coord[0][0], x2 = coord[0][0], 
			  y1 = coord[0][1], y2 = coord[0][1];
		for(int i = 0; i<5; i++)
			{coordinates[i][0]=coord[i][0]; coordinates[i][1]=coord[i][1];
			 if(x1>coord[i][0]) x1=coord[i][0];
			 if(x2<coord[i][0]) x2=coord[i][0];
			 if(y1<coord[i][1]) y1=coord[i][1];
			 if(y2>coord[i][1]) y2=coord[i][1];}
		left_x = x1; left_y = y1; 
		right_x = x2; right_y = y2;
	    color = c;
	}
	
   // ~Pentagon() { }
	
    void Move(float new_x, float new_y)
    {
		for(int i=4; i>0;i--)
			{coordinates[i][0] = new_x + (coordinates[i][0] - coordinates[0][0]); 
			 coordinates[i][1] = new_y + (coordinates[i][1] - coordinates[0][1]); }
			 
		if((left_x == coordinates[0][0]) && (left_y == coordinates[0][1])) {left_x = new_x; left_y = new_y;}
		else {left_x = new_x + (left_x - coordinates[0][0]); left_y = new_y + (left_y - coordinates[0][1]);}
		
		if((right_x == coordinates[0][0]) && (right_y == coordinates[0][1])) {right_x = new_x; right_y = new_y;}
		else {right_x = new_x + (right_x - coordinates[0][0]); right_y = new_y + (right_y - coordinates[0][1]);}
		
		coordinates[0][0] = new_x; coordinates[0][1] = new_y;
	}
	
	void Scale(float k)
	{
		for(int i=4; i>0;i--)
			{coordinates[i][0] = coordinates[i][0] * k; 
			 coordinates[i][1] = coordinates[i][1] * k;}
			 
		if ((left_x == coordinates[0][0]) && (left_y != coordinates[0][1])) {left_y = left_y * k;}
		if ((left_x != coordinates[0][0]) && (left_y == coordinates[0][1])) {left_x = left_x * k;}
		if ((left_x != coordinates[0][0]) && (left_y != coordinates[0][1])) {left_x = left_x * k; left_y = left_y * k;}
		
		if ((right_x == coordinates[0][0]) && (right_y != coordinates[0][1])) {right_y = right_y * k;}
		if ((right_x != coordinates[0][0]) && (right_y == coordinates[0][1])) {right_x = right_x * k;}
		if ((right_x != coordinates[0][0]) && (right_y != coordinates[0][1])) {right_x = right_x * k; right_y = right_y * k;}
		
	}
	
	void Turn(float angle)
	{
		float x, y;
		
		for(int i=4; i>0;i--)
			{x = coordinates[i][0]*cos(angle)+coordinates[i][1]*sin(angle);
			 y = -coordinates[i][0]*sin(angle)+coordinates[i][1]*cos(angle);
			 coordinates[i][0] = x; coordinates[i][1] = y;}
			 
		x = left_x*cos(angle)+left_y*sin(angle);
		y = -left_x*sin(angle)+left_y*cos(angle);
		left_x = x; left_y = y;
		
		x = right_x*cos(angle)+right_y*sin(angle);
		y = -right_x*sin(angle)+right_y*cos(angle);
		right_x = x; right_y = y;
	}
  };
