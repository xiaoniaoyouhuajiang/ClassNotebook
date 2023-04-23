#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0)
    {
        m_first = new Type[count];
        m_last = m_first + count;
        for (int i = 0; i < size(); i++)
            m_first[i] = 0;
      // use previous step implementation
    }

    template <typename InputIterator>
/*Создает контейнер с содержимым диапазона [first, last).*/
    vector(InputIterator first, InputIterator last) : vector(last-first)
    {
        std::copy(first, last, m_first);
      // use previous step implementation
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
    {
      // use previous step implementation
    }

    vector(const vector& other)
    {
        m_first = new Type[other.size()];
        m_last = &(m_first[other.size()]);
        std::copy(other.m_first, other.m_last, m_first);
      // use previous step implementation
    }

    vector(vector&& other)
    {
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
      // use previous step implementation
    }

    ~vector()
    {
        delete []m_first;
      // use previous step implementation
    }

      
    static void swap(vector& that, vector& other)
    {
        std::swap(that.m_first, other.m_first);
        std::swap(that.m_last, other.m_last);
    }
    //assignment operators
    vector& operator=(const vector& other)
    {
        if (this != &other) {
            vector tmp(other);
            swap(*this, tmp);
        }
        return *this;
      // implement this
    }

    vector& operator=(vector&& other)
    {
        if (this != &other)
            swap(*this, other);
        return *this;
      // implement this
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        vector tmp(first, last);
        swap(*this, tmp);
      // implement this
    }
      
    void resize(size_t count)
    {
        size_t new_size = count < (m_last-m_first) ? count : (m_last-m_first);   
        vector tmp(count);
        std::copy(m_first, m_first + new_size, tmp.m_first);
        swap(*this, tmp);
      // implement this
    }
      
    void push_back(const Type& value)
    {
        resize(size() + 1);
        *(m_last - 1) = value;
      // implement this
    }  
      
    iterator insert(const_iterator pos, const Type& value)
    {  
        vector temp_vector(pos - m_first);
        difference_type tmp = pos - m_first;
        std::copy(m_first, tmp + m_first, temp_vector.m_first);
        temp_vector.push_back(value);
        temp_vector.resize(size()+1);
        std::copy(m_first + tmp, m_last, temp_vector.m_first + 1);
        *this = std::move(temp_vector);
        return tmp + m_first;
      // implement this
    }
      
    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        difference_type tmp_pos = pos - m_first;
        difference_type tmp_range = last - first;
        vector temp_vector(size() + tmp_range);
        std::copy(m_first, tmp_pos + m_first, temp_vector.m_first);
        std::copy(first, last, temp_vector.m_first + tmp_pos);
        std::copy(m_first + tmp_pos, m_last, temp_vector.m_first + tmp_pos + tmp_range);
        *this = std::move(temp_vector);
        return tmp_pos + m_first;
        // implement this
    }

    //push_back methods

    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:   
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik