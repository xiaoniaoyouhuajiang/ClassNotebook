#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
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
  }
//destructor    
  ~Array() {
    delete[]m_array;
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
    
//copy constructor
   Array(Array& get_array){
        m_size = get_array.m_size;
        m_array = new T[m_size];
        copy(get_array.m_array, get_array.m_array + m_size, m_array);
    }
    
//move constructor
    Array(Array&& get_array){
        delete[]m_array;
        m_size = get_array.m_size;
        m_array = new T[m_size];
        copy(get_array.m_array, get_array.m_array + m_size, m_array); 
        delete get_array;    
    }
    
//operator=
    Array& operator=(Array& get_array) {
    unique_ptr<T[]> array(new T[get_array.m_size]);
    copy(get_array.m_array, get_array.m_array + get_array.m_size, array.get());
    if (this != &get_array) {
        m_size = get_array.m_size;
        m_array = new T[m_size];
        copy(get_array.m_array, get_array.m_array + m_size, m_array);
        array.reset();
        }
    return *this;
    }
   
    
private:
  size_t m_size;
  T* m_array;
};

