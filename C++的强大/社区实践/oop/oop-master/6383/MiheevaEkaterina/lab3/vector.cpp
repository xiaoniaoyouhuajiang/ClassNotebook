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
	 m_first = new Type [count];
      m_last = &(m_first[count]);
      for(int i=0; i<size(); i++)
        m_first[i]=0;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector(last - first)
    {
		std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
    {
    }

    vector(const vector& other) 
    {
		m_first = new Type [other.size()];
        m_last = &(m_first[other.size()]);
        std::copy(other.m_first,other.m_last,m_first);
		
    }
	
	void swap(vector & other)
	{
		std::swap(this->m_first, other.m_first);
		std::swap(this->m_last, other.m_last);
	}
	  
    vector(vector&& other) 
    {
       
      	 m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = nullptr;
        other.m_last = nullptr;
        other.p = new int(1);
    }

    ~vector()
    {
     	delete[] m_first;
    }
      
    // resize methods
    void resize(size_t count)
    {
         vector tmp(count);
        if (count>(m_last-m_first))
        std::copy(m_first,m_last,tmp.m_first); 
        else std::copy(m_first,m_first+count,tmp.m_first);
        delete [] m_first;
        m_first = new Type[count];
        m_last = m_first+count;
        std::copy(tmp.m_first,tmp.m_last,m_first); 
    }
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {    
          size_t d = pos - m_first;
          resize(size()+1);
          iterator posn = m_first + d;
          std::rotate(posn,m_last-1,m_last);
          size_t tmp = posn-m_first;
          m_first[tmp] = value;
         return posn;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      int d = (last - first);
      iterator posn = const_cast<iterator>(pos);
       while(d>0){
           d--;
           posn = insert(posn,*(first+d));
            
       }
        return posn;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      insert(end(),value);
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
