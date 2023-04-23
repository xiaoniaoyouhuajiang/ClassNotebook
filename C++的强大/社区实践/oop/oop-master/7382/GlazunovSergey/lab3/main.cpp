#include <iostream>
#include "myvector.h"
#include "mylist.h"
int main()
{
    std::cout << "VECTOR" << std::endl;
    stepik::vector<int> m_vec(3);
    m_vec[0] = 11;
    m_vec[1] = 13;
    m_vec[2] = 15;
    std::cout << "вектор: " << m_vec[0] << ", " << m_vec[1] << ", " << m_vec[2] << std::endl;

    std::cout << "Копирование:" << std::endl;
    stepik::vector<int> oldvector(m_vec.begin(), m_vec.end());
    std::cout << "Скопированный массив: " << oldvector[0] << ", " << oldvector[1] << ", " << oldvector[2] << std::endl;

    stepik::vector<int> newvector({9,3,4,6,7,4,1});
    newvector.print();
    std::cout << "удаление с 0 по 2: " << *newvector.insert(newvector.begin(), m_vec.begin()+0, m_vec.begin()+2) << std::endl;
    newvector.print();
    std::cout << "END_VECTOR" << std::endl;

    std::cout << "LIST" << std::endl;
    stepik::list<int> mylist;
    mylist.push_back(4);
    mylist.push_back(1);
    mylist.push_back(6);
    mylist.push_front(7);
    mylist.push_front(3);
    mylist.push_front(4);
    mylist.print();
    stepik::list_iterator<int> it = mylist.begin(); it++; it++;
    mylist.erase(it);
    mylist.print();
    std::cout << "END_LIST" << std::endl;

    return 0;
}
