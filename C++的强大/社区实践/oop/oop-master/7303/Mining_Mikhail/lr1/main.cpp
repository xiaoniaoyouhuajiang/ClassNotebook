#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template <typename T>
class Array {
public:
    // (default) constructor
    Array(const size_t size = 0)
        : m_size(size)
        , m_array(m_size ? new T[m_size]() : nullptr)
    {
    }

    Array(const Array &temp)
        : Array(temp.size())
    {
        std::copy(temp.m_array, temp.m_array+temp.size(), m_array);
    }

    Array (Array &&temp) : m_size(temp.m_size), m_array(temp.m_array)
    {
        ~Array();
    }

    Array & operator = (const Array &temp) {
        if (this != &temp) {
            Array new_Arr(temp);
            m_size = new_Arr.size();
            m_array = m_size ? new T[m_size]() : nullptr;
            std::copy(new_Arr.m_array, new_Arr.m_array+new_Arr.size(), m_array);
        }
        return *this;
    }

    const size_t size() const
    {
        return m_size;
    }

    T& operator [](const size_t index) {
        assert(index < m_size);

        return m_array[index];
    }

    ~Array() {
        destroy();
    }

private:
    void destroy()
    {
        if (m_array) delete[] m_array;
    }
    size_t m_size;
    T* m_array;
};

