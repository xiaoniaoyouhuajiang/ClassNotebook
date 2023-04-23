#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

using namespace std;

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

    explicit vector(size_t count = 0):m_first(count ? new value_type[count] : nullptr)
        ,m_last(m_first + count)
    {
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):vector(last - first)
    {
        copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init):vector(init.begin(),init.end())
    {
    }

    vector(const vector& other):vector(other.begin(),other.end())
    {
    }

    vector(vector&& other):m_first(other.begin()),m_last(other.end())
    {
        other.m_first = nullptr;
        other.m_last = nullptr;
    }
    ~vector()
    {
        delete [] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        vector tmp(other.end() - other.begin());
        copy(other.begin(), other.end(), tmp.m_first);
        swap(tmp.m_first, m_first);
        swap(tmp.m_last, m_last);
        return *this;
    }

    vector& operator=(vector&& other)
    {
        delete [] m_first;
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        vector tmp(first, last);
        swap(tmp.m_first, m_first);
        swap(tmp.m_last, m_last);
    }

    // resize methods
    void resize(size_t count)
    {
        vector tmp(count);
        if(m_last - m_first < count)
            copy(m_first, m_last, tmp.m_first);
        else
            copy(m_first, m_first + count, tmp.m_first);
        swap(tmp.m_first, m_first);
        swap(tmp.m_last, m_last);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        rotate(const_cast<iterator>(pos), const_cast<iterator>(pos)+1, m_last);
        m_last = m_last - 1;
        return const_cast<iterator>(pos);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        iterator i = const_cast<iterator>(last);
        while(i != const_cast<iterator>(first))
        {
            erase(--i);
        }
        return const_cast<iterator>(first);
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        vector tmp(size()+1);
        size_t offset = const_cast<iterator>(pos) - m_first;
        copy(m_first, m_first + offset, tmp.m_first);
        *(tmp.m_first + offset) = value;
        copy(m_first + offset, m_last, tmp.m_first+offset+1);
        swap(tmp.m_first, m_first);
        swap(tmp.m_last, m_last);
        return m_first + offset;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        vector tmp(size() + (last - first));
        size_t offset = const_cast<iterator>(pos) - m_first;
        copy(m_first, m_first + offset, tmp.m_first);
        copy(first, last, tmp.m_first + offset);
        copy(m_first + offset , m_last, tmp.m_first + offset + (last - first));
        swap(tmp.m_first, m_first);
        swap(tmp.m_last, m_last);
        return m_first + offset;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        insert(end(), value);
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

int main()
{

    return 0;
}
