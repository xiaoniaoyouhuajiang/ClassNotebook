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
        if(all_mem(count))
        {
            m_last += count;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        size_t dis = std::distance(first, last);
        if(all_mem(dis))
        {
            m_last += dis;
            std::copy(first, last, m_first);
        }
    }

    vector(std::initializer_list<Type> init)
    {
        if(all_mem(init.size()))
        {
            m_last += init.size();
            std::copy(init.begin(), init.end(), m_first);
        }
    }

    vector(const vector& other)
    {
        if(all_mem(other.size()))
        {
            m_last += other.size();
            std::copy(other.begin(), other.end(), m_first);
        }
    }

    vector(vector&& other) : m_first(), m_last()
    {
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
    }

    ~vector()
    {
        delete [] m_first;
        m_first = m_last = iterator();
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
        if(m_first == other.m_first)
            return *this;
        if(m_first != m_last)
        {
            delete [] m_first;
            m_last = m_first;
        }
        if(all_mem(other.size()))
        {
            m_last += other.size();
            std::copy(other.begin(), other.end(), m_first);
        }       
        return *this;
    }

    vector& operator=(vector&& other)
    {
	if(m_first == other.m_first)
	    return *this;
        if(m_first != m_last)
        {
            delete [] m_first;
            m_last = m_first;
        }
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        if(m_first != m_last)
        {
            delete [] m_first;
            m_last = m_first;
        }
        size_t size = std::distance(first, last);
        if(all_mem(size))
        {
            m_last += size;
            std::copy(first, last, m_first);
        }
    }

    // resize methods
    void resize(size_t count)
    {
        size_t old_size = size();
        if(count > old_size)
        {
            iterator new_vec = new Type[count];
            std::copy(m_first, m_last, new_vec);
            if(m_first != m_last)
            {
                delete [] m_first;
            }
            m_first = new_vec;
            m_last = new_vec + count;
        }
        else
        {
            m_last -= (old_size - count); 
        }
    }

    
    //erase methods
    iterator erase(const_iterator pos)
    {
        iterator p = iterator(pos);
        std::rotate(p, p + 1, m_last);
        resize(size() - 1);
        return p;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        difference_type dist = std::distance(first, last);
        std::rotate(iterator(first), iterator(last), m_last);
        resize(size() - dist);
        return iterator(first);
        
    }
    //insert methods
	iterator insert(const_iterator pos, const Type& value)
	{
		difference_type dist = std::distance(m_first, iterator(pos));
		resize(size() + 1);
		iterator new_pos = m_first + dist;
		std::rotate(new_pos, m_last - 1, m_last);
		*new_pos = value;
		return new_pos;
	}
    
	template <typename InputIterator>
	iterator insert(const_iterator pos, InputIterator first, InputIterator last)
	{
		difference_type dist = std::distance(m_first, iterator(pos));
		difference_type length = last - first;
		resize(size() + length);
		iterator new_pos = m_first + dist;
		std::rotate(new_pos, m_last - length, m_last);
		std::copy(first, last, new_pos);
		return new_pos;
	}

	//push_back methods
	void push_back(const value_type& value)
	{
		resize(size() + 1);
		*(m_last - 1) = value;
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
     bool all_mem(size_t N)
    {
        m_first = m_last = iterator();
        if(!N) return (false);
        m_first = new Type[N];
        m_last = m_first;
        return (true);
    }
    
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
