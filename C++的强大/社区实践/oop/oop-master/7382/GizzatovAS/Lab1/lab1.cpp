#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>
#define OUTPUT

template <typename T>
class Array
{
public:
// (default) constructor
Array(const size_t size = 0)
: m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
{
//std::cout « "дефолтный конструктор" « std::endl;
}
//деструктор
~Array()
{
delete[] m_array;
}
//оператор присваивания
Array &operator=(const Array &another){
if (this == &another)
return *this;
Array tmp = another;
delete[] m_array;
m_size = tmp.size();
if (m_size){
    m_array = new T[m_size];
    for (size_t i = 0; i < m_size; i++){
        m_array[i] = tmp.m_array[i];
    }
}
else{
    m_array = nullptr;
    }
return *this;
}

//конструктор копирования
Array(const Array &another){
Array tmp(another.size());
std::cout << "copy constuctor"<< std::endl;
for (size_t i = 0; i < tmp.size(); i++){
    tmp.m_array[i] = another.m_array[i];
    }
m_size = tmp.m_size;
if (m_size){
    m_array = new T[m_size];
    for (size_t i = 0; i < m_size; i++){
        m_array[i] = tmp.m_array[i];
    }
}
else{
    m_array = nullptr;
    }
}
//конструктор перемещения ?????????????????????????????????????
Array( Array &&another){
    m_size = another.size();
    std::cout << "move consuctor" << std::endl;
    if (m_size){
        m_array = new T[m_size];
        m_array = another.m_array;
        another.m_array = nullptr;
        another.m_size = 0;
    }
    else{
        m_array = nullptr;
    }
}
const size_t size() const{
return m_size;
}
T &operator[](const size_t index)
{
assert(index < m_size);
return m_array[index];
}
private:
size_t m_size;
T *m_array;
};

int main(){
    Array<int> a(5);
    Array<int> b(std::move(a));
    Array<int> c;
    c = b;
return 0; 
}
