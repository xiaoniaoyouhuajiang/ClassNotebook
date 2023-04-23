#include <QCoreApplication>
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
using namespace std;

//First task
class Base
{
public:
    Base()
    {
        cout << "Constructor Base" << endl;
    }
    ~Base()
    {
        cout << "Destructor Base" << endl;
    }
};

class P1
{
public:
    P1()
    {
        cout << "Constructor P1" << endl;
    }
    ~P1()
    {
        cout << "Destructor P1" << endl;
    }
};

class P2
{
public:
    P2()
    {
        cout << "Constructor P2" << endl;
    }
    ~P2()
    {
        cout << "Destructor P2" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Constructor Derived" << endl;
    }
    ~Derived()
    {
        cout << "Destructor Derived" << endl;
    }
  P1 m_property1;
  P2 m_property2;
};


//implementation class Array

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
  {}
  //copy constructor
  Array(Array const &arr)
  {
      Array buff(arr.m_size);
      for(size_t i = 0; i < buff.m_size; ++i)
          buff.m_array[i] = arr.m_array[i];
      m_size = buff.m_size;
      if(m_size == 0)
        m_array = nullptr;
      else
      {
        m_array = new T[m_size];
        for(size_t i = 0; i < m_size; ++i)
          m_array[i] = buff.m_array[i];
      }
  }
  //assignment constructor
  Array& operator=(Array const &arr)
  {
      if(this!= &arr)
      {
          Array buff = arr;
          delete[] m_array;
          m_size = buff.m_size;
          if(m_size == 0)
              m_array = nullptr;
          else
          {
              m_array = new T[m_size];
              for(size_t i = 0; i < m_size; ++i)
                  m_array[i] = buff.m_array[i];
          }
      }
      return *this;
  }
  //move constructor
  Array(Array&& arr)
  {
      Array buff = arr;
      delete[] m_array;
      m_size = buff.m_size;
      if(m_size == 0)
          m_array = nullptr;
      else
      {
          m_array = new T[m_size];
          for(size_t i = 0; i < m_size; ++i)
              m_array[i] = buff.m_array[i];
      }
      arr->~Array();
  }

  ~Array()
  {
      delete[] m_array;
  }

  size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }

private:
  size_t m_size;
  T* m_array;
};


int main()
{
    Array<Derived> a(500);
    Array<Derived> b = a;
    Array<Derived> c;
    c = b;
    return 0;
}
