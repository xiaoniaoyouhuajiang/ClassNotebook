
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>
#include <new>

template<typename T>
class Array
{
public:
    // default constructor
    Array(const size_t size = 0)
        : m_size(size)
        , m_array(m_size ? new T[m_size]() : nullptr)
    {
    }

    // copy constructor
    Array(const Array<T> &other)
        : Array(other.m_size)
    {
        std::copy(other.m_array.get(), other.m_array.get() + other.size(), m_array.get());
    }

    // move constructor
    Array(Array<T> &&other)
        : Array()
    {
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
    }
    
    // copy assignment
    Array<T>& operator=(const Array<T>& other)
    {
        Array<T> temp(other);
        std::swap(m_size, temp.m_size);
        std::swap(m_array, temp.m_array);
        return *this;
    }

    // move assignment
    Array<T>& operator=(Array<T>&& other)
    {
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
        return *this;
    }

    const size_t size() const noexcept
    {
        return m_size;
    }

    T& operator [](const size_t index)
    {
        assert(index < m_size);

        return m_array[index];
    }

    ~Array() {
        m_array.reset();
    }
private:
    size_t m_size;
    std::unique_ptr<T[]> m_array;
};

int main()
{
    return EXIT_SUCCESS;
}