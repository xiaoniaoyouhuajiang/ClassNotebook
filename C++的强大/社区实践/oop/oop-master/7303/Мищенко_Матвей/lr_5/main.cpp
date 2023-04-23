#define Pi 3.14
#include<iostream>
#include<cmath>
#include"shared_ptr.h"
#include"Shape.h"
#include"vector.h"
#include"list.h"
#include<iomanip>
#include<algorithm>
#define count 5;
using namespace stepik;
#define Turn(corn,x,y,cen_x,cen_y) std::make_pair(((x-cen_x)*cos((corn*Pi)/180)-(y-cen_y)*sin((corn*Pi)/180))+cen_x,((x-cen_x)*sin((corn*Pi)/180)+(y-cen_y)*cos((corn*Pi)/180))+cen_y)
#define Move(x,y,cen_x,cen_y,new_pos_x,new_pos_y) std::make_pair(x-cen_x+new_pos_x,y-cen_y+new_pos_y)
#define Inscrease(x,y,cen_x,cen_y,cf) std::make_pair((x-cen_x)*cf+cen_x,(y-cen_y)*cf+cen_y)

void Rectangle::move_by_coordinates(int x,int y)
{ basis1=std::make_pair(Move(basis1.first.first,basis1.first.second,centr.first,centr.second,x,y), Move(basis1.second.first,basis1.second.second,centr.first,centr.second,x,y));
    basis2=std::make_pair(Move(basis2.first.first,basis2.first.second,centr.first,centr.second,x,y), Move(basis2.second.first,basis2.second.second,centr.first,centr.second,x,y));
    centr=std::make_pair(x,y);
    
}
void Trapeze::move_by_coordinates(int x,int y)
{ basis1=std::make_pair(Move(basis1.first.first,basis1.first.second,centr.first,centr.second,x,y), Move(basis1.second.first,basis1.second.second,centr.first,centr.second,x,y));
    basis2=std::make_pair(Move(basis2.first.first,basis2.first.second,centr.first,centr.second,x,y), Move(basis2.second.first,basis2.second.second,centr.first,centr.second,x,y));
    centr=std::make_pair(x,y);
    
}
void Lsosceles_trapeze::move_by_coordinates(int x,int y)
{ basis1=std::make_pair(Move(basis1.first.first,basis1.first.second,centr.first,centr.second,x,y), Move(basis1.second.first,basis1.second.second,centr.first,centr.second,x,y));
    basis2=std::make_pair(Move(basis2.first.first,basis2.first.second,centr.first,centr.second,x,y), Move(basis2.second.first,basis2.second.second,centr.first,centr.second,x,y));
    centr=std::make_pair(x,y);
    
}
void Rectangle::turn_by_corner(int corner)
{
    basis1=std::make_pair(Turn(corner,basis1.first.first,basis1.first.second,centr.first,centr.second), Turn(corner,basis1.second.first,basis1.second.second,centr.first,centr.second));
    basis2=std::make_pair(Turn(corner,basis2.first.first,basis2.first.second,centr.first,centr.second), Turn(corner,basis2.second.first,basis2.second.second,centr.first,centr.second));
}
void Trapeze::turn_by_corner(int corner)
{
    basis1=std::make_pair(Turn(corner,basis1.first.first,basis1.first.second,centr.first,centr.second), Turn(corner,basis1.second.first,basis1.second.second,centr.first,centr.second));
    basis2=std::make_pair(Turn(corner,basis2.first.first,basis2.first.second,centr.first,centr.second), Turn(corner,basis2.second.first,basis2.second.second,centr.first,centr.second));
}
void Lsosceles_trapeze::turn_by_corner(int corner)
{
    basis1=std::make_pair(Turn(corner,basis1.first.first,basis1.first.second,centr.first,centr.second), Turn(corner,basis1.second.first,basis1.second.second,centr.first,centr.second));
    basis2=std::make_pair(Turn(corner,basis2.first.first,basis2.first.second,centr.first,centr.second), Turn(corner,basis2.second.first,basis2.second.second,centr.first,centr.second));
}
void Rectangle::inscrease_by_cf(int cf)
{ basis1=std::make_pair(Inscrease(basis1.first.first,basis1.first.second,centr.first,centr.second,cf), Inscrease(basis1.second.first,basis1.second.second,centr.first,centr.second,cf));
    basis2=std::make_pair(Inscrease(basis2.first.first,basis2.first.second,centr.first,centr.second,cf), Inscrease(basis2.second.first,basis2.second.second,centr.first,centr.second,cf));
}
void Trapeze::inscrease_by_cf(int cf)
{ basis1=std::make_pair(Inscrease(basis1.first.first,basis1.first.second,centr.first,centr.second,cf), Inscrease(basis1.second.first,basis1.second.second,centr.first,centr.second,cf));
    basis2=std::make_pair(Inscrease(basis2.first.first,basis2.first.second,centr.first,centr.second,cf), Inscrease(basis2.second.first,basis2.second.second,centr.first,centr.second,cf));
}
void Lsosceles_trapeze::inscrease_by_cf(int cf)
{ basis1=std::make_pair(Inscrease(basis1.first.first,basis1.first.second,centr.first,centr.second,cf), Inscrease(basis1.second.first,basis1.second.second,centr.first,centr.second,cf));
    basis2=std::make_pair(Inscrease(basis2.first.first,basis2.first.second,centr.first,centr.second,cf), Inscrease(basis2.second.first,basis2.second.second,centr.first,centr.second,cf));
}
std::ostream& operator <<(std::ostream &out,const Rectangle &rec)
{
    out<<"Centr("<<std::fixed<<std::setprecision(1)<<rec.centr.first<<","<<std::fixed<<std::setprecision(1)<<rec.centr.second<<")\n"<<"Id="
    <<rec.id<<"\n"<<"Color="<<rec.color[0]<<"."<<rec.color[1]<<"."<<rec.color[2]<<"\n"
<<"Coordinat(("<<std::fixed<<std::setprecision(1)<<rec.basis1.first.first<<","
    <<std::fixed<<std::setprecision(1)<<rec.basis1.first.second<<")("<<std::fixed<<std::setprecision(1)
    <<rec.basis1.second.first<<","<<std::fixed<<std::setprecision(1)<<rec.basis1.second.second<<")("
<<std::fixed<<std::setprecision(1)<<rec.basis2.first.first<<","<<std::fixed<<std::setprecision(1)<<rec.basis2.first.second<<")("<<std::fixed<<std::setprecision(1)
<<rec.basis2.second.first<<","<<std::fixed<<std::setprecision(1)<<rec.basis2.second.second<<"))\n";
    return out;
}
std::ostream& operator <<(std::ostream &out,const  Trapeze &tr)
{
    out<<"Centr("<<std::fixed<<std::setprecision(1)<<tr.centr.first<<","<<std::fixed<<std::setprecision(1)<<tr.centr.second<<")\n"<<"Id="
    <<tr.id<<"\n"<<"Color="<<tr.color[0]<<"."<<tr.color[1]<<"."<<tr.color[2]<<"\n"
<<"Coordinat(("<<std::fixed<<std::setprecision(1)<<tr.basis1.first.first<<","<<std::fixed<<std::setprecision(1)<<tr.basis1.first.second<<")("<<std::fixed<<std::setprecision(1)
    <<tr.basis1.second.first<<","<<std::fixed<<std::setprecision(1)<<tr.basis1.second.second<<")("<<std::fixed<<std::setprecision(1)<<tr.basis2.first.first<<","<<std::fixed<<std::setprecision(1)<<tr.basis2.first.second<<")("<<std::fixed<<std::setprecision(1)
    <<tr.basis2.second.first<<","<<std::fixed<<std::setprecision(1)<<tr.basis2.second.second<<"))\n";
    return out;
}
std::ostream& operator <<(std::ostream &out,const Lsosceles_trapeze &Lr_tr)
{
    out<<"Centr("<<std::fixed<<std::setprecision(1)<<Lr_tr.centr.first<<","<<std::fixed<<std::setprecision(1)<<Lr_tr.centr.second<<")\n"<<"Id="
    <<Lr_tr.id<<"\n"<<"Color="<<Lr_tr.color[0]<<"."<<Lr_tr.color[1]<<"."<<Lr_tr.color[2]<<"\n"
    <<"Coordinat(("<<std::fixed<<std::setprecision(1)<<Lr_tr.basis1.first.first<<","<<std::fixed<<std::setprecision(1)<<Lr_tr.basis1.first.second<<")("<<std::fixed<<std::setprecision(1)
    <<Lr_tr.basis1.second.first<<","<<std::fixed<<std::setprecision(1)<<Lr_tr.basis1.second.second<<")("<<std::fixed<<std::setprecision(1)<<Lr_tr.basis2.first.first<<","<<std::fixed<<std::setprecision(1)<<Lr_tr.basis2.first.second<<")("<<std::fixed<<std::setprecision(1)
    <<Lr_tr.basis2.second.first<<","<<std::fixed<<std::setprecision(1)<<Lr_tr.basis2.second.second<<"))\n";
    return out;
    
}
void foo(vector<Shape *>vec)
{
    for(auto  v:vec)
    {v->move_by_coordinates(5, 5);};
}
int main()
{   vector<Shape *> vec(6);
    auto sp =  stepik::make_shared<class Rectangle>(6,2,std::make_pair(0,0));
    Rectangle rec(6,2,std::make_pair(0,0));
    Rectangle rec2(8,5,std::make_pair(0,0));
    Lsosceles_trapeze l_tr(10.0,8,4,std::make_pair(0,0));
    Lsosceles_trapeze l_tr2(5.0,6,2,std::make_pair(0,0));
    Trapeze tr(10,6,10,90,std::make_pair(0,0));
    Trapeze tr2(6,4,8,60,std::make_pair(0,0));
    std::cout<<"\t\t\trec\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<rec;
    std::cout<<"\n\t\t\trec2\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<rec2;
    std::cout<<"\n\t\t\tl_tr\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<l_tr;
    std::cout<<"\n\t\t\tl_tr2\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<l_tr2;
    std::cout<<"\n\t\t\ttr\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<tr;
    std::cout<<"\n\t\t\ttr2\n";  
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<tr2;
    std::cout<<"---------------------------------------------------------------------------------";
    vec[0]=&rec;
    vec[1]=&rec2;
    vec[2]=&l_tr;
    vec[3]=&l_tr2;
    vec[4]=&tr;
    vec[5]=&tr2;
    
    foo(vec);
    std::cout<<"\t\t\trec\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<rec;
    std::cout<<"\n\t\t\trec2\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<rec2;
    std::cout<<"\n\t\t\tl_tr\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<l_tr;
    std::cout<<"\n\t\t\tl_tr2\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<l_tr2;
    std::cout<<"\n\t\t\ttr\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<tr;
    std::cout<<"\n\t\t\ttr2\n";
    std::cout<<"---------------------------------------------------------------------------------";
    std::cout<<tr2;
    std::cout<<"---------------------------------------------------------------------------------";
    return 0;
}
