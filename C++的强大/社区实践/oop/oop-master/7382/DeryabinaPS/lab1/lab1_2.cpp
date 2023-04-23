
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
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  { cout << "default constructor" << endl; }
  // copy
  Array(Array const &A) : m_size(A.m_size), m_array(new T[m_size]){

  	cout << "copy" << endl;
	try {
		if (m_size) {
			for (int i = 0; i < m_size; i++) { m_array[i] = A.m_array[i]; }
			}

			else { m_array = nullptr; }
	    }
	catch (...) {
		delete[] m_array;
		throw;
		}
  }
  //=
  Array & operator=(Array A)
  {
  	cout << "=" << endl;
        std::swap(m_size, A.m_size);
        std::swap(m_array, A.m_array);
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

  // move
  Array(Array&& A) : m_size(A.m_size), m_array(A.m_array)
  {
  	cout << "move" << endl;
        delete [] A.m_array;
        A.m_array = nullptr;
        A.m_size = 0;
  }

  ~Array()
  {
  	cout << "destructor" << endl;
  	delete [] m_array;
  	m_size = 0;
  }

private:
  size_t m_size;
  T* m_array;
};

