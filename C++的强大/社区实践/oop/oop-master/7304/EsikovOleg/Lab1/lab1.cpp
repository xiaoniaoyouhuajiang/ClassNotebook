#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
    //(default) constructor
    Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
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
    
    //конструктор копирования
    Array(const Array& element) : m_size(element.m_size), m_array(m_size ? new T [m_size] : nullptr)
    {
    try
    {
        if(m_size)
        {
            std::copy(element.m_array, element.m_array + element.m_size, m_array);
        }
    }
    catch(...)
    {
      delete [] m_array;
      throw;
    }
    }
    
    //оператор присваивания
    Array& operator=(Array& element) 
    {
        T* temp_data = nullptr;
        try 
        {
            if(element.m_size)
            {
                temp_data = new T[element.m_size];
                std::copy(element.m_array, element.m_array + element.m_size, temp_data);
            }
            else
                temp_data = nullptr;
        }
        catch(...)
        {
            delete [] temp_data;
            throw;
        }
        delete [] m_array;
        m_size = element.m_size;
        m_array = temp_data;
        return *this;
    }
    
    //конструктор перемещения
    Array(Array&& element) : m_array(element.m_array), m_size(element.m_size)
    {
        element.m_array = nullptr;
    }
    
    //деструктор
    ~Array()
    {
        if(m_array)
            delete [] m_array;
    }
    
private:
    size_t m_size;
    T* m_array;
};
