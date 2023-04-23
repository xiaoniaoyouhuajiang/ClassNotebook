#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>

class Array
{
public:
  // (default) constructor
    Array(const size_t size = 0) : m_size(size) , m_array(m_size ? new T[m_size]() : nullptr){}

  //Конструктор перемещения
    Array(const Array&& array)
    {
      delete [] m_array;
      m_size = array.m_size;
      m_array = array.m_array;
      array.m_size = 0;
      array.m_array = nullptr;
    }

  //Конструктор копирования
    Array(const Array &array) : m_size(array.m_size), m_array(m_size ? new T[m_size]():nullptr)
    {
      for(size_t i = 0; i != m_size; i++)
      {
         m_array[i] = array.m_array[i];
      }
    }

  //Оператор присваивания
    Array& operator=(const Array& array)
    {
        if(this != &array)
        {
            T *element = nullptr;
            try
	    {
                element = new T[array.size()];
                for(size_t i = 0; i < array.size(); i++)
                    element[i] = array.m_array[i];
            }
            catch(...)
	    {
                delete[] element;
                throw;
            }
            if(element != nullptr)
	    {
                m_size = array.size();
                delete[] m_array;
                m_array = element;
            }
        }
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

  // Деструктор
  ~Array()
  {
    delete [] m_array;
  }

private:
  size_t m_size;
  T* m_array;
};
