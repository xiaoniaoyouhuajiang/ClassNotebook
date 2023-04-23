#include <vector>
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
	    // std::cout << "Called count constructor" << std::endl;
      // implement this
	 Type *tmp = new Type[count];
	 m_first = tmp;
	 m_last = tmp + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
	    // std::cout << "Called iterators constructor" << std::endl;
      // implement this
	 Type *tmp = new Type[last-first];
	 std::copy(first, last, tmp);
	 m_first = tmp;
	 m_last = m_first + (last-first);
    }

    vector(std::initializer_list<Type> init)
    {
	    // std::cout << "Called init_list constructor" << std::endl;
      // implement this
	 Type *tmp = new Type[init.size()];
	 std::copy(init.begin(), init.end(), tmp);
	 m_first = tmp;
	 m_last = tmp + init.size();
    }

    vector(const vector& other) : vector(other.begin(), other.end())
    {
	    // std::cout << "Called copy constructor" << std::endl;
      // implement this
    }

    vector(vector&& other)
    {
      // implement this
	 // std::cout << "Called move constructor" << std::endl;
	 m_first = other.m_first;
	 m_last = other.m_last;
	 other.m_first = nullptr;
	 other.m_last = nullptr;
    }

    ~vector()
    {
	 // std::cout << "Called destructor" << std::endl;
      // implement this
	 delete [] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      // implement this
	 if (&other == this) return *this;
	 // std::cout << "Called operator=" << std::endl;
	 vector tmp{other};
	 delete [] m_first;
	 m_first = tmp.m_first;
	 m_last = tmp.m_last;
	 tmp.m_first = nullptr;
	 tmp.m_last = nullptr;
	 return *this;
    }

    vector& operator=(vector&& other)
    {
      // implement this
	 if (&other == this) return *this;
	 // std::cout << "Called move operator=" << std::endl;
	 delete [] m_first;
	 m_first = other.m_first;
	 m_last = other.m_last;
	 other.m_first = nullptr;
	 other.m_last = nullptr;
	 return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      // implement this
	 vector tmp{first, last};
	 delete [] m_first;
	 m_first = tmp.m_first;
	 m_last = tmp.m_last;
	 tmp.m_first = nullptr;
	 tmp.m_last = nullptr;
    }

    // resize methods
    void resize(size_t count)
    {
      // implement this
	 Type* tmp = new Type[count];
	 delete [] m_first;
	 m_first = tmp;
	 m_last = tmp + count;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      // implement this
	 return erase(pos, pos+1);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      // implement this
      if (first == m_last) return m_last;
      // assert(first < last);
      // assert((first>=m_first) && (first < m_last));
      // assert((last<=m_last) && (last>m_first));
      size_t diff = last - first ;
      size_t tmp_size = size() - diff;
      size_t ret_pos = first - m_first;
      Type* tmp = new Type[tmp_size];
      for (size_t i = 0; i != ret_pos; ++i)
      {
        tmp[i] = this->at(i);
      }
      for (size_t i = ret_pos+diff; i != size(); ++i)
      {
        tmp[i-diff] = this->at(i);
      }

      delete [] m_first;
      m_first = tmp;
      m_last = tmp + tmp_size;
      tmp = nullptr;
      return m_first + ret_pos;
    }


    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      return insert(pos, &value, 1+&value);
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      // implement this
      size_t in_size = last - first;
      size_t int_pos = pos - m_first;
      size_t new_size = size() + in_size;
      Type* tmp = new Type[new_size];
      for (size_t i = 0; i < int_pos; ++i)
      {
        tmp[i] = this->at(i);
      }
      for (size_t i = int_pos; i < int_pos + in_size; ++i)
      {
        tmp[i] = *(first+i-int_pos);
      }
      for (size_t i = int_pos + in_size; i < new_size; ++i)
      {
        tmp[i] = this->at(i-in_size);
      }
      delete [] m_first;
      m_first = tmp;
      m_last = tmp + new_size;
      return begin() + int_pos;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      // implement this
      size_t new_size = size() + 1;
      Type* tmp = new Type[new_size];
      std::copy(m_first, m_last, tmp);
      tmp[size()] = value;
      delete [] m_first;
      m_first = tmp;
      m_last = tmp + new_size;
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
    void print()
    {
	    for (auto i : *this)
		    std::cout << i << " ";
	    std::cout << std::endl;
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
