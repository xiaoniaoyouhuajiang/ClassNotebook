#ifndef MYVECTOR_H
#define MYVECTOR_H


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
        m_first = new value_type[count];
        m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        size_t count = last - first;
        m_first = new value_type[count];
        m_last = m_first + count;

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

    }

    vector(const vector& other) : vector(other.begin(), other.end())
    {

    }

    vector(vector&& other)
    {
        m_first = other.m_first;
        m_last = other.m_last;

        other.m_first = other.m_last = nullptr;
    }

    ~vector()
    {
        delete[] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        assert(this != &other);

        vector v(other);
        swap(v);

        return *this;
    }

    vector& operator=(vector&& other)
    {
        assert(this != &other);

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
        vector v(first, last);
        *this = std::move(v);
    }

    void swap(vector& other)
    {
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
    }

    // resize methods
    void resize(size_t count)
    {
        iterator end = (count > size()) ? m_last : m_first + count;

        vector v(count);
        std::move(m_first, end, v.m_first);

        swap(v);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        iterator pos_ = const_cast<iterator>(pos);
        size_t n = pos - m_first;

        std::rotate(pos_, pos_ + 1, m_last);
        resize(size() - 1);

        return (m_first + n);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        size_t count = last - first;

        iterator it = const_cast<iterator>(first);

        while (count)
        {
            it = erase(it);
            count--;
        }

        return it;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t n = pos - m_first;
        resize(size() + 1);

        iterator pos_ = m_first + n;
        std::rotate(pos_, m_last - 1, m_last);
        *pos_ = value;

        return pos_;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t count = last - first;
        iterator p = const_cast<iterator>(pos);

        while (count)
        {
            p = insert(p, first[--count]);
        }

        return p;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        insert(m_last, value);
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
  };
}// namespace stepik

#endif // MYVECTOR_H