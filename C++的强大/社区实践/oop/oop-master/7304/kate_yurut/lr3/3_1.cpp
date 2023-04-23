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
	if (count > 0)
        {
            m_first = new Type[count];
            m_last = m_first + count;
            for (size_t i = 0; i < count; i++)
                m_first[i] = 0;
        }
        else
        {
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
        :  vector(last - first)
    {
        // implement this
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init)
        :  vector(init.begin(), init.end())
    {}

    vector(const vector& other)
        :  m_first((other.size()) ? new Type[other.size()] : nullptr)
        ,  m_last((other.size()) ? m_first + other.size() : nullptr)
    {
        // implement this
	try
	{
		std::copy(other.m_first, other.m_last, m_first);	
	}
	catch(...)
	{
		delete[] m_first;
		throw;
	}
    }
      
    void swap(vector & other)
    {
	std::swap(this->m_first, other.m_first);
	std::swap(this->m_last, other.m_last);
    }

    vector(vector&& other)
        :  vector()
    {
        // implement this
        if (this != &other)
		swap(other);
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
        if (this != &other)
		vector(other).swap(*this);
        return *this;
    }

    vector& operator=(vector&& other)
    {
        // implement this
        if (this != &other)
		swap(other);
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        // implement this
        vector<Type>(first,last).swap(*this);
    }

    // resize methods
    void resize(size_t count)
    {
        // implement this
        vector buf(count);
		std::move(m_first, (count > size()) ? m_last : m_first + count, buf.m_first);
        swap(buf);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
        // implement this
        size_t new_pos = pos - m_first;
     	std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1, m_last);
		resize(size()-1);
        return m_first + new_pos;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        // implement this
        size_t new_pos = last - first;
		iterator _first = const_cast<iterator>(first);
		while(new_pos--)	
			_first = erase(_first);
        return _first;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        // implement this
        size_t buf = pos - m_first;
		resize(size() + 1);
		iterator new_pos = const_cast<iterator>(m_first + buf);
		std::rotate(new_pos, m_last - 1, m_last);
		*new_pos = value;
        return new_pos;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        // implement this
        size_t distance = last - first;
		iterator new_pos = const_cast<iterator>(pos);
		while(distance)
			new_pos = insert(new_pos, *(first+(--distance)));
        return new_pos;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        // implement this
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
