#include <assert.h>
#include <algorithm>
#include <cstddef>
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
        
        explicit vector(size_t count = 0)
        {
            if(count == 0 && false){
                m_first = nullptr;
                m_last = nullptr;
                return;
            }
            m_first = new Type[count];
            m_last = m_first + count;
        }
        
        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            size_t size =last - first;
            m_first = new Type[size];
            for(int i=0;i<size;++i){
                m_first[i]=*(first+i);
            }
            m_last = m_first + size;
        }
        
        vector(std::initializer_list<Type> init)
        {
            m_first = new Type[init.size()];
            iterator it = m_first;
            for(Type *i = (Type*)init.begin() ; i != init.end() ; ++i){
                *it = *i;
                it++;
            }
            m_last = m_first + init.size();
        }
        
        vector(const vector& other)
        {
            m_first = new Type[other.size()];
            for(int i=0;i<other.size();++i){
                *(m_first +i)=other.at(i);
            }
            m_last = m_first + other.size();
        }
        
        vector(vector&& other)
        {
            m_first = other.begin();
            m_last = other.end();
            other.m_first=nullptr;
            other.m_last=nullptr;
        }
        
        ~vector()
        {
            if(size() > 0) delete[] m_first;
            m_first=nullptr;
            m_last=nullptr;
        }
        
        iterator insert(const_iterator pos, const Type& value)
        {
            vector tmp(size() + 1);
            iterator iter_to = tmp.m_first;
            for(iterator it = m_first ; it != pos ; ++it){
                *iter_to = *it;
                iter_to++;
            }
            *iter_to = value;
            iterator finded = iter_to;
            iter_to++;
            for(iterator it = (iterator)pos ; it != m_last ; ++it){
                *iter_to = *it;
                iter_to++;
            }
            swap(tmp,*this);
            return finded;
        }
        
        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            if(first == last) return (iterator)pos;
            size_t position = pos - m_first;
            vector tmp(size() + (last - first));
            std::copy(m_first,(iterator)pos,tmp.m_first);
            std::copy(first, last, tmp.m_first + position);
            std::copy((iterator)pos,m_last, tmp.m_first + position + (last - first));
            swap(tmp,*this);
            return m_first + position;
        }
        
        void push_back(const value_type& value){
            vector tmp(size() + 1);
            std::copy(m_first,m_last,tmp.m_first);
            *(tmp.m_last - 1) = value;
            swap(tmp,*this);
        }
        
        void resize(size_t count) {
            if(size() == count) return;
            if(size() < count){
                vector tmp(count);
                std::copy(m_first, m_last,tmp.m_first);
                swap(tmp,*this);
                return;
            }
            else{
                vector tmp(m_first, m_first + count);
                swap(tmp,*this);
            }
        }
        
        iterator erase(const_iterator pos){
            size_t offset = pos - m_first;
            std::rotate(m_first + offset, m_first + offset + 1, m_last);
            resize(size() - 1);
            return m_first + offset;
        }
        iterator erase(const_iterator first, const_iterator last){
            vector tmp(size() - (last - first));
            iterator cur = tmp.begin();
            for(iterator it = m_first ; it < first ; ++it){
                *cur = *it;
                cur++;
            }
            iterator finded = cur;
            for(iterator it = (iterator)(last) ; it < m_last ; ++it){
                *cur = *it;
                cur++;
            }
            swap(tmp,*this);
            return finded;
        }
        
        vector& operator=(const vector& other)
        {
            if(&other == this) return *this;
            if(m_first != nullptr) delete[] m_first;
            m_first = new Type[other.size()];
            for(int i = 0 ; i < other.size() ; ++i){
                *(m_first + i) = other[i];
            }
            m_last = m_first + other.size();
            return *this;
        }
        
        vector& operator=(vector&& other)
        {
            if(m_first != nullptr) delete[] m_first;
            m_first = other.m_first;
            m_last = other.m_last;
            other.m_first = nullptr;
            other.m_last = nullptr;
            
        }
        
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            vector tmp(first,last);
            std::swap(m_first,tmp.m_first);
            std::swap(m_last,tmp.m_last);
        }
        
        reference at(size_t pos)
        {
            return checkIndexAndGet(pos);
        }
        
        const_reference at(size_t pos) const
        {
            return checkIndexAndGet(pos);
        }
        
        reference operator[](size_t pos)
        {
            return m_first[pos];
        }
        
        const_reference operator[](size_t pos) const
        {
            return m_first[pos];
        }
        
        iterator begin()
        {
            return m_first;
        }
        
        const_iterator begin() const
        {
            return m_first;
        }
        
        iterator end()
        {
            return m_last;
        }
        
        const_iterator end() const
        {
            return m_last;
        }
        
        size_t size() const
        {
            return m_last - m_first;
        }
        
        bool empty() const
        {
            return m_first == m_last;
        }
        
    private:
        void swap(vector& tmp1, vector& tmp2){
            std::swap(tmp1.m_first,tmp2.m_first);
            std::swap(tmp2.m_last,tmp1.m_last);
        }
        reference checkIndexAndGet(size_t pos) const
        {
            if (pos >= size())
            {
                throw std::out_of_range("out of range");
            }
            
            return m_first[pos];
        }
        
    private:
        iterator m_first;
        iterator m_last;
    };
}
