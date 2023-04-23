#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>

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

    Array(const Array<T>& other)
        : m_size(other.m_size)
        , m_array(m_size ? new T[m_size]() : nullptr)
    {
        std::copy(other.m_array.get(), other.m_array.get() + m_size, m_array.get());
    }

    Array(const Array<T>&& other)
        : m_size(std::move(other.m_size))
        , m_array(std::move(other.m_array))
    {
    }

    const size_t size() const{
        return m_size;
    }

    T& operator [](const size_t index){
        assert(index < m_size);
        return m_array[index];
    }

    Array<T> & operator=(const Array<T>& other){
        if(this != &other){
            Array<T>(other).swap(*this);
            return *this;
        }
    }

    void swap(Array<T>& other){
        std::swap(m_size, other.m_size);
        std::swap(m_array, other.m_array);
    }

private:
    size_t m_size;
    std::unique_ptr<T[]> m_array;
};
