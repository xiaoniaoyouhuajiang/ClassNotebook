#ifndef shared_ptr_hpp
#define shared_ptr_hpp

namespace stepik
{
    template <typename T>
    class shared_ptr
    {
    public:
        
        template <typename U>
        friend class shared_ptr;
        explicit shared_ptr(T *otherptr = 0)
        {
            ptr=otherptr;
            if (ptr) {
                link=new long(1);
            }
            
            else {
                link=nullptr;
                
            }
            // implement this
        }
        
        ~shared_ptr()
        {
            decrease();
            // implement this
        }
        
        template <typename U>
        shared_ptr(const shared_ptr<U> & other):ptr(other.ptr)
        {
            link=other.link;
            if (link)
                ++(*link);
            // implement this
        }
        template <typename U>
        shared_ptr& operator=(const shared_ptr<U> & other)
        {
            decrease();
            ptr=other.ptr;
            link=other.link;
            if (link)
                ++(*link);
            return *this;
            // implement this
        }
        
        explicit operator bool() const
        {
            return (ptr!=nullptr);
            // implement this
        }
        
        T* get() const
        {
            return ptr;
            // implement this
        }
        
        long use_count() const
        {
            if (link)
                return *link;
            else
                return 0;
            
            
            // implement this
        }
        
        T& operator*() const
        {
            return *ptr;
            // implement this
        }
        
        T* operator->() const
        {
            return ptr;
            // implement this
        }
        
        void swap(shared_ptr& x) noexcept
        {
            std::swap(ptr, x.ptr);
            std::swap(link, x.link);
            // implement this
        }
        
        void reset(T *otherptr = 0)
        {
            decrease();
            ptr=nullptr;
            link=nullptr;
            ptr=otherptr;
            if (ptr)
                link=new long (1);
            else
                link=nullptr;
            
            
        }
        long * getLink()
        {
            return link;
        }
        
    private:
        T *ptr;
        long *link;
        void decrease ()
        {
            if ((ptr) &&(link)&&(!--(*link))){
                delete ptr;
                delete link;
                link=0;
                
            }
        }
        // data members
    };
    
    template <typename Z, typename  U> //1
    bool  operator==(const shared_ptr<Z>& lhs, const shared_ptr<U>& rhs)
    {
        return  lhs.get() == rhs.get();
    }
    
    
    template <class Z, class U> //2
    bool   operator!=(const shared_ptr<Z>& lhs, const shared_ptr<U>& rhs)
    {
        return !(lhs == rhs);
    }
    
    template <class Z, class U> //3
    bool operator<(const shared_ptr<Z>& lhs, const shared_ptr<U>& rhs)
    {
        return lhs.get()<rhs.get();
    }
    
    template <class Z, class U> //4
    bool  operator>(const shared_ptr<Z>& lhs, const shared_ptr<U>& rhs)
    {
        return rhs < lhs;
    }
    
    template <class Z, class U> //5
    bool  operator<=(const shared_ptr<Z>& lhs, const shared_ptr<U>& rhs)
    {
        return !(rhs < lhs);
    }
    
    template <class Z, class U> //6
    bool  operator>=(const shared_ptr<Z>& lhs, const shared_ptr<U>& rhs)
    {
        return !(lhs < rhs );
    }
    
    template <class Z> //7
    bool  operator==(const shared_ptr<Z>& lhs, std::nullptr_t rhs)
    {
        return !lhs;
    }
    
    template <class Z> //8
    bool  operator==(std::nullptr_t lhs, const shared_ptr<Z>& rhs)
    {
        return !rhs;
    }
    
    template <class Z> //9
    bool operator!=(const shared_ptr<Z>& lhs, std::nullptr_t rhs)
    {
        return (bool)lhs;
    }
    
    template <class Z> //10
    bool operator!=(std::nullptr_t lhs, const shared_ptr<Z>& rhs)
    {
        return (bool)rhs;
    }
    template< class Z > //11
    bool  operator<( const shared_ptr<Z>& lhs, std::nullptr_t rhs )
    {
        return lhs.get()<nullptr;
    }
    
    template< class Z > //12
    bool  operator<( std::nullptr_t lhs, const shared_ptr<Z>& rhs ) {
        return nullptr<rhs;
    }
    
    template< class Z > //13
    bool  operator>( const shared_ptr<Z>& lhs, std::nullptr_t rhs ) {
        return nullptr < lhs;
    }
    
    template< class Z > //14
    bool  operator>( std::nullptr_t lhs, const shared_ptr<Z>& rhs )
    {
        return rhs < nullptr;
    }
    template< class Z > //15
    bool  operator<=( const shared_ptr<Z>& lhs, std::nullptr_t rhs ) 
    {
        return !(nullptr < lhs);
    }
    template< class Z > //16
    bool  operator<=( std::nullptr_t lhs, const shared_ptr<Z>& rhs ) 
    {
        return !(rhs < nullptr);
    }
    template< class Z > //17
    bool  operator>=( const shared_ptr<Z>& lhs, std::nullptr_t rhs ) 
    {
        return !(lhs < nullptr);
    }
    template< class Z > //18
    bool  operator>=( std::nullptr_t lhs, const shared_ptr<Z>& rhs )
    {
        return !(nullptr < rhs);
    }
}

#endif
