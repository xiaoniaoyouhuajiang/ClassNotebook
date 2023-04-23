#include"base.h"
int Shape::ID = 1;
void Shape:: printShape()
{  
	int i =0;
	cout<< "ID фигуры: id=" << Id << "\n";
	cout << "Цвет: " << Color<< "\n";
	cout << "Центр : X = " << Centre.X << " ,Y = " << Centre.Y<< endl;
	while(i<4){
	    cout <<"Координата  вершины : X"<<i+1<<" = "<< this->Vertex[i].X << " ,Y"<<i+1<<" = " <<this-> Vertex[i].Y << endl;
	    i++;
	}
}

void Shape::Turn(const double& R)
{   cout << "Угол поворота: А = " << R << endl;
    for(int i=0;i<4;i++){
		Vertex[i] = Turnus(R,Vertex[i], Centre);
	}
}
void Shape:: move(const double& x,const double& y)
{   for(int i=0;i<4;i++){
		Vertex[i] = Movus(x,y,Vertex[i], Centre);
	}
	this->Centre.X = x;
	this->Centre.Y = y;

}
void Shape:: Mahtab(const double& P)
{   for(int i=0;i<4;i++){
		Vertex[i] = Mahtabus(P,Vertex[i], Centre);
	}
}
void Shape:: SetColorFigure(const string &color)
{
    this->Color = color;
}
string Shape:: GetColorFigure()
{
	return Color;
}
bool Shape:: CommonSide(const Shape& shape2)
{   double arr1[3];double arr2[3];
	for(int i=0;i<4;i++)
	{   int m=i+1;
	    if(i==3) {m=0;}//чтобы построить сторону из первой и последней вершины
		//запоминаем коэффициенты прямой 0=Аx+By+C для стороны первой фигуры
		arr1[0]=Vertex[i].Y-Vertex[m].Y;
	    arr1[1]=Vertex[m].X-Vertex[i].X;
	    arr1[2]=(Vertex[i].X*Vertex[m].Y)-(Vertex[m].X*Vertex[i].Y);
		for(int j=0;j<4;j++)
		{   int r=i+1;
	        if(i==3) {r=0;}//запоминаем коэффициенты прямой 0=Аx+By+C для стороны второй фигуры
			arr2[0]=shape2.Vertex[j].Y-shape2.Vertex[r].Y;
	        arr2[1]=shape2.Vertex[r].X-shape2.Vertex[j].X;
	        arr2[2]=(shape2.Vertex[i].X*shape2.Vertex[r].Y)-(shape2.Vertex[r].X*shape2.Vertex[j].Y);
			if((arr1[0]==arr2[0]&&arr1[1]==arr2[1]&&arr1[2]==arr2[2])||(-arr1[0]==arr2[0]&&-arr1[1]==arr2[1]&&-arr1[2]==arr2[2])){
			//если уравнения прямых совпадают
			    if(Vertex[i].X!=Vertex[m].X)//если прямая не вертикальна
				{    //если первый отрезок больше второго
					if((Vertex[i].X>=shape2.Vertex[r].X&&Vertex[i].X>=shape2.Vertex[j].X&&
					Vertex[m].X<=shape2.Vertex[r].X&&Vertex[m].X<=shape2.Vertex[j].X)||	
					(Vertex[m].X>=shape2.Vertex[r].X&&Vertex[m].X>=shape2.Vertex[j].X&&
					Vertex[i].X<=shape2.Vertex[r].X&&Vertex[i].X<=shape2.Vertex[j].X)||
					//если отрезок второй фигуры больше чем первой
				    (shape2.Vertex[j].X>=Vertex[m].X&&shape2.Vertex[j].X>=Vertex[i].X&&
					shape2.Vertex[r].X<=Vertex[m].X&&shape2.Vertex[r].X<=Vertex[i].X)||	
					(shape2.Vertex[r].X>=Vertex[m].X&&shape2.Vertex[r].X>=Vertex[i].X&&
					shape2.Vertex[j].X<=Vertex[m].X&&shape2.Vertex[j].X<=Vertex[i].X))
					{
					    return true;
					}
				
				}
				else //сравниваем по  координате У
				{    //если первый отрезок больше второго
					if((Vertex[i].Y>=shape2.Vertex[r].Y&&Vertex[i].Y>=shape2.Vertex[j].Y&&
					Vertex[m].Y<=shape2.Vertex[r].Y&&Vertex[m].Y<=shape2.Vertex[j].Y)||	
					(Vertex[m].Y>=shape2.Vertex[r].Y&&Vertex[m].Y>=shape2.Vertex[j].Y&&
					Vertex[i].Y<=shape2.Vertex[r].Y&&Vertex[i].Y<=shape2.Vertex[j].Y)||
					//если отрезок второй фигуры больше чем первой
				    (shape2.Vertex[j].Y>Vertex[m].Y&&shape2.Vertex[j].Y>=Vertex[i].Y&&
					shape2.Vertex[r].Y<=Vertex[m].Y&&shape2.Vertex[r].Y<=Vertex[i].Y)||	
					(shape2.Vertex[r].Y>=Vertex[m].Y&&shape2.Vertex[r].Y>=Vertex[i].Y&&
					shape2.Vertex[j].Y<=Vertex[m].Y&&shape2.Vertex[j].Y<=Vertex[i].Y))
					{
					    return true;
					}

				
				}
			}
		
		}

	}
	return false;
}
	