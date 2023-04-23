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

    explicit vector(size_t count = 0) {
        m_first = new Type[count];
        m_last  = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) {
        m_first = new Type[last - first];
        std::copy(first, last, m_first);
        m_last = m_first + (last - first);
    }

    vector(std::initializer_list<Type> init) {
        m_first = new Type[init.size()];
        std::copy(init.begin(), init.end(), m_first);
        m_last = m_first + init.size();
    }

    vector(const vector& other) {
        m_first = new Type[other.size()];
        std::copy(other.begin(), other.end(), m_first);
        m_last = m_first + other.size();
    }

    vector(vector&& other) {
        m_first = other.begin();
        m_last  = other.end();
        other.m_first = nullptr;
        other.m_last  = nullptr;
    }
      
    vector &operator=(const vector &other) {
        delete[]m_first;
        m_first = new Type[other.size()];
        std::copy(other.begin(), other.end(), m_first);
        m_last = m_first + other.size();
    }
      
    vector &operator=(vector &&other) {
        if (this->size()) {
            delete[]m_first;    
        }
        
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
    }
      
    void assign(size_t count, const vector &value) {
        if (this->size()) {
            delete[]m_first;
        }
        
        m_first = new Type[count];
        
        for (int i = 0; i < count; i++) {
            *(m_first + i) = value;
        }
    }
      
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        if (this->size()) {
            delete[]m_first;
        }
        
        m_first = new Type[last - first];
        std::copy(first, last, m_first);
        m_last = m_first + (last - first);
    }
      
    void resize(size_t count, Type value = Type()) {
        iterator new_first = new Type[count];
        std::copy(m_first, m_first + std::min(count, this->size()), new_first);
        delete[]m_first;
        
        if (this->size() <= count) { 
            for (int i = this->size(); i < count; i++) {
                *(new_first + i) = value;    
            }
        }
        
        m_first = new_first;
        m_last = m_first + count;
    }
      
    iterator erase(iterator pos) {
        size_t sz = this->size() - 1;
        size_t next_num = pos - m_first;
        iterator new_first = new Type[sz];
        std::copy(m_first, pos, new_first);
        std::copy(pos + 1, m_last, new_first + next_num);
        delete[]m_first;
        
        m_first = new_first;
        m_last = m_first + sz;
        
        return m_first + next_num;
    }
      
    iterator erase(iterator first, iterator last) {
        size_t sz = this->size() - (last - first);
        size_t next_num = first - m_first;
        iterator new_first = new Type[sz];
        std::copy(m_first, first, new_first);
        std::copy(last, m_last, new_first + next_num);
        delete[]m_first;
        
        m_first = new_first;
        m_last = m_first + sz;
        
        return m_first + next_num;
    }
      
    void push_back(const Type &value) {
        size_t sz = this->size() + 1;
        iterator new_first = new Type[sz];
        std::copy(m_first, m_last, new_first);
        *(new_first + sz - 1) = value;
        delete[]m_first;
        
        m_first = new_first;
        m_last = m_first + sz;
    }
      
    iterator insert(iterator pos, const Type &value) {
        size_t sz = this->size() + 1;
        size_t next = pos - m_first;
        
        iterator new_first = new Type[sz];
        std::copy(m_first, pos, new_first);
        *(new_first + next) = value;
        std::copy(pos, m_last, new_first + (next + 1));
        delete[]m_first;
        
        m_first = new_first;
        m_last = m_first + sz;
        
        return m_first + next;
    }
      
    iterator insert(iterator pos, size_t count, const Type &value) {
        size_t sz = this->size() + count;
        size_t next = pos - m_first;
        
        iterator new_first = new Type[sz];
        std::copy(m_first, pos, new_first);
        
        for (int i = 0; i < count; i++) {
            *(new_first + next + i) = value;    
        }
        
        std::copy(pos, m_last, new_first + (next + count));
        delete[]m_first;
        
        m_first = new_first;
        m_last = m_first + sz;
        
        return m_first + next;
    }
      
    template <class InputIterator>
    iterator insert(iterator pos, InputIterator first, InputIterator last) {
        size_t count = last - first;
        size_t sz = this->size() + count;
        size_t next = pos - m_first;
        
        iterator new_first = new Type[sz];
        std::copy(m_first, pos, new_first);
        std::copy(first, last, new_first + next);
        std::copy(pos, m_last, new_first + (next + count));
        delete[]m_first;
        
        m_first = new_first;
        m_last = m_first + sz;
        
        return m_first + next;
    }

    ~vector() {
      delete[]m_first;
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
