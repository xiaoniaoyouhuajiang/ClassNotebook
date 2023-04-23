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
                for (size_t i = 0; i < count; i++)
                    m_first[i] = 0;
            }
            else{
                m_first = nullptr;
                m_last = nullptr;
            }
        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            m_first = new Type[last-first];
            m_last = m_first + (last-first);
            std::copy(first, last, m_first);
        }

        vector(std::initializer_list<Type> init): vector(init.begin(), init.end())
        {
        }

        vector(const vector& other)
        {
            if (other.size() == 0){
                m_first = nullptr;
                m_last = nullptr;
            }
            else{
                m_first = new Type[other.size()];
                m_last = m_first+other.size();
                std::copy(other.m_first, other.m_last, m_first);
            }
        }

        static void swap(vector& that, vector& other)
        {
            std::swap(that.m_first, other.m_first);
            std::swap(that.m_last, other.m_last);
        }

        vector(vector&& other): vector()
        {
            if (this != &other){
                swap(*this,other);
            }
        }

        ~vector()
        {
            delete[] m_first;
        }

        vector& operator=(const vector& other)
        {
            if (this != &other){
                vector temp(other);
                swap(*this, temp);
            }
            return *this;
        }

        vector& operator=(vector&& other)
        {
            if (this != &other){
                swap(*this, other);
            }
            return *this;
        }

        // assign method
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            vector temp(first,last);
            swap(*this, temp);
        }

        void resize(size_t count)
        {
            vector temp(count);
            std::copy(m_first, (count > size()) ? m_last : m_first + count, temp.m_first);
            swap(*this, temp);
        }

        //erase methods
        iterator erase(const_iterator pos)
        {
            size_t temp = pos - m_first;
            std::rotate(m_first + temp, m_first + temp + 1, m_last);
            resize(size()-1);
            return m_first + temp;
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            size_t temp = first - m_first;
            size_t tem1 = last - m_first;
            std::rotate(m_first + temp, m_first + tem1, m_last);
            resize(size()-tem1 + temp);
            return m_first + temp;
        }

        iterator insert(const_iterator pos, const Type& value)
        {
            size_t newpos = pos - m_first;
            vector temp(newpos);          
            std::copy(m_first, m_first+newpos, temp.m_first);
            temp.push_back(value);
            temp.resize(size()+1);
            std::copy(m_first+newpos, m_last, temp.m_first+1);
            *this = std::move(temp);
            return m_first+newpos;    
        }

        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            size_t newpos = pos - m_first;
            size_t newsize = last - first;
            vector temp(size() + newsize);
            std::copy(m_first, m_first+newpos, temp.m_first);
            std::copy(first, last, temp.m_first + newpos);
            std::copy(m_first+newpos, m_last, temp.m_first + newpos + newsize);
            *this = std::move(temp);
            return m_first+newpos;  
        }

        //push_back methods
        void push_back(const value_type& value)
        {
            resize(size()+1);
            *(m_last-1)=value;
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