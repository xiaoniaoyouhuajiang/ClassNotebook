#define Pi 3.14
#include<iostream>
#include<cmath>
#include"Shape.h"
#include<iomanip>
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
    <<rec.basis1.second.first<<","<<std::fixed<<std::setprecision(1)<<rec.basis1.second.second<<"("
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
int main()
{
    Rectangle rec(6,2,std::make_pair(0,0));
    Lsosceles_trapeze l_tr(5.0,8,4,std::make_pair(0,0));
    Trapeze tr(6,4,8,60,std::make_pair(0,0));
  
    rec.move_by_coordinates(2, 2);
    l_tr.move_by_coordinates(2, 2);
    tr.move_by_coordinates(2, 2);
    rec.turn_by_corner(90);
    l_tr.turn_by_corner(90);
    tr.turn_by_corner(90);
    rec.inscrease_by_cf(2);
    l_tr.inscrease_by_cf(2);
    tr.inscrease_by_cf(2);
    std::cout<<rec;
    std::cout<<l_tr;
    std::cout<<tr;
    
    return 0;
}
