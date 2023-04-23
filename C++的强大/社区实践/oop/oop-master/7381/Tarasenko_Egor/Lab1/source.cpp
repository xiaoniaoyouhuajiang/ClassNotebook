#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory> // std::unique_ptr

template <typename T>
class Array {
private:
    size_t m_size;
    T* m_array;
    
public:
    // (default) constructor
    Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr) { }

    const size_t size() const {
        return m_size;
    }

    T& operator[] (const size_t index) {
        assert(index < m_size);
        return m_array[index];
    }
    
    Array& operator= (Array& a) {
        std::unique_ptr<T[]> arr(new T[a.m_size]);
        std::copy(a.m_array, a.m_array + a.m_size, arr.get());
        if(this != &a) {
            m_size = a.m_size;
            m_array = new T[m_size];
            std::copy(arr.get(), arr.get() + m_size, m_array);
        }
        return *this;
    }
    
    // copy constructor
    Array(const Array& a) : m_size(a.m_size) {
        m_array = new T[a.m_size];
        std::copy(a.m_array, a.m_array + a.m_size, m_array);
    }
    
    // move constructor
    Array(Array&& a) {
        m_array = a.m_array;
        m_size = a.m_size;
        a.m_array = nullptr;
        a.m_size = 0;
    }
    
    // destructor
    ~Array() {
        m_size = 0;
        delete[] m_array;
    }
};