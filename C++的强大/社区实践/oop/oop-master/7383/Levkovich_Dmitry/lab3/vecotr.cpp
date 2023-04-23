#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
using namespace std;
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
          m_last =m_first+count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):vector (last - first)
    {

        copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init):vector(init.begin(), init.end())
    {

    }

    vector& operator=(const vector& other){
                size_t new_size = other.size();
                if (m_first!=nullptr){
                    delete[] m_first;
                }
                if(other.size()>0){
                    m_first = new Type[new_size];
                    m_last = m_first + new_size;
                    copy(other.begin(), other.end(), m_first);
                }
                else {
                    m_first = m_last = nullptr;
                }
                return *this;
        }

        vector& operator=(vector&& other)
        {
            if(m_first!=nullptr)
            delete[] m_first;
            m_first = other.begin();
            m_last = other.end();
            other.m_first = nullptr;
            other.m_last = nullptr;
        }

        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last){
            delete [] m_first;
            m_first = new Type[last - first];
            m_last = m_first +(last - first);
            copy(first, last, m_first);
        }

    vector(const vector& other){
        if (other.size() == 0){
            m_first = nullptr;
            m_last = nullptr;
        }else{
        m_first = new Type [other.size()];
        m_last = &(m_first[other.size()]);
        copy(other.m_first,other.m_last,m_first);
        }
    }

    vector(vector&& other){
        m_first = other.begin();
        m_last = other.end();
        other.m_first = other.m_last = nullptr;
    }

    void resize(size_t count)
    {
      vector tmp(count);
      std::copy(m_first, (count > size()) ? m_last : m_first + count, tmp.m_first);
      swap(this->m_first, tmp.m_first);
      swap(this->m_last, tmp.m_last);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        size_t new_pos = pos - m_first;
        rotate(new_pos+m_first, new_pos+m_first+1, m_last);
        resize(size()-1);
        return new_pos+m_first;

    }

    iterator erase(const_iterator first, const_iterator last)
    {
      iterator x = const_cast<iterator>(first);
      size_t i = (last - first);
      while(i--)
          x = erase(x);
      return x;
    }
    iterator insert(const_iterator pos, const Type& value)
    {
      size_t new_pos = pos-m_first;
      resize( size()+1);
      *(m_last-1) = value;
      std::rotate(m_first+new_pos, m_last-1, m_last);
      return m_first+new_pos;
    }
    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      size_t size_in = last-first;
      iterator new_pos = const_cast<iterator>(pos);
      while(size_in--){
          new_pos = insert(new_pos, *(first+size_in));
      }
      return new_pos;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      insert(end(), value);
    }

    ~vector()
    {
      delete[] m_first;
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
int main()
{
    vector<int> a;
    return 0;
}
