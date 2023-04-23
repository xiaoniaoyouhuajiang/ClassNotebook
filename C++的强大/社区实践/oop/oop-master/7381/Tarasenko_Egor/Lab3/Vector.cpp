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
      // implement this
        m_first = new value_type[count]();
        m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
      // implement this
        size_t count = std::distance(first, last);
        m_first = new value_type[count]();
        m_last = m_first + count;
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
    {
      // implement this
    }

    vector(const vector& other) : vector(other.begin(), other.end())
    {
      // implement this
    }

    vector(vector&& other)
    {
      // implement this
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector()
    {
      // implement this
        delete[] m_first;
    }

	//assignment operators
    vector& operator=(const vector& other)
    {
      // implement this
        if(other.size() > 0){
            delete[] m_first;
            m_first = new value_type[other.size()];
            m_last = m_first + other.size();
            std::copy(other.begin(), other.end(), m_first);
        }
        return *this;
    }

    vector& operator=(vector&& other)
    {
      // implement this
        if(this != &other) {
            delete[] m_first;
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = nullptr;
            other.m_last = nullptr;
        }
    }
	
	// assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      // implement this
        delete[] m_first;
        if(first != last) {
            size_t count = std::distance(first, last);
            m_first = new value_type[count];
            m_last = m_first + count;
            std::copy(first, last, m_first);
        }
        else {
            m_first = m_last = nullptr;
        }
    }
	
	// resize methods
    void resize(size_t count)
    {
      // implement this
        if (count > 0) {
            if (count == size()) return;
            iterator tmp = new value_type[count]();
            if (count > size()) std::copy(m_first, m_last, tmp);
            if (count < size()) std::copy(m_first, m_first + count, tmp);
            delete[] m_first;
                m_first = tmp;
                m_last = m_first + count;
        }
        else {
            delete[] m_first;
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      // implement this
        difference_type difference = pos - m_first;
        std::rotate(m_first + difference, m_first + difference + 1, m_last);
        resize(m_last - m_first - 1);
        return (m_first + difference);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      // implement this
        difference_type difference = first - m_first;
        difference_type erase_zone = last - first;
        std::rotate(m_first + difference, m_first + difference + erase_zone, m_last);
        resize(m_last - m_first - erase_zone);
        return (m_first + difference);
    }
	
	//insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      // implement this
        difference_type difference = pos - m_first;
        resize(size() + 1);
        m_first[size() - 1] = value;
        std::rotate(m_first + difference, m_last - 1, m_last);
        iterator new_el = m_first + difference;
        return new_el;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      // implement this
        size_t difference = pos - m_first;
        resize(size() + (last - first));
        std::copy(first, last, m_last - (last - first));
        std::rotate(m_first + difference, m_last - (last - first), m_last);
        iterator new_el = m_first + difference;
        return new_el;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      // implement this
        resize(size() + 1);
        m_first[size() - 1] = value;
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