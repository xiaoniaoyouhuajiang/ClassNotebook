#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <cstring>

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
            if( count >= 0 )
            {
                m_first = new Type[count];
                m_last = m_first + count;
            }
        }
        
        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            unsigned int count = last - first;
            m_first = new Type[count];
            for(int i = 0; i < count; first++, i++ )
            {
                m_first[i] = *first;
            }
            m_last = m_first + count;
        }
        
        vector(std::initializer_list<Type> init)
        {
            m_first = new Type[init.size()];
            int i = 0;
            for( auto item : init )
                m_first[i++] = item;
            m_last = m_first + init.size();
        }
        
        vector(const vector& other)
        {
            unsigned int count = other.size();
            m_first = new Type[count];
            for(int i = 0; i < count; i++ )
            {
                m_first[i] = other[i];
            }
            m_last = m_first + count;
        }
        
        vector(vector&& other) : vector()
        {
            std::swap((*this).m_first, other.m_first);
            std::swap((*this).m_last, other.m_last);
        }
        
        ~vector()
        {
            delete [] m_first;
        }
        
        //insert methods
        iterator insert(const_iterator pos, const Type& value)
        {
            int count = size() + 1;
            Type* buffer = new Type[count];
            iterator itr = &m_first[pos-m_first];
            iterator itr2 = std::copy(m_first, itr, buffer);
            std::copy(itr, m_last, itr2+1);
            *(itr2) = value;
            delete[] m_first;
            m_first = new Type[count];
            std::copy(buffer, buffer+count, m_first);
            delete[] buffer;
            m_last = m_first + count;
            
            return &m_first[pos-m_first];
        }
        
        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            vector buffer(size()+(last-first));
            size_t posCount = (pos-begin());
            std::copy(const_iterator(begin()), pos, buffer.begin());
            std::copy(first, last, buffer.begin()+posCount);
            if (pos+1 < end())
                std::copy(pos, const_iterator(end()), buffer.begin()+posCount+(last-first));
            std::swap(buffer.m_first, (*this).m_first);
            std::swap(buffer.m_last, (*this).m_last);
            return begin()+posCount;
        }
        
        //push_back methods
        void push_back(const value_type& value)
        {
            vector<Type> buffer = *this;
            delete [] m_first;
            m_first = new Type[buffer.size() + 1];
            m_last = m_first + buffer.size() + 1;
            std::copy(buffer.begin(), buffer.end(), m_first);
            m_first[buffer.size()] = value;
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
