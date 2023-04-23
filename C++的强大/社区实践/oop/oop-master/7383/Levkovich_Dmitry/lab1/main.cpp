#include <assert.h>
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
using namespace std;

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0): m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
  {
      cout<<"default"<<endl;
  }

    Array(const Array& a){
        cout<<"copy"<<endl;
        m_size = a.m_size;
        if(m_size)
            m_array = new T[m_size];
        else
            m_array = nullptr;
        try{
        copy( a.m_array, a.m_array+a.m_size, m_array);
        }catch(...){
            delete[] m_array;
            throw;
        }
    }


      Array& operator = (const Array &a)
     {
      cout<<"operator"<<endl;
      Array temp(a);
      m_size = temp.m_size;
      m_array = m_size ? new T[m_size]() : nullptr;
      copy(temp.m_array, temp.m_array+temp.size(),m_array);
      return *this;
     }

    Array(Array&& a){
        cout<<"move"<<endl;
        m_array = a.m_array;
        m_size = a.m_size;
        a.m_size = 0;
        a.m_array = nullptr;
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
      ~Array(){
     delete[] m_array;
  }
  T* get_array() const{
      return m_array;
  }
private:
  size_t m_size;
  T* m_array;
};


void print(Array<int>& a)
{
        for(unsigned i=0; i<a.size(); i++)
               cout << a[i]<< ' ' << &a[i]<<endl;
        cout<<endl;
}


int main()
{
    Array<int> a(5);
    for(int i=0;i<5;i++)
        a[i] = i;

    print(a);

    Array<int> b(a);

    print(b);

    Array<int> c(move(a));

    print(c);

    c = b;

    print(c);

    print(b);
    cout << endl;

    return 0;
}
