#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
    // (default) constructor
    Array(const size_t size = 0): m_size(size), m_array(m_size ? new T[m_size]() : nullptr){}
    
    //Деструктор
    ~Array(){
        delete [] m_array;
    }
    
    //Копирование
    Array(const Array &copy) : m_size(copy.m_size), m_array(m_size ? new T[m_size]():nullptr){
        std::copy(copy.m_array, copy.m_array + m_size, m_array);
    }
    
    //Перемещение
    Array(Array&& other){
        delete [] m_array;
        m_size = other.m_size;
        m_array = other.m_array;
        other.m_size = 0;
        other.m_array = nullptr;
    }
    
    //Присваивание
    Array& operator=(const Array &array) {
        size_t copied_size = m_size;
        T copied_array[copied_size];
        std::copy(m_array, m_array + m_size, copied_array);
        if(this != &array){
            try {
                delete [] m_array;
                m_size = array.size();
                m_array = new T[m_size]();
                std::copy(array.m_array, array.m_array + m_size, m_array);
            }
            catch(std::exception &e)
            {
                m_size = copied_size;
                std::copy(copied_array, copied_array + copied_size, m_array);
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
    
private:
    size_t m_size;
    T* m_array;
};
