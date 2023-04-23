
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
        {  if (count>0)
        { m_first=new Type[count];
            m_last=m_first+count;}
        else  m_first=m_last=nullptr;
        }
        
        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            if((last-first)>0)
            { m_first=new Type[last-first];
                m_last=m_first+(last-first);
                std::copy(first,last,this->m_first);}
            else m_first= m_last=nullptr;
        }
        
        vector(std::initializer_list<Type> init)
        {
            if((init.size())>0)
            { m_first=new Type[init.size()];
                m_last=m_first+init.size();
                std::copy(init.begin(),init.end(),this->m_first);}
            else m_first=m_last=nullptr;
        }
        
        vector(const vector& other)
        {
            if (other.size()>0){
                this->m_first=new Type[other.size()];
                this->m_last=this->m_first+other.size();
                std::copy(other.m_first,other.m_last,this->m_first);}
            else m_first=m_last=nullptr;
        }
        
        vector(vector&& other):m_last(nullptr),m_first(nullptr)
        {
            std::swap(m_first,other.m_first);
            std::swap(m_last,other.m_last);
        }
        
        ~vector()
        {
            if( m_first!=nullptr)
            { delete [] m_first;
                m_first=m_last=nullptr;}
        }
        
        
        //insert methods
        iterator insert(const_iterator pos, const Type& value)
        {iterator Pos=iterator(pos);
            size_t sz=size();
            size_t count = std::distance(m_first,Pos);
            Pos=m_first+count;
            iterator new_arr=new Type[size()+1];
            iterator Pos1=new_arr;
            Pos1=Pos1+count;
            if (Pos!=m_first)
                std::copy(m_first,Pos,new_arr);
            *Pos1=value;
            std::copy(Pos,m_last,Pos1+1);
            delete [] this->m_first;
            this->m_first=nullptr;
            std::swap(m_first,new_arr);
            m_last=m_first+sz+1;
            return m_first+count;
        }
        
        
        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {  size_t sz=size();
            iterator Pos = iterator(pos);
            iterator First = iterator(first);
            iterator Last = iterator(last);
            size_t count1 = std::distance(First,Last);
            size_t count2 = std::distance(m_first,Pos);
            
            Pos=m_first+count2;
            iterator new_arr=new Type[size()+count1];
            iterator Pos1=new_arr;
            Pos1=Pos1+count2;
            if (Pos!=m_first)
                std::copy(m_first,Pos,new_arr);
            std::copy(First,Last,Pos1);
            std::copy(Pos,m_last,Pos1+count1);
            delete [] this->m_first;
            this->m_first=nullptr;
            std::swap(m_first,new_arr);
            m_last=m_first+sz+count1;
            return m_first+count2;
        }
        
        //push_back methods
        void push_back(const value_type& value)
        {resize(size()+1);
        *(m_last - 1)= value;
        }
        
        void resize(size_t count)
        {
            if( count>size()){
                iterator new_arr=new Type[count];
                std::copy(this->m_first,this->m_last,new_arr);
                delete [] this->m_first;
                this->m_first=nullptr;
                std::swap(m_first,new_arr);
                m_last=m_first+count;}
            
            if( count<size()){
                iterator new_arr=new Type[count];
                m_last=m_first+count;
                std::copy(this->m_first,this->m_last,new_arr);
                delete [] this->m_first;
                this->m_first=nullptr;
                std::swap(m_first,new_arr);
                m_last=m_first+count;}
        }
        iterator erase(const_iterator pos)
        {  iterator Pos = iterator(pos);
            std::rotate(Pos, Pos + 1, m_last);
            --m_last;
            return Pos;
        }
        
        iterator erase(const_iterator first, const_iterator last)
        {
            iterator Pos1 = iterator(first);
            iterator Pos2 = iterator(last);
            std::rotate(Pos1, Pos2, m_last);
            m_last =m_last-(last-first);
            return (Pos1);
        }
        
        vector& operator=(const vector& other)
        {  if (m_first!=nullptr)
            delete [] m_first;
            
            if (other.size()>0){
                this->m_first=new Type[other.size()];
                this->m_last=this->m_first+other.size();
                std::copy(other.m_first,other.m_last,this->m_first);}
            else m_first=m_last=nullptr;
            
            return *this;
        }
        
        vector& operator=(vector&& other)
        {   if (m_first!=nullptr)
            delete [] m_first;
            
            m_first=m_last=nullptr;
            std::swap(m_first,other.m_first);
            std::swap(m_last,other.m_last);
            return *this;
        }
        
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            if (m_first!=nullptr)
                delete [] m_first;
            
            this->  m_first=new Type[last-first];
            this->   m_last=m_first+(last-first);
            std::copy(first,last,this->m_first);
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
        iterator test;
        iterator itr;
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
