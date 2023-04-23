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

    ~Array(){
    if(m_array)
    delete[] m_array;
    m_array = nullptr;
    m_size = 0;
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

    Array(Array& obj)
    : m_size(obj.m_size)
    , m_array(m_size ? new T[m_size]() : nullptr)
    {
    std::copy(obj.m_array, obj.m_array+obj.m_size, m_array);
    }

    Array(Array&& obj)
    : m_size(obj.m_size)
    , m_array(m_size ? new T[m_size]() : nullptr)
    {
    obj.m_array = nullptr;
    obj.m_size = 0;
    }
    Array& operator = (Array & obj){
    if(&obj == this) return *this;
    Array temp(obj.m_size);
    try{
    std::copy(obj.m_array, obj.m_array + obj.m_size, temp.m_array);
    delete[] m_array;
    m_size = obj.m_size;
    m_array = temp.m_array;
    temp.m_array = nullptr;
    }
    catch(...){
    delete[] temp.m_array;
    temp.m_array = nullptr;
    throw;
    }
    return *this;
    }

    private:
    size_t m_size;
    T* m_array;
    };
