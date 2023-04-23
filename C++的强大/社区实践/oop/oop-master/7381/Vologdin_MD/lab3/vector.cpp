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
        : m_first(count ? new Type[count] : nullptr), m_last(m_first + count)
        {}

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            int count = std::distance(first, last);
            m_first = new value_type[count];
            m_last = m_first + count;
            std::copy(first, last, m_first);
        }
    
        vector(std::initializer_list<Type> init)
        : vector(init.begin(), init.end()) 
        {}
      

        vector(const vector& other)
        : vector(other.begin(), other.end())
        {}
 

        vector(vector&& other)
        {
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = other.m_last = nullptr;
        }

        ~vector()
        {
            delete [] m_first;
        }
        //assignment operators
        vector& operator=(const vector& other)
        {
            if(this != &other)
            {
                delete[] m_first;
                m_first = new value_type[other.size()];
                m_last = m_first + other.size();
                std::copy(other.m_first, other.m_last, m_first);
            }
            return *this;
        }

        vector& operator=(vector&& other)
        {
            if(this != &other)
            {
                delete[] m_first;
                m_first=m_last=nullptr;
                std::swap(m_first,other.m_first);
                std::swap(m_last,other.m_last);
            }
            return *this;
        }

        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            if (m_first!=nullptr)
                delete [] m_first;
            m_first = new value_type[last-first];
            m_last = m_first + std::distance(first,last);
            std::copy(first, last, m_first);
        }
        // resize methods
        void resize(size_t count)
        {
            if(count == size()) 
                return;
            Type* temp = new Type[count];
            if(count > size())
                std::copy(m_first, m_last, temp);
            else
                std::copy(m_first, m_first+count, temp);
            delete[] m_first;
            m_first = temp;
            m_last = m_first+count;
        }

        //erase methods
        iterator erase(const_iterator pos)
        {
            iterator _Pos = iterator(pos);
            std::rotate(_Pos, _Pos + 1, m_last--);
            return (_Pos);
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            iterator _First = iterator(first);
            iterator _Last = iterator(last);
            std::rotate(_First, _Last, m_last);
            m_last -= std::distance(first,last);
            return (_First);
        }
        
        iterator insert(const_iterator pos, const Type& value)
        {
            size_t len = pos - m_first;
            resize(size() + 1);
            iterator newPos = m_first + len;
            std::rotate(newPos, m_last - 1, m_last);
            m_first[newPos - m_first] = value;
            return newPos;
        }
        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            size_t len = std::distance(first,last);
            iterator newPos = const_cast<iterator>(pos);
            while (len != 0)
            {
                len--;
                newPos = insert(newPos, *(first + len));
            }
            return newPos;
        }
        
        //push_back methods
        void push_back(const value_type& value)
        {
            resize(size()+1);
            *(m_last-1) = value;
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