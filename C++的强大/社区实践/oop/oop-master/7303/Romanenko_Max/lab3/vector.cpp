#include <assert.h>
#include <iostream>
#include <iterator>
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
        if (count > 0){
            m_first = new value_type[count];
            m_last = m_first + count;
        }
        else{
            m_first = m_last = nullptr;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
            if (last - first > 0){
            m_first = new value_type[last - first];
            m_last = m_first + (last - first);
            std::copy(first,last, m_first);
            }
            else{
                m_first = m_last = nullptr;
            }
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end()){
    }

    vector(const vector& other): vector(other.begin(), other.end()){
    }

    vector(vector&& other): m_first(other.m_first), m_last(other.m_last){
          other.m_first = other.m_last = nullptr;
    }

    ~vector()
    {
      delete[] m_first;
      m_first = m_last = nullptr;
    }

    vector& operator=(const vector& other) {
      if (this != &other) {
        delete[] m_first;
        m_first = new value_type[other.size()];
        std::copy(other.m_first, other.m_last, m_first);
        m_last = m_first + other.size();
      }
      return *this;
    }

    vector& operator=(vector&& other) {
      if (this != &other) {
        delete[] m_first;
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
      }
      return *this;
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        delete[] m_first;
        m_first = new value_type[last-first];
        m_last = m_first + (last-first);
        std::copy(first, last, m_first);
    }

    void resize(size_t count)
        {
            if(count == size()) return;
            iterator temp = new value_type[count];
            if(count > size())
                std::copy(m_first, m_last, temp);
            else
                std::copy(m_first, m_first+count, temp);
            delete[] m_first;
            m_first = temp;
            m_last = m_first+count;
        }


        iterator erase(const_iterator pos)
        {
            size_t new_pos = pos - m_first;
            std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos)+1, m_last);
            resize(size() - 1);
            return m_first + new_pos;
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            size_t new_pos = last - first;
            iterator new_first = const_cast<iterator>(first);
            while (new_pos != 0) {
                  new_first = erase(new_first);
                  new_pos--;
            }
            return new_first;
        }

        iterator insert(const_iterator pos, const Type& value) {
            size_t len = size()+1;
            iterator temp = new value_type[len];
            size_t d = pos-m_first;
            std::copy(m_first, m_first+d, temp);
            *(temp+d) = value;
            std::copy(m_first+d, m_last, temp);
            delete[] m_first;
            m_first = temp;
            m_last = m_first+len;
            return m_first+d;
        }


        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
            size_t len = size()+(last-first);
            iterator temp = new value_type[len];
            size_t d = pos-m_first;
            std::copy(m_first, m_first+d, temp);
            std::copy(first, last, temp+d);
            std::copy(m_first+d, m_last, temp+d+(last-first));
            delete[] m_first;
            m_first = temp;
            m_last = m_first+len;
            return m_first+d;
        }


        void push_back(const value_type& value) {
            resize(size()+1);
            *(m_last-1) = value;
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

