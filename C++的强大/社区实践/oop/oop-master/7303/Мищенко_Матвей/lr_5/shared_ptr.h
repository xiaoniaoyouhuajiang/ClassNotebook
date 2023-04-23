namespace stepik
{
    template <typename T>
    class shared_ptr
    {
    public:
        explicit shared_ptr(T *ptr = 0)
        {pointer=ptr;
            if (pointer!=nullptr)
                count = new long(1);
            else count=nullptr;
        }
        
        
        ~shared_ptr()
        {
            if(pointer!=nullptr){
                if((*count)==1){
                    delete pointer;
                    delete count;}
                else (*count)--;
            }
        }
        template <class Y>
        friend class shared_ptr;
        
        template <class Y>
        shared_ptr(const shared_ptr<Y> & other):pointer(other.pointer),count(other.count)
        { if(pointer) (*count)++;}
        template <class Y>
        shared_ptr& operator=(const shared_ptr<Y> & other)
        {
            shared_ptr<T>(other).swap(*this);
            return *this;
        }
        template <class Y>
        bool operator==(const shared_ptr<Y> & other) const
        {
            return pointer==other.pointer;
        }
        
        explicit operator bool() const
        {
            if (pointer !=nullptr)
                return true;
            else return false;
        }
        
        T* get() const
        {
            return pointer;
        }
        
        long use_count() const
        {
            if (count)
                return (*count);
            else return 0;
        }
        
        T& operator*() const
        {
            return *pointer;
        }
        
        T* operator->() const
        {
            return pointer;
        }
        
        void swap(shared_ptr& x) noexcept
        {
            std::swap(pointer, x.pointer);
            std::swap(count,x.count);
        }
        
        void reset(T *ptr = 0)
        { shared_ptr<T>(ptr).swap(*this);}
        
        
    private:
        T *pointer;
        long *count;
    };
    template<class T, class ... Args>
    shared_ptr<T> make_shared(Args  ... args)
    {
        
        return shared_ptr<T>(new T(args...));
    }
    
}
