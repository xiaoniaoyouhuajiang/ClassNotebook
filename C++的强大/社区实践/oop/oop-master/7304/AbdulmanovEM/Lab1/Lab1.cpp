#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>
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

  Array(const Array& arr){
    copyArray(arr,nullptr,0);
  }

  Array( Array&& arr){
    m_size=arr.m_size;
    m_array=arr.m_array;
    m_array=nullptr;
  }

  Array& operator=(const Array& arr){
      copyArray(arr,m_array,m_size);
      return *this;
  }

   Array sss(){
        return Array<int>(100);
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
private:
  size_t m_size;
  T* m_array;
  void copyArray(const Array& arr,T* save_array,size_t save_size){
      if(arr.m_size&&(&arr)!=this){
        try{
            m_size=arr.m_size;
            std::unique_ptr<T[]> new_array( new T[m_size] );
            copy(arr.m_array,arr.m_array+arr.m_size,new_array.get());
            m_array=new_array.release();
            if(save_array)
                delete [] save_array;
        }catch(...){
            m_size=save_size;
            m_array=save_array;
            throw;
        }
    }
  }
};

int main()
{
    return 0;
}
