#include <iostream>
#include <shape.hpp>
#include <vector.hpp>
#include <shared_ptr.hpp>
#include <fstream>

using namespace std;
typedef stepik::shared_ptr<shape> vectorType;
using stepik::shared_ptr;

class Alg
{
    stepik::vector<vectorType> kontainer;
    size_t ammount;

public:

    Alg (size_t count): ammount(count)
    {}

    void fill()
    {
        for (size_t i=1; i<=ammount; i++)
        {
            switch (i % 3)
            {
            case 0:
            {
                eclipse* b = new eclipse(0, 0, 4, 10);
                b->setColor(0x0ffff0);
                kontainer.push_back(shared_ptr<shape>(b));
                break;
            }
            case 1:
            {
                NOtrap* c = new NOtrap(0, 0, 4, 10, 6);
                c->setColor(0x0f00f0);
                kontainer.push_back(shared_ptr<shape>(c));
                break;
            }
            case 2:
            {
                trap* d = new trap(0, 0, 4, 10, 6, 3);
                d->setColor(0x0ffff0);
                kontainer.push_back(shared_ptr<shape>(d));
                break;
            }
            }
        }
    }

    void nonChangingAlgorithm()
    {
        ofstream fout("output1.txt", ios_base::trunc);
        size_t i = 0;
        unsigned int temp = 0;
        for (auto current: kontainer)
        {
            if (current->getColor() == temp)
                fout << "Elements " << i << " and " << i+1 << " are ok" << endl;
            temp = current->getColor();
            i++;
        }
        fout.close();
    }

    void ChangingAlgorithm()
    {
        ofstream fout("output2.txt", ios_base::trunc);
        int k = 0;
        for(size_t i=0; i<ammount; i++)
        {
            if (i >= kontainer.size() - 1)
                break;
            unsigned int temp = (kontainer.operator [](i))->getColor();

            if(temp < 0x0ffff0)
            {
                kontainer.erase(&(kontainer.operator [](i)));
                fout << "Element deleted - " << i + k << endl;
                k++;
            }
        }
        fout.close();
    }

};
