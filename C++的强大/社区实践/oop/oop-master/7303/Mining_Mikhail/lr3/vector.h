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
        if (count > 0){ 
            m_first = new Type[count];
            m_last = m_first + count;
        }
        else {  
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        size_t size = last - first;
        if (size > 0){ 
            m_first = new Type[size];
            m_last = m_first + size;
            std::copy(first, last, this->m_first);
        }
        else{ 
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    vector(std::initializer_list<Type> init)
    {
        if (init.size()){ 
            m_first = new Type[init.size()];
            m_last = m_first + init.size();
            std::copy(init.begin(), init.end(), this->m_first);
        }
        else{
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    vector(const vector& other)
    {
        if (other.size()){
            this->m_first = new Type[other.size()];
            this->m_last  = this->m_first + other.size();
            std::copy(other.m_first, other.m_last, this->m_first);
        }
        else{ 
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    vector(vector&& other): m_last(nullptr), m_first(nullptr)
    {
         std::swap(m_first, other.m_first);
         std::swap(m_last, other.m_last);
    }

    ~vector()
    {
        if (m_first != nullptr){ 
            delete [] m_first;

            m_first = nullptr;
            m_last = nullptr;
        }
    }
      
    //assignment operators
    vector& operator=(const vector& other)
    {
      if (m_first != nullptr) delete [] m_first;
        
        if (other.size()) {
            this->m_first = new Type[ other.size() ];
            this->m_last  = this->m_first + other.size();
            
            std::copy(other.m_first, other.m_last, this->m_first);
        }
        else { 
            m_first = nullptr;
            m_last = nullptr;
        }
        return *this;
    }

    vector& operator=(vector&& other)
    {
        if (m_first != nullptr) delete [] m_first;
        m_first = nullptr;
        m_last = nullptr;
        
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        return *this;
    }
    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        if (m_first != nullptr) delete [] m_first;
        
        size_t size = last- first;
        this->m_first = new Type[ size ];
        this->m_last  = m_first + size;
        std::copy(first, last, this->m_first);
    }
      
    void resize(size_t count)
    {
      if (count == 0) {
          delete [] m_first;
          
          m_first = nullptr;
          m_last = nullptr;
          
          return;
        }
        if (count == size()) return;
        
        Type* buffer = new Type[count];
        
        if (count > size()) {
            std::copy(m_first, m_last, buffer);
        } else {
            std::copy(m_first, m_first + count, buffer);
        }

        delete[] m_first;
        m_first = buffer;
        m_last = m_first + count;
    }
    
    //push_back methods
    void push_back(const value_type& value)
    {
        resize(size() + 1);
		*(m_last - 1) = value;
    }
      
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        size_t index = 0;
		iterator current = m_first;

		while (current != pos) {
			current++;
			index++;
		}

		push_back(value);
		std::rotate(m_first + index, m_last - 1, m_last);

		return m_first + index;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t index = 0;
		iterator current = m_first;

		while (current != pos) {
			current++;
			index++;
		}

		difference_type size = last - first;

		for (size_t j = 0; j < size; ++j) {

			push_back(*first);
			first++;
		}

		std::rotate(m_first + index, m_last - size, m_last);

		return m_first + index;
    }
    
    //erase methods
    iterator erase(const_iterator pos)
    {
        difference_type delta = pos - m_first;
        
        std::rotate(m_first + delta, m_first + delta + 1, m_last);
        resize(size() - 1);
        return (m_first + delta);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        difference_type delta = first - m_first;
        difference_type erase_size = last - first;
        
        std::rotate(m_first + delta, m_first + delta + erase_size, m_last);
        resize(size() - erase_size);
        return m_first + delta;
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
