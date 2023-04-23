
namespace stepik
{
    template <typename T>
    class shared_ptr
    {
        template <typename X>
        friend class shared_ptr;
        
    public:
        explicit shared_ptr(T *ptr = 0)
        {
            number = new long(1);
            mem = ptr;
        }
        
        ~shared_ptr()
        {
            decrement();
        }
        
        template <typename X>
        shared_ptr(const shared_ptr<X> & other){
            mem = (T*)other.mem;
            number = other.number;
            ++(*number);
        }
        
        template <typename X>
        shared_ptr& operator=(const shared_ptr<X> & other)
        {
            
            if((void*)this == (void*)(&other)) return *this;
            decrement();
            mem = (T*)other.mem;
            number = other.number;
            ++(*number);
            return *this;
        }
        
        shared_ptr(const shared_ptr<T> & other)
        {
            mem = other.mem;
            number = other.number;
            ++(*number);
        }
        
        shared_ptr& operator=(const shared_ptr<T> & other)
        {
            if(this == &other){
                return *this;
            }
            decrement();
            mem = other.mem;
            number = other.number;
            ++(*number);
            return *this;
        }
        
        bool operator==(const shared_ptr & other) const{
            return mem == other.mem;
        }
        
        template <typename X>
        bool operator==(const shared_ptr<X> & other) const{
            return (void*)mem == (void*)(other.mem);
        }
        
        explicit operator bool() const
        {
            return (bool)mem;
        }
        
        T* get() const
        {
            return mem;
        }
        
        long* get_count(){
            return number;
        }
        
        long use_count() const
        {
            return mem ? *number : 0;
        }
        
        T& operator*() const
        {
            return *mem;
        }
        
        T* operator->() const
        {
            return mem;
        }
        
        void swap(shared_ptr& x) noexcept
        {
            long *a = number;
            void *b = mem;
            number = x.number;
            mem = x.mem;
            x.number = a;
            x.mem = (T*)b;
        }
        
        void reset(T *ptr = 0)
        {
            shared_ptr tmp(ptr);
            swap(tmp);
            return;
            --(*number);
            mem = ptr;
            number = new long(1);
        }
        
    private:
        void decrement(){
            if(*number <= 1){
                delete number;
                delete mem;
                number = nullptr;
                mem = nullptr;
            }
            else{
                --(*number);
            }
        }
        long *number;
        T *mem;
    };
}
