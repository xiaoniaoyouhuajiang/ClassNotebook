#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef>   // size_t
#include <iostream>

template <typename T>
class Array
{
  public:
    // (default) constructor
    Array(const size_t size = 0)
        : m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
    {
	std::cout << "дефолтный конструктор" << std::endl;
    }
    //деструктор
    ~Array()
    {
        delete[] m_array;
    }
    //оператор присваивания
    Array &operator=(const Array &another)
    {
        std::cout << "оператор присваивания" << std::endl;
        if (this == &another)
            return *this;

        Array tmp = another;
        delete[] m_array;
        m_size = tmp.size();

        if (m_size)
        {
            m_array = new T[m_size];
            for (size_t i = 0; i < m_size; i++)
            {
                m_array[i] = tmp.m_array[i];
            }
        }
        else
        {
            m_array = nullptr;
        }
        return *this;
    }

    //конструктор копирования
    Array(const Array &another)
    {
        std::cout << "конструктор копирования" << std::endl;
        Array tmp(another.size());
        for (size_t i = 0; i < tmp.size(); i++)
        {
            tmp.m_array[i] = another.m_array[i];
        }
        m_size = tmp.m_size;

        if (m_size)
        {
            m_array = new T[m_size];
            for (size_t i = 0; i < m_size; i++)
            {
                m_array[i] = tmp.m_array[i];
            }
        }
        else
        {
            m_array = nullptr;
        }
    }
    //конструктор перемещения 
    Array(const Array &&another)
    {
        std::cout << "конструктор перемещения" << std::endl;
        Array tmp = another;
        delete[] m_array;
        m_size = tmp.size();

        if (m_size)
        {
            m_array = new T[m_size];
            for (size_t i = 0; i < m_size; i++)
            {
                m_array[i] = tmp.m_array[i];
            }
        }
        else
        {
            m_array = nullptr;
        }
        tmp.~Array();
    }

    const size_t size() const
    {
        return m_size;
    }

    T &operator[](const size_t index)
    {
        assert(index < m_size);

        return m_array[index];
    }

  private:
    size_t m_size;
    T *m_array;
};
int main()
{
    Array<int> a(5);
    std::cout << "1-------------------" << std::endl;
    Array<int> b = a;
    std::cout << "2-------------------" << std::endl;
    Array<int> c;
    std::cout << "3-------------------" << std::endl;
    c = b;
    return 0; 
}
