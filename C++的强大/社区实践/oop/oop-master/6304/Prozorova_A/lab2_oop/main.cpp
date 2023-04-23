/* Прозорова А.Д. 6304. Лабораторная работа №2, ООП.
 * Вариант 6. Треугольник, ромб, параллелограмм.
 */

#include "./shapes.h"
int main()
{
       //Тест треугольник
       std::cout << "triangle" << std::endl ;
       Triangle tr(3, 2, 4, 4, 5, 3);
       std::cout << "n/zoom" << std::endl ;
       tr.zoom(5);
       cout << tr;
       std::cout << "n/rotate" << std::endl ;
       tr.rotation(90);
       cout << tr;

       //Параллелограмм (квадрат)
        std::cout << "--------------------------" << std::endl ;
       std::cout << "parallelogram" << std::endl ;
       Parallelogram pr(1, 4, 1, 1, 4, 1);
       std::cout << "n/zoom" << std::endl ;
       pr.zoom(2);
       cout << pr;
       std::cout << "n/rotate" << std::endl ;
       pr.rotation(90);
       cout << pr; //координаты не должны измениться

       //Ромб (квадрат)
       std::cout << "n/--------------------------" << std::endl ;
       std::cout << "rhombus" << std::endl ;
       std::cout << "n/zoom" << std::endl ;
       Rhombus rm(1, 4, 1, 1, 90);
       rm.zoom(2);
       cout << rm;
       std::cout << "n/rotate" << std::endl ;
       rm.rotation(90);
       cout << rm; //координаты не должны измениться

       //Параллелограмм (произвольный)
       std::cout << "--------------------------" << std::endl ;
       std::cout << "parallelogram" << std::endl ;
       Parallelogram pr2(1, 6, 3, 2, 4, 1);
       std::cout << "n/zoom" << std::endl ;
       pr2.zoom(2);
       cout << pr2;
       std::cout << "n/rotate" << std::endl ;
       pr2.rotation(45);
       cout << pr2;

       //Ромб (прямая)
       std::cout << "n/--------------------------" << std::endl ;
       std::cout << "rhombus" << std::endl ;
       std::cout << "n/zoom" << std::endl ;
       Rhombus rm2(4, 1, 3, 2, 180);
       rm2.zoom(2);
       cout << rm2;
       std::cout << "n/rotate" << std::endl ;
       rm2.rotation(45);
       cout << rm2;

       //Ромб (произвольный)
       std::cout << "n/--------------------------" << std::endl ;
       std::cout << "rhombus" << std::endl ;
       std::cout << "n/zoom" << std::endl ;
       Rhombus rm3(4, 1, 3, 2, 45);
       rm3.zoom(2);
       cout << rm3;
       std::cout << "n/rotate" << std::endl ;
       rm3.rotation(45);
       cout << rm3; //координаты должны отзеркалиться относительно вертикальной прямой, проходящей через центр


       return 0;
}
