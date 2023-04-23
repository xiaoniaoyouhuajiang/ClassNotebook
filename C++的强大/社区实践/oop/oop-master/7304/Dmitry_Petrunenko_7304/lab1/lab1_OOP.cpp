#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <utility>
#include <memory>

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
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

Array(const Array &other) : m_size(other.size())
    , m_array(m_size ? new T[m_size]() : nullptr){
        try{
        std::copy(other.m_array, other.m_array+other.size(),m_array);}
        catch(...){
            this->~Array();
          throw;
        }
    }


     Array &operator=(const Array &other){
    if(this != &other)
        Array(other).swap(*this);
        return *this;
    }


  void swap(Array &other){
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
    }


 Array(Array&& other)
  {
   swap(other);
  }

     Array& operator=(Array&& other)
 {
    swap(other);
     return *this;
 }

  ~Array(){
    delete [] m_array;
  }
private:
  size_t m_size;
  T* m_array;
};