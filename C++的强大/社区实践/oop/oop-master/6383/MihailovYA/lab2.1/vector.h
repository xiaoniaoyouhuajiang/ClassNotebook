#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>

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

    explicit vector(size_t count = 0) : m_first((count) ? new Type[count] : nullptr), m_last((count) ? (m_first + count) : nullptr)
    {
      for(size_t i=0;i<count;i++)
          m_first[i]=0;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector(last-first)
    {
      std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(),init.end())
    {
    }

    vector(const vector& other) : m_first((other.size()) ? new Type[other.size()] : nullptr), m_last((other.size()) ? m_first + other.size() : nullptr)
    {
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

    vector(vector&& other) : vector()
    {
        if(this != &other) swap(other);
    }

    ~vector()
    {
        Destroy();      
    }
      
     void resize(size_t count)
    {
      vector buf(count);
	  std::move(m_first, (count > size()) ? m_last : m_first + count, buf.m_first);
	  swap(buf);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      size_t new_pos = pos - m_first;
      std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1, m_last);
	  resize(size()-1);
	  return m_first + new_pos;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      size_t new_pos = last - first;
      iterator next=const_cast<iterator>(first);  
     	while(new_pos--)
            next=erase(next);
		return next;
    }  
      
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {      
        size_t buf = pos - m_first;
		resize(size() + 1);
		iterator new_pos = const_cast<iterator>(m_first+buf);
		std::rotate(new_pos, m_last - 1, m_last);
		*new_pos = value;
		return new_pos;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      size_t next = last - first;
	  iterator new_pos = const_cast<iterator>(pos);
	  while(next)
	  new_pos = insert(new_pos, *(first+(--next)));
	  return new_pos;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      insert(end(),value);
    }
    
    vector& operator=(const vector& other)
    {
      if(this!= &other) vector(other).swap(*this);
        return *this;
    }

    vector& operator=(vector&& other)
    {
      if(this!= &other) swap(other);
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      vector<Type>(first,last).swap(*this);
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
		for (size_t i = 0; i < size(); i++)
			std::cout << m_first[i] << " ";
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
      void Destroy(){
          delete[] m_first;
      }
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik
