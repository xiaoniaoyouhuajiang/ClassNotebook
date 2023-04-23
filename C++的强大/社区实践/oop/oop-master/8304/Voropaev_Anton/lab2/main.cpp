#include <iostream>
#include "Unit.h"
#include "Field.h"
#include "FieldIterator.h"
#include <ctime>


int main()
{
    srand(time(nullptr));

    LandscapeTypes t;

    bool stop_flag = false;

    while (true) {

        if(stop_flag)
            break;

        std::cout << "Choose game field size (2 positive integer numbers)" << std::endl;

        int w(0), h(0);

        std::cin >> w >> h;

        Field f(w, h);

        int maxQuantity = 0;

        std::cout << "Input max quantity of units on the field\n";

        std::cin >> maxQuantity;
        while(true) {
            if(maxQuantity <= w * h && maxQuantity >= 0) {
                break;
            }
            std::cout << "Inserted quantity is larger than field size\nInput new quantity\n";
            std::cin >> maxQuantity;
        }

        f.setLimit(maxQuantity);



        f.print();

        while (true) {

            if(stop_flag)
                break;

            std::cout << "Choose action" << std::endl;
            std::cout << "'+' - add Unit, '-' - remove Unit, 'a' - attack, 'm' - move, 's' - stop" << std::endl;

            char action(0);
            std::cin >> action;
            int x(0), y(0);
            char unit(0);


            auto tier1_factory = new Tier1Factory();
            auto tier2_factory = new Tier2Factory();
            auto tier3_factory = new Tier3Factory();
            Object *newUnit;




            int Ax(0), Ay(0);
            int Tx(0), Ty(0);
            int dx(0), dy(0);


            switch (action) {
                case '+':
                    std::cout << "Enter position (2 positive integer numbers)" << std::endl;

                    std::cin >> x >> y;

                    if(x < 1 || x > f.getSize().width || y > f.getSize().height || y < 1) {
                        std::cout << "Invalid unit coordinates\n";
                        break;
                    }

                    std::cout << "Choose Unit type:" << std::endl;

                    std::cout << "'n' - novice archer" << std::endl
                              << "'m' - master archer" << std::endl
                              << "'s' - shieldman" << std::endl
                              << "'w' - swordsman" << std::endl
                              << "'c' - cavalier" << std::endl
                              << "'p' - paladin" << std::endl;

                    std::cin >> unit;





                    switch (unit) {
                        case 'n':
                            newUnit = tier2_factory->createType1();
                            break;

                        case 'm':
                            newUnit = tier2_factory->createType2();
                            break;

                        case 'w':
                            newUnit = tier1_factory->createType1();
                            break;

                        case 's':
                            newUnit = tier1_factory->createType2();
                            break;

                        case 'p':
                            newUnit = tier3_factory->createType1();
                            break;

                        case 'c':
                            newUnit = tier3_factory->createType2();
                            break;

                        default:
                            newUnit = new NoviceArcher;
                            break;
                    }

                    if(f.addObj(newUnit, x, y))
                        dynamic_cast<Unit*>(newUnit)->say_attributes();

                    break;

                case '-':
                    std::cout << "Enter coordinates (2 positive integer numbers)" << std::endl;

                    std::cin >> x >> y;

                    if(x < 1 || x > f.getSize().width || y > f.getSize().height || y < 1) {
                        std::cout << "Invalid unit coordinates\n";
                        break;
                    }

                    f.removeObj(Location(x , y ));
                    break;

                case 'a':
                    std::cout << "Enter attacker coordinates (2 positive integer numbers)" << std::endl;
                    std::cin >> Ax >> Ay;

                    std::cout << "Enter target coordinates (2 positive integer numbers)" << std::endl;
                    std::cin >> Tx >> Ty;

                    (*(Unit*)f.getHead()[Ay - 1][Ax - 1].unit)((Unit*)f.getHead()[Ty - 1][Tx - 1].unit);
                    if(((Unit*)f.getHead()[Ty - 1][Tx - 1].unit)->getHealth() <= 0) {
                        f.getBase()->unsubscribe((Unit*)f.getHead()[Ty - 1][Tx - 1].unit);
                        f.getHead()[Ty - 1][Tx - 1].unit = nullptr;
                        --(f.currentQuantity);
                    }
                    break;

                case 'm':
                    std::cout << "Enter Unit coordinates (2 positive integer numbers)" << std::endl;

                    std::cin >> x >> y;


                    if( x < 1 || x > f.getSize().width || y > f.getSize().height || y < 1 || !((f.getHead())[y - 1][x - 1].unit)) {
                        std::cout << "Invalid unit coordinates\n";
                        break;
                    }

                    std::cout << "Enter horizontal and vertical steps (2 integer numbers)" << std::endl;

                    std::cin >> dx >> dy;
                    if( x + dx < 1 || x + dx > f.getSize().width || y + dy > f.getSize().height || y + dy < 1 || !((f.getHead())[y - 1][x - 1].unit)) {
                        std::cout << "Invalid move coordinates\n";
                        break;
                    }



                    ((Unit*)(f.getHead())[y - 1][x - 1].unit)->move(&f, dx, dy);
                    dynamic_cast<Unit*>(f.getHead()[y - 1 + dy][x - 1 + dx].unit)->say_attributes();
                    break;

                case 's':
                    stop_flag = true;
                    break;

                default:
                    break;
            }

            f.print();
        }
    }

    return 0;
}


