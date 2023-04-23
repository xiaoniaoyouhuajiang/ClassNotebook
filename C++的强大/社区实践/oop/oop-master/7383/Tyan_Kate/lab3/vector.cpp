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
        
        explicit vector(size_t count = 0)  : m_first(count ? new Type[count] : nullptr), m_last(m_first + count)
        {
        }
        
        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            if((last - first) > 0){
                m_first = new Type[last - first];
                m_last = m_first + (last - first);
                std::copy(first, last, m_first);
            }else{
                m_first = nullptr;
                m_last = nullptr;
            }// implement this
        }
        
        vector(std::initializer_list<Type> init) : m_first(new Type[init.size]), m_last(m_first + init.size())
        {
            std::copy(init.begin(), init.end(), m_first);
        }
        
        vector(const vector& other)
        {
            if(other.size() > 0){
                m_first = new Type[other.size()];
                m_last = m_first + other.size();
                std::copy(other.m_first, other.m_last, m_first);// implement this
            }else{
                m_first = nullptr;
                m_last = nullptr;
            }// implement this
        }
        
        vector(vector&& other)
        {
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = nullptr;
            other.m_last = nullptr;// implement this
        }
        
        ~vector()
        {
            delete [] m_first;// implement this
        }
        
        vector& operator=(const vector& other)
        {
            if(other.m_first == m_first)
                return * this;
            size_t count = m_last - m_first;
            Type data[count];
            std::copy(m_first, m_last, data);
            delete [] m_first;
            size_t size = other.m_last - other.m_first;
            try{
                m_first = new Type[size];
                m_last = m_first + size;
                std::copy(other.m_first, other.m_last, m_first);
            }catch(...){
                m_first = new Type[count];
                std::copy(data, data + count, m_first);
                m_last = m_first + count;
            };
            return *this;
            // implement this
        }
        
        vector& operator=(vector&& other)
        {
            if(other.m_first == m_first)
                return *this;
            delete [] m_first;
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = nullptr;
            other.m_last = nullptr;
            return *this;// implement this
        }
        
        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            delete [] m_first;
            if((last - first) > 0){
                m_first = new Type[last - first];
                m_last = m_first + (last - first);
                std::copy(first, last, m_first);
            }else{
                m_first = nullptr;
                m_last = nullptr;
            }
            // implement this
        }
        
        // resize methods
        void resize(size_t count)
        {
            if(count == m_last - m_first)
                return;
            size_t size = m_last - m_first;
            Type data[size];
            std::copy(m_first, m_last, data);
            delete [] m_first;
            m_first = new Type[count];
            m_last = m_first + count;
            if(count > size){
                std::copy(data, data + size, m_first);
            }else{
                std::copy(data, data + count, m_first);
            }// implement this
        }
        
        //erase methods
        iterator erase(const_iterator pos)
        {
            // if(m_last < pos)
            //   return pos;
            size_t size = m_last - m_first;
            size_t stop = pos - m_first;
            for(size_t i = stop; i < size - 1; i++){
                m_first[i] = m_first[i + 1];
            }
            m_last = m_first + size - 1;
            resize(size - 1);
            return m_first + stop;// implement this
        }
        
        iterator erase(const_iterator first, const_iterator last)
        {
            // if(m_last < last)
            //   return last;
            size_t size = m_last - m_first;
            size_t dif = last - first;
            // size_t lst = last - m_first;
            size_t f = first - m_first;
            
            for(size_t i = f; i < size - dif; i++){
                m_first[i] = m_first[i + dif];
            }
            resize(size - dif);
            return m_first + f;// implement this
        }
        
        //insert methods
        iterator insert(const_iterator pos, const Type& value)
        {
            size_t size = m_last - m_first;
            size_t ptr = pos - m_first;
            Type data[size];
            std::copy(m_first, m_last, data);
            delete [] m_first;
            m_first = new Type[size + 1];
            m_last = m_first + size + 1;
            std::copy(data, data + ptr, m_first);
            *(m_first+ptr) = value;
            std::copy(data + ptr, data + size, m_first + ptr + 1);
            return m_first + ptr;// implement this*/
        }
        
        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            size_t size = m_last - m_first;
            size_t dif = last - first;
            size_t ptr = pos - m_first;
            Type data[size];
            std::copy(m_first, m_last, data);
            delete [] m_first;
            m_first = new Type[size + dif];
            m_last = m_first + size + dif;
            std::copy(data, data + ptr, m_first);
            std::copy(first, last, m_first + ptr);
            std::copy(data + ptr, data + size, m_first + ptr + dif);
            return m_first + ptr;// implement this
        }
        
        //push_back methods
        void push_back(const value_type& value)
        {
            insert(m_last, value);// implement this
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
