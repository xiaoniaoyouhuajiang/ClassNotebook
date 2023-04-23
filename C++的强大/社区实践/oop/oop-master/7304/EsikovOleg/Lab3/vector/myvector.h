#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <assert.h>
#include <algorithm>        // std::copy, std::rotate
#include <cstddef>          // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>

using std::copy;
using std::swap;
using std::rotate;

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

    //constructors
    explicit vector(size_t count = 0) : m_first(new Type[count]), m_last(&(m_first[count])) {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) :  m_first(new Type[last-first]), m_last(m_first + (last-first))
    {
            copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end()) {}

    vector(const vector& other) : m_first(new Type[other.size()]), m_last(&(m_first[other.size()]))
    {
            copy(other.m_first, other.m_last, m_first);
    }

    vector(vector&& other) : m_first(other.m_first), m_last(other.m_last)
    {
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector()
    {
        delete[] m_first;
    }

    //assignment operators
    vector& operator = (const vector& other)
    {
        if(this != &other)
        {
            vector temp(other);
            swap(m_first, temp.m_first);
            swap(m_last, temp.m_last);
        }
        return *this;
    }

    vector& operator = (vector&& other)
    {
        if(this != &other)
        {
            swap(m_first, other.m_first);
            swap(m_last, other.m_last);
        }
        return *this;
    }

    //assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        vector temp(first, last);
        swap(m_first, temp.m_first);
        swap(m_last, temp.m_last);
    }

    //resize methods
    void resize(size_t count)
    {
        vector temp(count);
        size_t delta = count < this->size() ? count : this->size();
        copy(m_first, m_first + delta, temp.m_first);
        swap(m_first, temp.m_first);
        swap(m_last, temp.m_last);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        difference_type result = pos - m_first;
        rotate(m_first + result, m_first + result + 1, m_last);
        resize(size() - 1);
        return m_first + result;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        difference_type result = first - m_first;
        difference_type delta = last - first;
        rotate(m_first + result, m_first + result + delta, m_last);
        resize(size() - delta);
        return m_first + result;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        difference_type result = pos - m_first;
        resize(size() + 1);
        rotate(m_first + result, m_last - 1, m_last);
        m_first[result] = value;
        return m_first + result;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        difference_type i = last - first;
        iterator temp = const_cast<iterator>(pos);
        while(i)
        {
            i--;
            temp = insert(temp, *(first + i));
        }
        return temp;
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

    friend void operator << (std::ostream& os, vector& element)
    {
        for(size_t i = 0; i < element.size(); i++)
            os << element.m_first[i] << " ";
        os << std::endl;
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
