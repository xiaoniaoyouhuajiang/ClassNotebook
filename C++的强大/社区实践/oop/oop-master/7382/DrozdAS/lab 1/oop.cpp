#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>
using namespace std;

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
	cout << "def" << endl;
  }

      ~Array()
  { 
	cout << "del" << endl;
          delete[] m_array;
  }
    
    Array(const Array& object): Array(object.m_size) //конструктор копирования 
    { 
	cout << "obg" << endl;
    try 
        { 
        std::copy(object.m_array, object.m_array + m_size, m_array); 
        } 
    catch(...) 
        { 
        delete[] m_array; 
        throw; 
        } 
    } 
    
    Array(Array&& object)  //конструктор перемещения 
    {
	cout << "obg2" << endl;
    m_size = object.m_size; 
    m_array = object.m_array; 
    object.m_size = 0; 
    object.m_array = nullptr; 
    } 

    Array& operator=(const Array& other)
   {
	cout << "oper" << endl;
   if (this != &other)
      {
      size_t a=other.m_size;
      T* b=nullptr;
      if(a)
          b=new T[a]();
      try
         {
         std::copy(other.m_array, other.m_array + a, b);  
         }
      catch(...)
         {
          if(b!=nullptr)
         delete[] b;
          throw; 
         }          
      m_size=a;
      m_array=b;
      }
      return *this;
   }
    
   Array& operator=(Array&& other)
{
	cout << "oper2" << endl;
   if (this != &other)
   {
      delete[] m_array;
      m_array = other.m_array;
      m_size = other.m_size;
      other.m_array = nullptr;
      other.m_size = 0;
   }
   return *this;
}

   const size_t size() const
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
