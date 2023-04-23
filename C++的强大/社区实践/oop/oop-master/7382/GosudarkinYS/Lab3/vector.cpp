#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <cstring>

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
        //std::cout << "DEFAULT constructor\n";
        m_first = new Type[count];
        m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
        : vector(last - first)
    {
        //std::cout << "ITERATOR constructor\n";
        for(size_t it=0; it<size(); it++)
            m_first[it] = first[it];
    }

    vector(std::initializer_list<Type> init)
        : vector(init.begin(), init.end())
    {
        //std::cout << "INITIALIZER LIST constructor\n";
    }

    vector(const vector& other)
        : vector(other.begin(), other.end())
    {
        //std::cout << "COPY constructor\n";
    }

    vector(vector&& other)
    {
        m_first = m_last = nullptr;

        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
    }


    ~vector()
    {
        clear();
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        clear();
        m_first = new Type[other.size()]; 
        m_last = m_first + other.size();
        
        for(size_t it=0; it<size(); it++)
            m_first[it] = other[it];

        return *this;
    }

    vector& operator=(vector&& other)
    {
        clear();
        
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        clear();
        
        m_first = new Type[last-first]; 
        m_last = m_first + (last-first);
        std::copy(first, last, m_first);
    }

    // resize methods
    void resize(size_t count)
    {
        vector tmp(*this);
        clear();
        allocate(count);
        size_t size = count > tmp.size() ? tmp.size() : count;
        for(size_t i = 0; i < size; i++)
            m_first[i] = tmp[i];
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        size_t newCount = size() - 1;
        vector tmp(newCount);
        size_t i = 0;
        size_t index = pos-m_first;
        for(; i<index; i++)
            tmp[i] = m_first[i];
        for(size_t it=index+1; it<size(); it++, i++)
            tmp[i] = m_first[it];

        clear();
        allocate(newCount);
        std::copy(tmp.begin(), tmp.end(), m_first);
        return m_first + index;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        if (first == last)
            return m_first + (last - m_first);

        size_t newCount = size() - (last - first);
        vector tmp(newCount);
        size_t i = 0;
        size_t index = first-m_first;
        for(; i<index; i++)
            tmp[i] = m_first[i];
        for(size_t it=last-m_first; it<size(); it++, i++)
            tmp[i] = m_first[it];

        clear();
        allocate(newCount);
        std::copy(tmp.begin(), tmp.end(), m_first);
        return m_first + index;
    }

    //insert methods
        iterator insert(const_iterator pos, const Type& value)
        {
            size_t newCount = size() + 1;
            vector tmp(newCount);
            size_t i = 0;
            size_t index = pos-m_first;
            for(; i<index; i++)
                tmp[i] = m_first[i];
            tmp[i] = value; i++;
            for(size_t it=index+1; it<size(); it++, i++)
                tmp[i] = m_first[it];
    
            clear();
            allocate(newCount);
            std::copy(tmp.begin(), tmp.end(), m_first);
            return m_first + index;
        }
    
        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            if (first == last)
                return m_first + (pos - m_first);
    
            size_t addiditional = last - first;
            size_t newCount = size() + addiditional;
            vector tmp(newCount);
            size_t index = pos - m_first;
    
            std::copy(m_first, m_first+index, tmp.begin());
            std::copy(first, last, tmp.begin() + index);
            std::copy(m_first+index, m_last, tmp.begin() + addiditional + index);
    
            clear();
            allocate(newCount);
            std::copy(tmp.begin(), tmp.end(), m_first);
            return m_first + index;
        }
    
        //push_back methods
        void push_back(const value_type& value)
        {
            insert(m_last,value);
        }

    void print()
    {
        for(int i=0; i<size(); i++)
            std::cout << m_first[i] << ", ";
        std::cout << "\n";
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

    void clear()
    {
        delete[] m_first;
        m_first = m_last = nullptr;
    }

    void allocate(size_t count)
    {
        m_first = new Type[count];
        m_last = m_first + (count);
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
    stepik::vector<int> a(3);
    a[0] = 4;
    a[1] = 5;
    a[2] = 1;
    std::cout << "arr: " << a[0] << ", " << a[1] << ", " << a[2] << "\n";
    std::cout << "_____________________________________________________\n";

    stepik::vector<int> b(a.begin(), a.end());
    std::cout << "arr: " << b[0] << ", " << b[1] << ", " << b[2] << "\n";
    std::cout << "_____________________________________________________\n";

    stepik::vector<int> c({9,3,4,6,7,4,1});
    c.print();
    std::cout << "iter: " << *c.insert(c.begin(), a.begin()+0, a.begin()+2) << "\n";
    c.print();

    return 0;
}
