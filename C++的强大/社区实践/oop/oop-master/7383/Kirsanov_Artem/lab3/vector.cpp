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

    explicit vector(size_t count = 0)
    {
          m_first = new value_type[count];
          m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
        : vector(last - first)
    {
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init)
        : vector(init.begin(), init.end())
    {

    }

    vector(const vector& other)
    {
        if(other.empty()){
            m_first = nullptr;
            m_last = nullptr;
        }
        else{
            m_first = new value_type[other.size()];
            m_last = m_first + other.size();
            std :: copy(other.begin(), other.end(), m_first);
        }
    }

    vector(vector&& other)
        : m_first(other.begin()), m_last(other.end())
    {
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector()
    {
        delete [] m_first;
        m_first = m_last = nullptr;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        if(other.size() != 0){
            iterator tmp = new value_type[other.size()];
            std :: copy(other.begin(), other.end, tmp);

            if (m_first!=nullptr){
                delete[] m_first;
            }

            m_first = tmp;
            m_last = tmp + other.size();
        }
        else{
            m_first = m_last = nullptr;
        }

        return *this;
    }

    vector& operator=(vector&& other)
    {
        if(m_first != nullptr)
            delete [] m_first;
        m_first = other.begin();
        m_last = other.end();
        other.m_last = other.m_first = nullptr;
      // implement this
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      // implement this
        iterator tmp = new value_type[last - first];
        std :: copy(first, last, tmp);
        delete [] m_first;
        m_first = tmp;
        m_last = m_first + last - first;
    }

    // resize methods
    void resize(size_t count)
    {
        vector<value_type> tmp(count);
        std :: copy(begin(), (size() > count) ? begin() + count : end(), tmp.begin());
        std :: swap(m_first, tmp.m_first);
        std :: swap(m_last, tmp.m_last);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        std :: rotate(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1, end());
        end()--;
        return const_cast<iterator>(pos);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        vector<value_type> :: iterator it = const_cast<iterator>(last);
        while (it != const_cast<iterator>(first)){
            it--;
           it = erase(it);
        }
        return it;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t leng = pos - begin();
        resize(size() + 1);
        *(end() - 1) = value;
        std::rotate(begin() + leng, end() - 1, end() );
        return begin() + leng;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t leng = last-first;
        iterator posi = const_cast<iterator>(pos);
        while(leng--){
            posi = insert(posi, *(first+leng));
        }
        return posi;
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

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik
