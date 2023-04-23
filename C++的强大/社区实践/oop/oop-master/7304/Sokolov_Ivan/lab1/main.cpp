#include <assert.h>
#include <algorithm>
#include <cstddef>
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
        cout << "Вызван конструктор" << endl;
  }

  Array(Array const & arr)
    : m_size(arr.size())
    , m_array(m_size ? new T[m_size]() : nullptr)
    {
      try{
      std::copy(arr.m_array, arr.m_array+arr.size(), m_array);
      }
      catch(...){
          this->~Array();
          throw;
      }
        cout <<"Вызван конструктор копирования"<<endl;
    }

  Array &operator =(Array const & arr){
      if(this!=&arr){
        Array temp(arr);
        m_size=temp.size();
        m_array=m_size ? new T[m_size]() : nullptr;
        std::copy(temp.m_array, temp.m_array+temp.size(), m_array);
      }
      return *this;
  }

  Array(Array && arr)
    : m_array(arr.m_array)
    , m_size(arr.size())
  {
    arr.m_array=nullptr;
  }

  ~Array(){
    delete [] m_array;
  cout << "Вызван диструктор" << endl; 
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

int main(){
        Array<int> a(5);
        Array<int> b(a);
        return 0;
}

