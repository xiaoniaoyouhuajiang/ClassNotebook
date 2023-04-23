#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

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


    Array(const Array &A) : Array(A.size()) {
        std :: copy(A.m_array, A.m_array+A.size(), m_array);
    }

    Array & operator = (const Array & A)
    {
        if (this != &A)
        {
            T* obj = A.m_size ? new T[A.m_size]() : nullptr;
            try
            {
                std::copy(A.m_array, A.m_array + A.m_size, obj);
                delete[] m_array;
                m_array = obj;
                m_size = A.m_size;
            }
            catch(...)
            {
                delete[] obj;
                throw;
            }
        }
        return *this;
    }

    Array(Array && A)
    {
        std::swap(m_size, A.m_size);
        std::swap(m_array, A.m_array);
    }


    ~Array()
    {
        delete[] m_array;
    }

private:
    size_t m_size;
    T* m_array;
};
