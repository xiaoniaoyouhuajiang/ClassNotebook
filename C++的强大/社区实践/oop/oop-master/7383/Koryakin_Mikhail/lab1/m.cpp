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
  {}

  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }
    
  Array(Array const& a): m_size(a.m_size), m_array(new T[m_size]) {
      try{
      for (size_t i = 0; i!=m_size; i++ )
          m_array[i] = a.m_array[i];
      }
      catch(...){
          delete [] m_array;
          throw;
      }
  }
  

    
  Array & operator=(const Array& a){
      if(this != &a)
      {
          T* n = a.m_size ? new T[a.m_size]() : nullptr;
          try
          {
              for(size_t i=0; i<a.m_size; i++)
                  n[i] = a.m_array[i];
              delete[] m_array;
              m_array = n;
              m_size = a.m_size;
          }
          catch(...)
          {
              delete[] n;
              throw;
          }
      }
      return *this;
  }
  
  Array(Array&& a){
      m_size = 0;
      m_array = nullptr;
      delete [] m_array;
      swap(m_size, a.m_size);
      swap(m_array, a.m_array);
 
  }
    
  ~Array()
  {
      delete[] m_array;
  }

private:
  size_t m_size;
  T* m_array;
};



void print(Array<char>& elem)
{
        for(unsigned i=0; i<elem.size(); i++)
               cout << elem[i]<< ' ' << (void *)(&elem[i])<<endl;
        cout<<endl;
}


int main()
{
    Array<char> elem(10);
    for(int i=0; i<10; i++)
        elem[i] = i+97;
    cout<<"Исходник"<<endl;
    print(elem);
	
    
    Array<char> cop(elem);
   
    cout<<"Копировние"<<endl;
    print(cop);

    Array<char> per(move(elem));

    cout<<"Перемещение"<<endl;
    print(per);
  


    cout<<"Для сравнение после перемещения"<<endl;
    Array<char> d(10);
    for(int i=0; i<10; i++)
	d[i]=i+107;
    print(d);

    d = cop;
    
    cout<<"Сравнение после присваивания"<<endl;
    print(d);
    print(cop);

    cout << endl;

    return 0;
}
