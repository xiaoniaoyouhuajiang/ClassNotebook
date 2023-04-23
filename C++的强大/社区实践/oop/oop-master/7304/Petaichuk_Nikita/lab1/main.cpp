#include <assert.h>
#include <iostream>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <exception>

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
    cout << "Usual constructor called" << endl;
  }

private: 
  Array(const Array &other) /*:
    m_size(other.m_size),
    m_array(m_size ? new T[m_size]() : nullptr)*/ = delete;
/*{
    cout << "Copy constructor called" << endl;
    copy(other.m_array, other.m_array + m_size, m_array);
  }*/

public:
  Array(Array&& other)
  {
    cout << "Move constructor called" << endl;
    m_size = other.m_size;
    m_array = other.m_array;
    other.m_array = nullptr;
    other.m_size = 0;
  }
    
  Array& operator=(const Array& other)
  {
    cout << "Operator '=' called" << endl;
    size_t copied_size = m_size;
    T copied_array[copied_size];
    copy(m_array, m_array + m_size, copied_array);
    if (this != &other)
    {
        try
        {
            delete [] m_array;
            m_size = other.size();
            m_array = new T[m_size]();
            copy(other.m_array, other.m_array + m_size, m_array);
        }
        catch (std::exception &e)
        {
            m_size = copied_size;
            copy(copied_array, copied_array + copied_size, m_array);        
        }
    }
    return *this;
  }
    
  ~Array()
  {
    cout << "Array destruction" << endl;
    delete [] m_array;
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
  int index;
};

void print_array(Array<int> &array)
{
  for (int i = 0; i < 10; i++)
      cout << array[i] << " ";
  cout << endl;
  return;
}

Array<int> create_array(Array<int> array)
{
  return array;
}

int main()
{
  Array<int> array_first(10);

  for (int i = 0; i < 10; i++)
      array_first[i] = i;
  print_array(array_first);

  Array<int> array_second = create_array(Array<int>(10));
  Array<int> array_third = array_first;
  
  print_array(array_third);

  array_second = array_third;

  print_array(array_second);
      
  return 0;
}
