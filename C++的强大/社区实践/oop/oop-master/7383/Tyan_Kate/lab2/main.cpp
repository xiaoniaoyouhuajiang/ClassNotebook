#include <iostream>
#include <cmath>

using namespace std;

enum Clr { RED, GREEN, BLUE,WHITE };

class Shape{
public:
    Shape(double x0, double y0, Clr color):x0(x0),y0(y0),clr(color){
        id=++next_id;
    }
    Shape():x0(0),y0(0),clr(WHITE),angle(0){
        id+=id;
    }
    void move(double x0, double y0){
        this->x0=x0;
        this->y0=y0;
    }
    virtual void rotate(double angle){}
    virtual void scale(double k){}
    virtual ostream& write(ostream&ostream)const=0;
    void set_clr(Clr color){
        clr=color;
    }
    void get_clr(Shape& shape){
        switch(shape.clr){
            case (RED):
                cout<<"Color is red"<<endl<<endl;
                break;
            case (GREEN):
                cout<<"Color is green"<<endl<<endl;
                break;
            case (BLUE):
                cout<<"Color is blue"<<endl<<endl;
                break;
            case (WHITE):
                cout<<"Color is white"<<endl<<endl;
                break;
        }
    }
protected:
    double x0;
    double y0;
    Clr clr;
    double angle;
    int id;
    static int next_id;
};

int Shape::next_id=0;

ostream& operator << (ostream& ostream,Shape const& shape){
    return shape.write(ostream);
}

class Square: public Shape{
public:
    Square(double x0, double y0, Clr color,double angle,double a):Shape(x0,y0,color){
        this->x1=(this->x0)+a;
        this->y1=(this->y0)+a;
        Square::rotate(angle);
    }
    Square():Shape(),x1(1),y1(1){}
    void move_sqr(double x, double y){
        double dif_x,dif_y;
        dif_x=fabs((this->x0)-(this->x1));
        dif_y=fabs((this->y0)-(this->y1));
        move(x,y);
        this->x1=(this->x0)+dif_x;
        this->y1=(this->y0)+dif_y;
    }
    void rotate(double angle)override{
        double new_x1,new_y1;
        (this->angle)+=angle;
        if(this->angle >= 360.0){
            int z;
            z=(this->angle)/360;
            (this->angle)=(this->angle)-z*360;
        }
        if(angle>360.0){
            int z=angle/360.0;
            angle=angle-z*360.0;
        }
        double sina=sin(angle * (M_PI/180));
        double cosa=cos(angle * (M_PI/180));
        new_x1=( ( (this->x1)-(this->x0))*cosa-((this->y1)-(this->y0))*sina)+(this->x0);
        new_y1=(((this->x1)-(this->x0))*sina+((this->y1)-(this->y0))*cosa)+(this->y0);
        this->x1=new_x1;
        this->y1=new_y1;
    }
    void scale(double k)override{
        double dif_x,dif_y;
        dif_x=k*(fabs((this->x1)-(this->x0)));
        dif_y=k*(fabs((this->y1)-(this->y0)));
        (this->x1)+=dif_x;
        (this->y1)+=dif_y;
    }
    ostream& write(ostream& ostream)const{
        return ostream<<"It is square."<<endl<<"ID: "<<this->id<<endl<<"Angle: "<<this->angle<<endl
                                            <<"Centre coordinates: "<<endl<<"x0 = "<<this->x0<<endl<<"y0 = "<<this->y0<<endl
                                                            <<"Vertex coordinates: "<<endl<<"x1 = "<<this->x1<<endl<<"y1 = "<<this->y1<<endl;
    }
private:
    double x1;
    double y1;
};

