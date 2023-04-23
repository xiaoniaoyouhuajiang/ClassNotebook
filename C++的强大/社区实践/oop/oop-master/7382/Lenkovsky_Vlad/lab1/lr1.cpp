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

  const size_t size() const
  {
    return m_size;
  }

  ~Array() {
	  delete [] m_array;
  }

  Array(const Array &other)
    : m_size(other.m_size)
    , m_array(other.m_size ? new T[other.m_size]() : nullptr)
  {
        copy(other.m_array,other.m_array+other.m_size,m_array);
  }

  Array &operator=(const Array &other) {
	  if (this != &other) {
	  size_t first_size = other.m_size;
	  T first_array[first_size];
	  copy(m_array, m_array + m_size, first_array);
		  try {
			  m_array = new T[other.m_size];
			  copy(other.m_array, other.m_array + other.m_size, m_array);
			  m_size = other.m_size;
		  }
		  catch(exception &fnd){
			  m_size = first_size;
			  copy(first_array, first_array + first_size, m_array);
		  }
	  }
	  return *this;
  }

  Array(Array &&other) :m_size(other.m_size),m_array(other.m_array)
  {
        other.m_size=0;
        other.m_array=nullptr;
  //      cout << "Ready" << endl;
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
