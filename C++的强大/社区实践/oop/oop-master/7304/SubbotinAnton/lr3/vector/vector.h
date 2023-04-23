#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
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

    explicit vector(size_t count = 0) : m_first(new Type[count]), m_last(&(m_first[count])) {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : m_first(new Type[last - first]), m_last(m_first + (last - first))
    {
      std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end()) {}

    vector(const vector& other) : m_first(new Type[other.size()]), m_last(&(m_first[other.size()]))
    {
      std::copy(other.m_first, other.m_last, m_first);
    }

    vector(vector&& other) : m_first(other.m_first), m_last(other.m_last)
    {
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector()
    {
      delete[] m_first;
      m_first = nullptr;
      m_last = nullptr;
    }

    vector& operator=(const vector& other)
    {
      if(this != &other){
        vector temp(other);
        std::swap(m_first, temp.m_first);
        std::swap(m_last, temp.m_last);
      }
      return *this;
    }

    vector& operator=(vector&& other)
    {
      if(this != &other){
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
      }
      return *this;
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      vector temp(first, last);
      std::swap(m_first, temp.m_first);
      std::swap(m_last, temp.m_last);
    }

    void resize(size_t count)
    {
      vector temp(count);
      size_t min = count < this->size() ? count : this->size();
      std::copy(m_first, m_first + min, temp.m_first);
      std::swap(m_first, temp.m_first);
      std::swap(m_last, temp.m_last);
    }

    iterator erase(const_iterator pos)
    {
      difference_type index = pos - m_first;
      std::rotate(m_first + index, m_first + index + 1, m_last);
      resize(size() - 1);
      return m_first + index;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      difference_type index = first - m_first;
      difference_type delta = last - first;
      std::rotate(m_first + index, m_first + index + delta, m_last);
      resize(size() - delta);
      return m_first + index;
    }

    iterator insert(const_iterator pos, const Type& value)
    {
      difference_type index = pos - m_first;
      resize(size() + 1);
      std::rotate(m_first + index, m_last - 1, m_last);
      m_first[index] = value;
      return m_first + index;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      difference_type index = pos - m_first;
      resize(size() + (last - first));
      std::copy(first, last, m_last - (last - first));
      std::rotate(m_first + index, m_last - (last - first) , m_last);
      return m_first + index;
    }

    void push_back(const value_type& value)
    {
      insert(m_last, value);
    }

    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    size_t size() const
    {
      return m_last - m_first;
    }

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

    friend void operator << (std::ostream& os, vector& v)
    {
        for(size_t i(0); i < v.size(); i++)
            os << v.m_first[i] << " ";
        os << std::endl;
    }

    iterator m_first;
    iterator m_last;
  };
}

#endif // VECTOR_H
