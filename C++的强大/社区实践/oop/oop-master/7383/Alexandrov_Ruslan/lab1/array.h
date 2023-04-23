#ifndef ARRAY_H
#define ARRAY_H
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>
template<typename T>
class Array {
public:
    // (default) constructor
    Array(const size_t size = 0)
            : m_size(size), m_array(m_size ? new T[m_size]() : nullptr) {
    }

    Array(const Array &array)
            : m_size(array.m_size), m_array(array.m_size ? new T[array.m_size]() : nullptr) {
        if (this->m_array != nullptr && array.m_array != nullptr)
            std::copy(array.m_array, array.m_array + array.m_size, this->m_array);
    }

    Array(Array &&array)
            : m_size(array.m_size), m_array(array.m_size ? new T[array.m_size]() : nullptr) {
        if (array.m_array != nullptr)
            m_array = array.m_array;
        array.m_array = nullptr;
        array.m_size = 0;
    }

    ~Array() {
        delete[] m_array;
    }

    Array &operator=(Array &array);

    const size_t size() const {
        return m_size;
    }

    T &operator[](const size_t index) {
        assert(index < m_size);

        return m_array[index];
    }
private:
    size_t m_size;
    T *m_array;
};

template<typename T>
Array<T> &Array<T>::operator=( Array &array) {
    if (this != &array) {
        std::unique_ptr<T[]> new_m_arr(new T[array.m_size]);
        std::copy(array.m_array, array.m_array + array.m_size, new_m_arr.get());
        delete[] m_array;
        m_size= array.m_size;
        m_array = new_m_arr.release();
        //  m_size = array.m_size;
    }
    return *this;
}


#endif ARRAY_H
