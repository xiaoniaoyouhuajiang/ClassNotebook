#include <algorithm> 
#include <cstddef> 

namespace stepik 
{ 
    template <typename T> 
    class shared_ptr 
    { 
        template <typename C> 
        friend class shared_ptr; 
        public: 
        explicit shared_ptr(T *ptr = 0) : p_(ptr), c_(0) 
        { 
            if (p_) 
            c_ = new size_t(1); 
        } 

        ~shared_ptr() 
        { 
            if (c_ && (--*c_ == 0)) 
            { 
                delete p_; 
                delete c_; 
            } 
        } 

        template <typename C> 
        shared_ptr(const shared_ptr<C> &other) 
        {
            if (other.get()) 
            { 
                p_ = other.get(); 
                c_ = other.get_c(); 
                ++(*c_); 
            } 
            else 
            { 
                p_ = nullptr; 
                c_ = nullptr; 
            } 
        } 

        template <typename C> 
        shared_ptr& operator = (const shared_ptr<C> &other) 
        {
            shared_ptr p (other); 
            swap(p); 
        } 

        template <typename C> 
        bool operator == (const shared_ptr<C> &other) const 
        { 
            return (p_==other.p_); 
        } 

        explicit operator bool() const  
        {
            return (p_ != nullptr); 
        } 

        T* get() const 
        {
            return p_; 
        } 

        long use_count() const 
        {
            return (c_) ? *c_ : 0; 
        } 

        T& operator*() const 
        {
            return (*p_); 
        } 

        T* operator->() const 
        { 
            return p_; 
        } 

        void swap(shared_ptr& x) noexcept 
        { 
            if (this != &x) 
            { 
                shared_ptr<T> tmp(*this); 
                *this = x; 
                x = tmp; 
            } 
        } 

        void reset(T *ptr = 0)  
        {
            shared_ptr p(ptr); 
            swap(p); 
        } 

        private: 
        T *p_; 
        size_t *c_; 
        size_t* get_c() const 
        { 
            return c_; 
        } 
    }; 
} // namespace stepik