class Ellipse: public Shape{
public:
    Ellipse(double x0, double y0, Clr color,double angle,double a,double b):Shape(x0,y0,color){
        if(x1==x2 && y1==y2){
            throw "Wrong data.\n";
        }else{
            this->x1=(this->x0)+a;
            this->y1=(this->y0);
            this->x2=(this->x0);
            this->y2=(this->y0)+b;
            Ellipse::rotate(angle);
        }
    }
    Ellipse():Shape(),x1(1),y1(0),x2(0),y2(1){}
    void move_ellipse(double x,double y){
        double dif_x1,dif_y1,dif_x2,dif_y2;
        dif_x1=(this->x1)-(this->x0);
        dif_y1=(this->y1)-(this->y0);
        dif_x2=(this->x2)-(this->x0);
        dif_y2=(this->y2)-(this->y0);
        move(x,y);
        (this->x1)=dif_x1+(this->x0);
        (this->y1)=dif_y1+(this->y0);
        (this->x2)=dif_x2+(this->x0);
        (this->y2)=dif_y2+(this->y2);
    }
    void rotate(double angle)override{
        double new_x1,new_y1,new_x2,new_y2;
        (this->angle)+=angle;
        if((this->angle)>=360.0){
            int z=(this->angle)/360.0;
            (this->angle)=(this->angle)-z*360.0;
        }
        if(angle>360.0){
            int z=angle/360.0;
            angle=angle-z*360.0;
        }
        double sina=sin(angle * (M_PI/180));
        double cosa=cos(angle * (M_PI/180));
        new_x1=( ( (this->x1)-(this->x0))*cosa-((this->y1)-(this->y0))*sina)+(this->x0);
        new_y1=(((this->x1)-(this->x0))*sina+((this->y1)-(this->y0))*cosa)+(this->y0);
        new_x2=( ( (this->x2)-(this->x0))*cosa-((this->y2)-(this->y0))*sina)+(this->x0);
        new_y2=(((this->x2)-(this->x0))*sina+((this->y2)-(this->y0))*cosa)+(this->y0);
        this->x1=new_x1;
        this->y1=new_y1;
        this->x2=new_x2;
        this->y2=new_y2;
    }
    void scale(double k)override{
        double dif_x1,dif_y1,dif_x2,dif_y2;
        dif_x1=k*(fabs((this->x1)-(this->x0)));
        dif_y1=k*(fabs((this->y1)-(this->y0)));
        dif_x2=k*(fabs((this->x2)-(this->x0)));
        dif_y2=k*(fabs((this->y2)-(this->y0)));
        (this->x1)+=dif_x1;
        (this->y1)+=dif_y1;
        (this->x2)+=dif_x2;
        (this->y2)+=dif_y2;
    }
    ostream& write(ostream& ostream)const{
        return ostream<<"It is ellipse."<<endl<<"ID: "<<this->id<<endl<<"Angle: "<<this->angle<<endl
                                                <<"Centre coordinates: "<<endl<<"x0 = "<<this->x0<<endl<<"y0 = "<<this->y0<<endl
                                                            <<"Vertexes' coordinates: "<<endl<<"x1 = "<<this->x1<<endl<<"y1 = "<<this->y1<<endl<<"x2 = "<<this->x2<<endl<<"y2 = "<<this->y2<<endl;
    }
protected:
    double x1;
    double y1;
    double x2;
    double y2;
};

class Rhombus: public Ellipse{
public:
    Rhombus(double x0, double y0, Clr color,double angle,double a,double b):Ellipse(x0,y0,color,angle,a,b){}
    Rhombus():Ellipse(){}
    ostream& write(ostream& ostream)const{
        return ostream<<"It is rhombus."<<endl<<"ID: "<<this->id<<endl<<"Angle: "<<this->angle<<endl
                                            <<"Centre coordinates: "<<endl<<"x0 = "<<this->x0<<endl<<"y0 = "<<this->y0<<endl
                                                        <<"Vertexes' coordinates: "<<endl<<"x1 = "<<this->x1<<endl<<"y1 = "<<this->y1<<endl<<"x2 = "<<this->x2<<endl<<"y2 = "<<this->y2<<endl;
    }
};

int main(){
    Square sqr(3.5,2.5,RED,45,3.5);
    cout<<sqr;
    sqr.get_clr(sqr);
    sqr.set_clr(BLUE);
    sqr.move_sqr(-5,7);
    cout<<sqr;
    sqr.get_clr(sqr);
    sqr.scale(1);
    cout<<sqr;
    sqr.get_clr(sqr);
    sqr.rotate(270.0);
    cout<<sqr;
    sqr.get_clr(sqr);
    
    Ellipse ellps(2.5,-1,RED,30,6.5,8);
    cout<<ellps;
    ellps.get_clr(ellps);
    ellps.set_clr(RED);
    ellps.move_ellipse(-5,7);
    cout<<ellps;
    ellps.get_clr(ellps);
    ellps.scale(3.2);
    cout<<ellps;
    ellps.get_clr(ellps);
    ellps.rotate(90.0);
    cout<<ellps;
    ellps.get_clr(ellps);
    
    Rhombus rmb(4,7.5,RED,135,6,4.5);
    cout<<rmb;
    rmb.get_clr(rmb);
    rmb.set_clr(GREEN);
    rmb.move_ellipse(-5,7);
    cout<<rmb;
    rmb.get_clr(rmb);
    rmb.scale(0.5);
    cout<<rmb;
    rmb.get_clr(rmb);
    rmb.rotate(45.0);
    cout<<rmb;
    rmb.get_clr(rmb);
    return 0;
}
