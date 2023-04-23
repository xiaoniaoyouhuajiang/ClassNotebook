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
        m_first = new Type[count];
        m_last = m_first + count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
      // implement this
        size_t dis = std::distance(first,last);
        m_first = new Type[dis];
        std::copy(first, last, m_first);
        m_last = m_first + dis;
        
    }

    vector(std::initializer_list<Type> init):vector(init.begin(), init.end()){}

    vector(const vector& other): vector(other.begin(), other.end()) {}

    vector(vector&& other) :m_first(other.m_first), m_last(other.m_last) {
      other.m_first = other.m_last = nullptr;
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
	
 vector& operator=(const vector& other)
    {
      // implement this
         if (this != &other){
            if (other.size()) {
                delete[] m_first;
                m_first = new value_type[other.size()];
                m_last = m_first + other.size();
                std::copy(other.begin(), other.end(), m_first);
               
        }
         }
        return *this;
        
    }

    vector& operator=(vector&& other)
    {
      // implement this
        if (this != &other){
        std::swap(m_first,other.m_first);
        std::swap(m_last,other.m_last);}
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      // implement this
       *this = vector(first,last);
    }
   void resize(size_t count)
    {
        // implement this
        vector new_vector(count);
		if (count > size())
			std::move(m_first, m_last, new_vector.m_first);
		else 
			std::move(m_first, m_first + count, new_vector.m_first);
		std::swap(m_first,new_vector.m_first);
        std::swap(m_last,new_vector.m_last);
    }

    //erase methods
  iterator erase(const_iterator pos)
		{
			iterator iter = m_first;
			difference_type size = m_last - m_first;
			size_t i = 0;

			while (iter != pos) {
				iter++;
				i++;
			}
			std::rotate(iter, iter + 1, m_last);

			resize(size - 1);
			return  m_first + i;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			difference_type  n = last - first;
			iterator iter = m_first;

			if (n == 0) 
				return iter;

			for (; iter != first; iter++);
			for (size_t i = 0; i < n; i++) {
				iter = erase(iter);
			}
			return iter;
		}   iterator insert(const_iterator pos, const Type& value)
       {
       size_t offset = pos - m_first;

       resize(size()+1);
       *(m_last-1) = value;
       std::rotate(m_first+offset, m_last-1, m_last);

       return m_first + offset;
       }
    
       template <typename InputIterator>
       iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
        size_t offset = pos - m_first; 
        resize( size() + (last-first));
        std::copy(first, last, m_last - (last-first));
        std::rotate(m_first+offset, m_last - (last-first) , m_last);
            return m_first + offset;
        }

     
    void push_back(const value_type& value)
     {
        resize(size()+1);
        *(m_last-1) = value;
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
