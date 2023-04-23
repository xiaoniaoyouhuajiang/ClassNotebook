//
// Created by katier on 12.03.18.
//

#include "Square.h"
Square::Square(Colour colour,Point p1,Point p2,Point p3,Point p4):Rectangle(colour,p1,p2,p3,p4){
if(!isSquare())throw "NOT SQUARE!!!";
}

Square:: Square(Colour colour):Square(colour,Point(0.5,0.5),Point(0.5,-0.5),Point(-0.5,-0.5),Point(-0.5,0.5)){}

bool Square:: isSquare(){
    double s1 = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    double s2 = (p1.x - p3.x)*(p1.x - p3.x) + (p1.y - p3.y)*(p1.y - p3.y);
    double s3 = (p1.x - p4.x)*(p1.x - p4.x) + (p1.y - p4.y)*(p1.y - p4.y);
    double s4 = (p2.x - p3.x)*(p2.x - p3.x) + (p2.y - p3.y)*(p2.y - p3.y);
    double s5 = (p2.x - p4.x)*(p2.x - p4.x) + (p2.y - p4.y)*(p2.y - p4.y);
    double s6 = (p3.x - p4.x)*(p3.x - p4.x) + (p3.y - p4.y)*(p3.y - p4.y);
    if ((s1 == s6) && (s3 == s4) && (s1==s3) && (s2 == s5) && (s2 == 2*s1)) return  true;
    if ((s1 == s6) && (s2 == s5) && (s1 == s2) && (s3 == s4) && (s3 == 2*s1)) return  true;
    return (s2 == s5) && (s3 == s4) && (s2==s3) && (s1 == s6) && (s1 == 2*s2);
}
void Square:: print (std::ostream& os)  {
    os<<"\nSquare\nid = "<<getId()<<"\nPoints:\np1 = "<<p1<<"p2 = "<<p2
      <<"p3 = "<<p3<<"p4= "<<p4<<"Colour:\nblue = "<<getColour().blue
      <<"\ngreen = "<<getColour().green<<"\nred = "<<getColour().red<<std::endl;
}

