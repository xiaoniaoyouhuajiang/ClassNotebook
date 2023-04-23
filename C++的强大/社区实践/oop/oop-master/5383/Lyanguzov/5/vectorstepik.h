#ifndef VECTORSTEPIK_H
#define VECTORSTEPIK_H
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
      // implement this
      m_first = new Type[count];
      for(unsigned int i = 0; i < count; i++)
      {
          //m_first[i] = 0;
      }
      m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
      // implement this
        size_t size = last - first;

        m_first = new Type[size];
        m_last = m_first + size;
        try
        {
            std::copy(first, last, m_first);
        }
        catch(...)
        {
            delete[] m_first;
            throw;
        }
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
    {
      // implement this

    }

    vector(const vector& other): vector(other.begin(), other.end())
    {
      // implement this
    }

    vector(vector&& other)
    {
      // implement this
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
    }

    ~vector()
    {
      // implement this
        delete[] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      // implement this
      vector tmp(other);
      swap(tmp);
      return *this;
    }

    vector& operator=(vector&& other)
    {
      // implement this
        assert( this != &other );
        delete[] m_first;

        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      // implement this
        vector tmp(first, last);
        swap(tmp);
    }

    // resize methods
    void resize(size_t count)
    {
      // implement this
        size_t size = m_last - m_first;
        iterator last = (count >= size) ? m_last : m_first + count;
        vector result(count);
        std::move(m_first, last, result.m_first);
        swap(result);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      // implement this
        size_t start_position = pos - m_first;
        iterator end_position = m_last;
        iterator _pos = const_cast<iterator>(pos);
        std::rotate(_pos, _pos + 1, end_position);
        resize(size()-1);
        return (m_first + start_position);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      // implement this
        size_t size = last - first;

        iterator tmpIt = const_cast<iterator>(first);

        while(size)
        {
            tmpIt = erase(tmpIt);
            size--;
        }

        return tmpIt;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      // implement this
        size_t n = pos - m_first;
        push_back(value);
        std::rotate(m_first + n, m_last - 1, m_last);
        return m_first + n;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      // implement this
        size_t size = last - first;


        iterator tmpIt = const_cast<iterator>(pos);
        while(size)
        {
            tmpIt = insert(tmpIt, first[size-1]);
            size--;
        }
        return tmpIt;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      // implement this
        resize(size()+1);
        m_first[size() - 1] = value;
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

    //your private functions

  private:
    iterator m_first;
    iterator m_last;

    void swap(vector &v)
    {
        std::swap(this->m_first, v.m_first);
        std::swap(this->m_last, v.m_last);
    }

  };
}// namespace stepik

#endif // VECTORSTEPIK_H
