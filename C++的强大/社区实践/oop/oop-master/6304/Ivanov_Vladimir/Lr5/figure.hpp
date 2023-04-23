#ifndef figure_hpp
#define figure_hpp

#include <iostream>
#include <cmath>

namespace last
{
    struct Point{
        double x;
        double y;
        Point(double x, double y): x(x),y(y){}
    };
    struct Colour{
        short r;
        short g;
        short b;
        Colour (short r, short g, short b):r(r),g(g),b(b){}
    };

    class Shape{
    public:
        Shape(double x, double y):ang(0), cent(x,y), col(0,0,0),square(0){}

        void changePos(double x, double y){
            for(auto& it: pts){
                it.x+=x - cent.x;
                it.y+=y - cent.y;
            }
            cent.x=x;
            cent.y=y;
        }

        void forSize(double& k){
            if(k<0){
                k=fabs(k);
            }
            cent.x*=k;
            cent.y*=k;
            for(auto& it: pts){
                it.x*=k;
                it.y*=k;
            }
        }

        virtual void changeSize(double k)=0;

        void changeAngle(int deg){
            ang+=deg;
            ang%=360;
            double rad=ang*M_PI/180;
            for(auto& it: pts){
                double tmpx=it.x*cos(rad)-it.y*sin(rad);
                double tmpy=it.y*cos(rad)+it.x*sin(rad);
                it.x=tmpx;
                it.y=tmpy;
            }
        }

        void changeColour(short r, short g, short b){
            col={r,g,b};
        }

        void forPrint(std::ostream& out){
            out<<"Центр. коорд. "<<cent.x<<" "<<cent.y<<std::endl;
            out<<"Угол поворота "<<ang<<std::endl;
            out<<"Точки "<<std::endl;
            int count=0;
            for(const auto& it: pts){
                count++;
                out<<count<<") ("<<it.x<<", "<<it.y<<")\n";
            }
            out<<"Цвет "<<col.r<<" "<<col.g<<" "<<col.b<<std::endl;
            out<<"Площадь "<< square<<"\n";
        }

        virtual void print(std::ostream& out)=0;

        friend std::ostream& operator<<(std::ostream& out, Shape& sh){
            sh.forPrint(out);
            sh.print(out);
            return out;
        }
        virtual void squareFind()=0;
        double getSquare(){
            return square;
        }
        virtual ~Shape()=default;

    protected:
        Point cent;
        int ang;
        Colour col;
        double square;
        std:: vector<Point> pts;

    };

    class Pentagon : public Shape{
    public:
        Pentagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5):
        Shape((x1+x2+x3+x4+x5)/5,(y1+y2+y3+y4+y5)/5), perimeter(0)
        {
            pts.push_back({x1,y1});
            pts.push_back({x2,y2});
            pts.push_back({x3,y3});
            pts.push_back({x4,y4});
            pts.push_back({x5,y5});
            for(int i=0; i<5;i++){
                perimeter+=sqrt(pow((pts[(i+1)%5].x - pts[i].x), 2) + pow((pts[(i+1)%5].y - pts[i].y), 2));
            }
            squareFind();
        }

        void changeSize(double k){
            forSize(k);
            perimeter*=k;
            squareFind();
        }
        void squareFind(){
            square=0;
            for(int i=0;i<5;i++){
                double firstlen=sqrt(pow((pts[(i+1)%5].x - pts[i].x), 2) + pow((pts[(i+1)%5].y - pts[i].y), 2));
                double seclen=sqrt(pow((pts[(i)%5].x - cent.x), 2) + pow((pts[(i)%5].y - cent.y), 2));
                double thirdlen=sqrt(pow((pts[(i+1)%5].x - cent.x), 2) + pow((pts[(i+1)%5].y - cent.y), 2));
                double tmphalfper=(firstlen+seclen+thirdlen)/2;
                square+=sqrt(tmphalfper*(tmphalfper-firstlen)*(tmphalfper-seclen)*(tmphalfper-thirdlen));
            }
        }
        void print(std::ostream& out){
            out<<"Периметр "<< perimeter<<"\n";
        }

    protected:
        double perimeter;
    };

    class Rectangle : public Shape{
    public:
        Rectangle(double x, double y, double a, double b) : Shape(x,y), a(a), b(b){
            pts.push_back({cent.x+a/2,cent.y+b/2});
            pts.push_back({cent.x+a/2,cent.y-b/2});
            pts.push_back({cent.x-a/2,cent.y-b/2});
            pts.push_back({cent.x-a/2,cent.y+b/2});
            squareFind();
        }

        void changeSize(double k){
            forSize(k);
            a*=k;
            b*=k;
            squareFind();
        }

        void print(std::ostream& out){
            out<<"Первая сторона "<< a<<"\n";
            out<<"Вторая сторона "<< b<<"\n";
        }
        void squareFind(){
            square=a*b;
        }

    protected:
        double a;
        double b;
    };
    class Ellipse : public Shape{
    public:
        Ellipse(double x, double y, double R, double r) : Shape(x,y), R(R), r(r){
            pts.push_back({x+R,y});
            pts.push_back({x,y-r});
            pts.push_back({x-R,y});
            pts.push_back({x,y+r});
            focdist = std::max(R,r)*sqrt(1-(std::min(R,r)*std::min(R,r))/(std::max(R,r)*std::max(R,r)));
            squareFind();
        }

        void changeSize(double k){
            forSize(k);
            r*=k;
            R*=k;
            focdist*=k;
            squareFind();
        }

        void print(std::ostream& out){
            out<<"Большой радиус "<< R<<"\n";
            out<<"Малый радиус "<<r<<"\n";
            out<<"Фокусное расстояние "<< focdist<<"\n";
        }
        void squareFind(){
            square=M_PI*R*r;
        }
     protected:
        double R, r;
        double focdist;
    };
}
#endif //figure_hpp