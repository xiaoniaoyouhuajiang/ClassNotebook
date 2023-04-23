#include <iostream>

#include "parallelogramm.h"
#include "righttriangle.h"
#include "triangle.h"

/*%2F%2F Cool Class Diagram, [Shape|virtual void move;virtual void rotate;virtual void scale;Color color|int id; int count],[Shape|void scale()void rotare()void move()]<-, [Shape]<-[Triangle|void scale();void rotare();void move();friend std::ostream& operator|double coefficient; double a b c; Point p1 p2 p3 center], [Shape]<-[Parallelogramm|void scale(); void rotate(); void move(); friend std::ostream& operator|Point p1 p2 p3 p4 center; double coefficient; double a b c d], [Shape]<-[rightTriangle|]*/

int main()
{
    Point point1(2, 2);
    Point point2(5, 7);
    Point point3(6, 1);
    Point center((point1.x+point2.x+point3.x)/3, (point1.y+point2.y+point3.y)/3);
    Triangle t_1(center, point1, point2, point3);
    std::cout << "Triangle parameters after the announcement:" << std::endl << t_1 << std::endl;
    t_1.move(point2);
    t_1.setColor(Color(255, 255, 255));
    std::cout << "Triangle parameters after moving the center and change color:" << std::endl  << t_1 << std::endl;
    t_1.rotate(90);
    std::cout << "Triangle parameters after rotate:" << std::endl  << t_1 << std::endl;
    t_1.scale(1.5);
    t_1.setColor(Color(0, 0, 0));
    std::cout << "Triangle parameters after scale and change color:" << std::endl  << t_1 << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    Point center1(4, 4);
    Point p1(1, 2), p2(5, 2), p3(7, 6), p4(3, 6);
    Parallelogramm p_1(center1, p1, p2, p3, p4);
    p_1.setColor(Color(122, 240, 99));
    std::cout << "The parameters of the parallelogramm after the announcement:" << std::endl << p_1 << std::endl;
    p_1.move(point2);
    std::cout << "The parameters of the parallelogramm after moving the center:" << std::endl  << p_1 << std::endl;
    p_1.rotate(90);
    std::cout << "The parameters of the parallelogramm after rotate:" << std::endl  << p_1 << std::endl;
    p_1.scale(1.5);
    p_1.setColor(Color(0, 0, 0));
    std::cout << "The parameters of the parallelogramm after scale and change color:" << std::endl  << p_1 << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    Point pointR1(1, 1);
    Point pointR2(4, 6.1);
    Point pointR3(7, 1);
    Point centerR((pointR1.x+pointR2.x+pointR3.x)/3, (pointR1.y+pointR2.y+pointR3.y)/3);
    rightTriangle RT_1(centerR, pointR1, pointR2, pointR3);
    std::cout << "Triangle parameters after the announcement:" << std::endl << RT_1 << std::endl;
    RT_1.move(pointR2);
    RT_1.setColor(Color(13, 45, 129));
    std::cout << "Triangle parameters after moving the center and change color:" << std::endl  << RT_1 << std::endl;
    RT_1.rotate(270);
    std::cout << "Triangle parameters after rotate:" << std::endl  << RT_1 << std::endl;
    RT_1.scale(2.0);
    RT_1.setColor(Color(12, 12, 12));
    std::cout << "Triangle parameters after scale and change color:" << std::endl  << RT_1 << std::endl;
    /*Point point1(2, 2);
    Point point2(5, 7);
    Point point3(6, 1);*/
    Point point1_1(5, 2);
    Point point2_1(3, 9);
    Point point3_1(6, 6);

    Point point1_2(2, 5);
    Point point2_2(9, 3);
    Point point3_2(6, 6);
    Point center2((point1_1.x+point2_1.x+point3_1.x)/3, (point1_1.y+point2_1.y+point3_1.y)/3);
    Triangle t_2(center2, point1_1, point2_1, point3_1);
    Point center3((point1_2.x+point2_2.x+point3_2.x)/3, (point1_2.y+point2_2.y+point3_2.y)/3);
    Triangle t_3(center3, point1_2, point2_2, point3_2);
    Triangle triangle = t_2 + t_3;

    std::cout << "Triangle parameters after operator:" << std::endl  << triangle << std::endl;
    /*std::cout << "New triangle: " << std::endl << "Point1: A(" << triangle.p1.x << ", " << triangle.p1.y << ") "
                                               << "Point2: B(" << triangle.p2.x << ", " << triangle.p2.y << ") "
                                               << "Point3: C(" << triangle.p3.x << ", " << triangle.p3.y << ") "
                                               << "Center: D(" << (triangle.p1.x + triangle.p2.x + triangle.p3.x)/3 <<
                                                          ", " << (triangle.p1.y + triangle.p2.y + triangle.p3.y)/3 << ")" << endl;*/
    system("pause");
    return 0;
}