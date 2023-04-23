#include <iostream>
#include "vector.hpp"

using namespace std;

void nicefill(stepik::vector<int>* a){
    for (int i=0; i<a->size(); i++){
        a->operator [](i) = i;
    }
}

int main()
{
    //Инициализация с числом
    cout << "===|Init with number test|===" << endl;
    stepik::vector<int> a(10);
    a.fill(10);
    a.out();
    cout << "---------------" << endl;
    //Инициализация с содержимым диапазона [first, last)
    cout << "===|Init with [first, last) test|===" << endl;
    stepik::vector<int> b(a.begin(), a.end());
    a[5] = 2;
    a.out();
    b.out();
    cout << "---------------" << endl;
    //Инициализация с помощью списка инициализации
    cout << "===|Init with list test|===" << endl;
    stepik::vector<int> c{ 1, 2, 3, 4, 5 };
    c.out();
    cout << "---------------" << endl;
    //Копирование
    cout << "===|Copy test|===" << endl;
    stepik::vector<int> d(c);
    c[3] = 0;
    c.out();
    d.out();
    cout << "---------------" << endl;
    //Перемещение
    cout << "===|Move test|===" << endl;
    stepik::vector<int> e(std::move(d));
    d.out();
    e.out();
    cout << "---------------" << endl;
    cout << "===|Destroying test|===" << endl;
    //Разрушение
    e.~vector();
    e.out();
    cout << "---------------" << endl;
    //Присваивание
    cout << "===|Assign test|===" << endl;
    stepik::vector<int> f = a;
    a.out();
    f.out();
    cout << "---------------" << endl;
    //Присваивание с перемещением
    cout << "===|Move assign test|===" << endl;
    stepik::vector<int> g = std::move(f);
    f.out();
    g.out();
    cout << "---------------" << endl;
    //Назначение
    cout << "===|Assign method test|===" << endl;
    stepik::vector<int> h(d);
    h.assign(c.begin(), c.end());
    h.out();
    cout << "---------------" << endl;
    //Resize
    cout << "===|Resize test|===" << endl;
    g.out();
    g.resize(5);
    g.out();
    g.resize(10);
    g.out();
    cout << "---------------" << endl;
    cout << "===|Erase test|===" << endl;
    stepik::vector<int> i(10);
    nicefill(&i);
    i.out();
    i.erase(&i[7]);
    i.out();
    cout << "---------------" << endl;
    cout << "===|Erase a lot test|===" << endl;
    i.erase(&i[2], &i[5]);
    i.out();
    cout << "--------------" << endl;
    cout << "===|Insert one test|===" << endl;
    stepik::vector<int> j;
    j.out();
    j.insert(j.begin(), 10);
    j.insert(&j[1], 15);
    j.insert(j.end(), 20);
    j.out();
    cout << "--------------" << endl;
    cout << "===|Insert many test|===" << endl;
    j.insert(&j[3], i.begin(), i.end());
    j.out();
    stepik::vector<int> k;
    k.insert(k.begin(), j.begin(), j.end());
    k.out();
    cout << "--------------" << endl;
    cout << "===|Push back test|===" << endl;
    j.push_back(8);
    j.push_back(800);
    j.out();
    cout << "===|End|===" << endl;
    return 0;
}
