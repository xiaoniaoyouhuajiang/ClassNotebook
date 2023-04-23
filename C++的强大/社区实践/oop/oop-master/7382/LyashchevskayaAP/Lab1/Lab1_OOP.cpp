#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
	std::cout << "КОНСТРУКТОР ПО УМОЛЧАНИЮ" << std::endl;
  }
  //Конструктор копирования
  Array(const Array &obj)
  {
	std::cout << "КОНСТРУКТОР КОПИРОВАНИЯ" << std::endl;
    if(!obj.m_size)
    {
      *this = Array (0);
      return;
    }
    Array tmp(obj.size());
    std::copy(obj.m_array, obj.m_array + obj.m_size, tmp.m_array);

    m_size = tmp.m_size;
    m_array = new T[m_size]();
    std::copy(tmp.m_array, tmp.m_array + tmp.m_size, m_array);
  }
  //Оператор присваивания
  Array & operator=(const Array &obj)
  {
	std::cout << "ОПЕРАТОР ПРИСВАИВАНИЯ" << std::endl;
    Array tmp(*this);
    try{
      if(this != &obj)
      {
        if(m_size)
          delete [] m_array;
        m_size = obj.m_size;
        m_array = new T[obj.m_size]();
        std::copy(obj.m_array, obj.m_array + obj.m_size, m_array);
      }
      return *this;
    }
    catch(...)
    {
      m_size = tmp.m_size;
      m_array = std::move(tmp.m_array);
    }
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
    
  ~Array()
  {
    delete [] m_array;
    m_size = 0;
  }
    
private:
  size_t m_size;
  T* m_array;
};

int main(){
	Array <int>a = Array <int>(4);
	std::cout << "________" << std::endl;
	Array <int> b(6);
	std::cout << "________" << std::endl;
	a = b;
	std::cout << "________" << std::endl;
	a = Array <int> (8);
	std::cout << "________" << std::endl;
	Array <int> c = a;
	std::cout << "________" << std::endl;
	Array <int> d = std::move(a);
	std::cout << "________" << std::endl;
	std::cout << a.size() << std::endl;
	return 0;
}
