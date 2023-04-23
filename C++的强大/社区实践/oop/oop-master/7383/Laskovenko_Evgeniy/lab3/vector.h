#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

#ifndef VECTOR_H
#define VECTOR_H


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
        m_first = count ? new Type[count]() : nullptr;
        m_last = count ? m_first + count : nullptr;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        difference_type size = last - first;
        m_first = size>0 ? new Type[size] : nullptr;
        std::copy(first, last, m_first);
        m_last = size>0 ? m_first + size : nullptr;
    }

    vector(std::initializer_list<Type> init)
    {
        m_first = init.size() ? new Type[init.size()] : nullptr;
        std::copy(init.begin(), init.end(), m_first);
        m_last = init.size() ? m_first + init.size() : nullptr;
    }

    vector(const vector& other)
    {
        m_first = other.size() ? new Type[other.size()] : nullptr;
        std::copy(other.begin(), other.end(), m_first);
        m_last = other.size() ? m_first + other.size() : nullptr;
    }

    vector(vector&& other)
    {
        m_first = other.begin();
        m_last = other.end();
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector()
    {
        delete[] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        if(m_first != other.begin())
        {
            delete[] m_first;
            m_first = other.size() ? new Type[other.size()] : nullptr;
            std::copy(other.begin(), other.end(), m_first);
            m_last = other.size() ? m_first + other.size() : nullptr;
        }

        return *this;
    }

    vector& operator=(vector&& other)
    {
        if(m_first != other.begin())
        {
            delete[] m_first;
            m_first = other.begin();
            m_last = other.end();
            other.m_first = nullptr;
            other.m_last = nullptr;
        }

        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        difference_type size = last - first;
        delete[] m_first;
        m_first = size ? new Type[size] : nullptr;
        std::copy(first, last, m_first);
        m_last = size ? m_first + size : nullptr;
    }
    // resize methods
    void resize(size_t count)
    {
        iterator tmp = count ? new Type[count] : nullptr;
        if(count >= size())
            std::copy(m_first, m_last, tmp);
        else
            std::copy(m_first, m_first + count, tmp);
        delete[] m_first;
        m_first = tmp;
        m_last = count ? m_first + count : nullptr;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        size_t i=0;
        iterator cur = m_first;
        while(cur != pos)
        {
            cur++;
            i++;
        }

        std::rotate(cur, cur+1, m_last);
        resize(size()-1);

        return m_first + i;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        iterator cur = m_first;
        while(cur != first)
            cur++;

        difference_type sz = last - first;
        for(size_t i=0; i<sz; ++i)
            cur = erase(cur);

        return cur;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t i = 0;
        while((m_first + i) != pos)
            i++;

        push_back(value);
        std::rotate(m_first + i, m_last - 1, m_last);

        return m_first + i;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t i = 0;
        while((m_first + i) != pos)
            i++;

        difference_type sz = last - first;
        for(size_t j=0; j<sz; ++j)
            push_back(*(first + j));
        std::rotate(m_first + i, m_last - sz, m_last);

        return m_first + i;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        resize(size() + 1);
        *(m_last - 1) = value;
    }

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


private:
    iterator m_first;
    iterator m_last;
};

#endif // VECTOR_H
