#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

static int count = 0;      //глобальная внутренняя переменная

struct Point {             //структура координат
    double x, y;
    Point():x(0),y(0) {}   //конструктор по умолчанию, т.е если не инициализируем, то будет ноль
    Point(double curr_x, double curr_y):x(curr_x), y(curr_y) {} //если не нули, то передаём нужное значение
};

struct Color {             //структура цвета
    unsigned red;
    unsigned green;
    unsigned blue;
    Color(): red(0), green(0),blue(0) {}
    Color(unsigned r, unsigned g, unsigned b) : red(r), green(g), blue(b) {}
};

class Shape {              //класс фигура (любая)
public:

    Shape():id(count),angle(0), color() {
        count++;
    }                      //конструктор по умолчанию, count всегда передаём, фигура изначально не повернута, и вызываем конструктор цвета и координат

    Shape(int id, double curr_angle, Color curr_color):id(count), angle(curr_angle), color(curr_color) {
        count++;           //конструктор по заданным значениям
    }

    double get_angle() {   //взятие угла фигуры (для печати используем)
        return angle;
    }

    int get_id() {         //взятие индивидуального адреса фигуры
        return id;
    }

    Color get_color() {    //взятие цвета фигуры
        return color;
    }

    void set_color(unsigned r,unsigned g,unsigned b){
        color.red = r;
        color.green = g;
        color.blue = b;
    }

    virtual ~Shape() {
        id--;
    }

    virtual void move(const Point new_place) = 0;
    virtual void rotate(int curr_angle) = 0;
    virtual void scale(double multiplier) = 0;
    virtual void print(ostream &out) = 0;    //определение вертуальной функции, поток вывода
    virtual void data_of_shape() = 0;       
    friend ostream& operator << (ostream &out, Shape* shape); //перегрузка оператора

protected:                                   //возможность изменения в наследниках
    double angle;
    int id;
    Color color;
};

ostream& operator << (ostream& out, Shape* shape) {
    out << "Данные о фигуре:"<<endl;
    out << "Цвет (RGB): " <<"("<< shape->get_color().red << ","<< shape->get_color().green << ","<< shape->get_color().blue << ")" << endl;
    out << "Угол поворота = " << shape->get_angle() << endl;
    out << "Id: " << shape->get_id() << endl;
    shape->print(out);
    out << "---------------------------------------------------------------------"<<endl;
    return out;
}

class Square : public Shape {
private:
	Point center;
	Point *arr;
	double side, area;
public:
    	Square(const Point A, const Point _center, const Color curr_color) : Shape(count, 0, curr_color) { 
        center = _center;
	arr = new Point[4];
	memset(arr, 0, sizeof(Point)*4);
	id++;
	arr[0] = A;
	double dif = abs(arr[0].x - center.x);
	arr[1] = {arr[0].x + 2 * dif, arr[0].y};
	arr[2] = {arr[0].x + 2 * dif, arr[0].y - 2 * dif};
	arr[3] = {arr[0].x, arr[0].y - 2 * dif};
    }

	void move(const Point new_place) override {       
        double dx = new_place.x - center.x;  
        double dy = new_place.y - center.y;
        center.x += dx;
        center.y += dy;
        for(int i = 0; i < 4; i++) {            
            arr[i].x += dx;
            arr[i].y += dy;
        }
    }
	
	void rotate(int curr_angle) override {
        angle = angle + curr_angle;          
        curr_angle = curr_angle % 360;       
        double rad = curr_angle*M_PI/180;   
        double x, y; 
        for(int i = 0; i < 4; i++) {           
            x = arr[i].x;                      
            y = arr[i].y;
            arr[i].x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x; //матрица поворота
            arr[i].y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
        }

    }
	
	void scale(double multiplier) override {         
        double x, y;
        for(int i = 0; i < 4; i++) {
            x = arr[i].x; 
            y = arr[i].y;
            arr[i].x = center.x + (x - center.x) * multiplier;
            arr[i].y = center.y + (y - center.y) * multiplier;
        }
	}
	
    void data_of_shape() override {         //защита от опечатки, т.е мы используем функцию из shape
        side = 2 * abs(arr[0].x - center.x);
	area = side * side;
    }

    void print(ostream &out) override {
	data_of_shape();
	out << "Координаты центра: " <<"("<< center.x << ";" << center.y << ")" << endl;
	out << "Площадь = " << area << endl;
        out << "Сторона квадрата: " << side << endl;
        out << "Координаты вершин: ";
        for(int i = 0; i < 4; i++) {
            out << i << ": (" << arr[i].x << "; " << arr[i].y << ") || ";
        }
        out << endl;
    }

    ~Square() {
	delete[] arr;
        id--;
	}
};

class Pentagon : public Shape {
private:
	Point center;
	Point *arr;
	double side, area;
	
	void push_points(Point A) {
        arr[0] = A;
	Point tmp;
	tmp = A;
	for (int i = 1; i < 5; i++) 
		arr[i] = rotate_point(tmp, 72);
    }
	
	Point rotate_point(Point &P, int curr_angle) {
        double rad = curr_angle*M_PI/180;
        double x, y;
        x = P.x;
        y = P.y;
        P.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
        P.y = (x - center.x) * sin(rad) - (y - center.y) * cos(rad) + center.y;
        return P;
    }
	
public:
    Pentagon(const Point _center, const Point A, const Color curr_color) : Shape(count, 0, curr_color) {
        center = _center;
	id++;
        arr = new Point[5];
	memset(arr, 0, sizeof(Point)*5);
        push_points(A);
    }
	
	void move(const Point new_place) override {       
        double dx = new_place.x - center.x;  
        double dy = new_place.y - center.y;
        center.x += dx;
        center.y += dy;
        for(int i = 0; i < 5; i++) {            
            arr[i].x += dx;
            arr[i].y += dy;
        }
    }
	
	void rotate(int curr_angle) override {
        angle = angle + curr_angle;          
        curr_angle = curr_angle % 360;       
        double rad = curr_angle*M_PI/180;   
        double x, y; 
        for(int i = 0; i < 5; i++) {           
            x = arr[i].x;                      
            y = arr[i].y;
            arr[i].x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x; //матрица поворота
            arr[i].y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
        }

    }
	
	void scale(double multiplier) override {         
        double x, y;
        for(int i = 0; i < 5; i++) {
            x = arr[i].x; 
            y = arr[i].y;
            arr[i].x = center.x + (x - center.x) * multiplier;
            arr[i].y = center.y + (y - center.y) * multiplier;
        }
	}

    void data_of_shape() override {
        side = sqrt(pow((arr[0].x - arr[1].x), 2.0) + pow((arr[0].y - arr[1].y), 2.0));
	area = 5*pow(side, 2.0)/(tan(M_PI/5)*4);
    }

    void print(ostream &out) override {
	data_of_shape();
	out << "Координаты центра: " <<"("<< center.x << ";" << center.y << ")" << endl;
	out << "Площадь = " << area << endl;
        out << "Сторона правильного пятиугольника: " << side << endl;
        out << "Координаты вершин: " ;
        for(int i = 0; i < 5; i++) {
            out << i << ": (" << arr[i].x << "; " << arr[i].y << ") || ";
        }
        out << endl;
    }

    ~Pentagon() {
	delete[] arr;
        id--;
	}
};

class Fivepointed_star: public Pentagon {
private:
	Point center;
	Point *arr;
	double side, area;
public:
    Fivepointed_star(const Point _center, double radius_big, const Color curr_color) : Pentagon(Point(_center), Point(center.x + radius_big, center.y), curr_color) {
        center = _center;
	arr = new Point[10];
	memset(arr, 0, sizeof(Point)*10);
        Point A = Point(center.x + radius_big, center.y);
	Point tmp = {center.x + (radius_big*cos(2*M_PI/5)/cos(M_PI/5)), center.y};
	arr[0] = A;
	arr[1].x = (tmp.x - center.x) * cos(36*M_PI/180) - (tmp.y - center.y) * sin(36*M_PI/180) + center.x;
	arr[1].y = (tmp.x - center.x) * sin(36*M_PI/180) - (tmp.y - center.y) * cos(36*M_PI/180) + center.y;
	double rad = 72*M_PI/180;
	for (int i = 2; i < 10; i++) { 
		arr[i].x =(arr[i-2].x - center.x) * cos(rad) - (arr[i-2].y - center.y) * sin(rad) + center.x;
		arr[i].y = (arr[i-2].x - center.x) * sin(rad) - (arr[i-2].y - center.y) * cos(rad) + center.y;
	}
    }

    void data_of_shape() override {
        side = sqrt(pow((arr[0].x - arr[1].x), 2.0) + pow((arr[0].y - arr[1].y), 2.0));
	double AB = side;
        double BC = abs(arr[0].x - center.x)*cos(2*M_PI/5)/cos(M_PI/5); //соотношение радиусов вписанной и описанной окружностей
        double CA = abs(arr[0].x - center.x);
        double p = (AB+BC+CA)/2;
        area = 10 * sqrt(p*(p-AB)*(p-BC)*(p-CA));
    }

    void print(ostream &out) override {
        data_of_shape();
	out << "Координаты центра: " <<"("<< center.x << ";" << center.y << ")" << endl;
	out << "Площадь = " << area << endl;
        out << "Сторона пятиконечной звезды: " << side << endl;
        out << "Координаты вершин: " ;
        for(int i = 0; i <  10; i = i + 2) {
            out << i << ": (" << arr[i].x << "; " << arr[i].y << ") || ";
        }
        out << endl;
        out << "Координаты пересечений: " ;
        for(int j = 1; j < 10; j = j + 2) {
            out << j << ": (" << arr[j].x << "; " << arr[j].y << ") || ";
        }
        out << endl;
    }
	
	void move(const Point new_place) override {       
        double dx = new_place.x - center.x;  
        double dy = new_place.y - center.y;
        center.x += dx;
        center.y += dy;
        for(int i = 0; i < 10; i++) {            
            arr[i].x += dx;
            arr[i].y += dy;
        }
    }
	
	void rotate(int curr_angle) override {
        angle = angle + curr_angle;          
        curr_angle = curr_angle % 360;       
        double rad = curr_angle*M_PI/180;   
        double x, y; 
        for(int i = 0; i < 10; i++) {           
            x = arr[i].x;                      
            y = arr[i].y;
            arr[i].x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x; //матрица поворота
            arr[i].y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
        }

    }
	
	void scale(double multiplier) override {         
        double x, y;
        for(int i = 0; i < 10; i++) {
            x = arr[i].x; 
            y = arr[i].y;
            arr[i].x = center.x + (x - center.x) * multiplier;
            arr[i].y = center.y + (y - center.y) * multiplier;
        }
	}

    ~Fivepointed_star() {
	delete[] arr;
        id--;
	}
};

int main() {
    Shape* test1 = new Square ({0,6}, {3,3}, {0, 1, 0} );
    cout << test1;
    test1->rotate(90);
    cout << test1;
    Shape* test2 = new Pentagon ({0,0}, {0,8}, {0, 1, 0});
    cout << test2;
    test2->scale(3);
    cout << test2;
    Pentagon* test3 = new Fivepointed_star ({1,4}, 8, {0, 1, 0});
    cout << test3;
    test3->move({5, 10});
    cout << test3;
    return 0;
}
