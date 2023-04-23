namespace stepik {
    template <typename T>
    class shared_ptr {

        template <typename Derived>
        friend class shared_ptr;

    public:
        
        // Constructors and destructor
        
        explicit shared_ptr(T * ptr = nullptr) : ptr(ptr), counter(new unsigned(1)) {
        }

        shared_ptr(const shared_ptr & other) : ptr(other.ptr), counter(other.counter) {
            inc_counter();
        }

        template <typename Derived>
        shared_ptr(const shared_ptr<Derived> & other) : ptr((T*)other.ptr), counter(other.counter) {
            inc_counter();
        }
      
        ~shared_ptr() {
            dec_counter();
        }
        

        // Methods and operators

        shared_ptr& operator = (const shared_ptr & other) {
            if (ptr != other.ptr) {
                dec_counter();
                ptr = other.ptr;
                counter = other.counter;
                inc_counter();
            }
            return *this;
        }

        template <typename Derived>
        shared_ptr& operator = (const shared_ptr<Derived> & other) {
            if (ptr != other.ptr) {
                dec_counter();
                ptr = other.ptr;
                counter = other.counter;
                inc_counter();
            }
            return *this;
        }

        explicit operator bool() const {
            return ptr != nullptr;
        }

        template <typename Derived>  
        bool operator == (const shared_ptr<Derived> & other) const {
            return ptr == other.ptr;
        }

        template <typename Derived>  
        bool operator != (const shared_ptr<Derived> & other) const {
            return ptr != other.ptr;
        }

        template <typename Derived>
        bool operator < (const shared_ptr<Derived> & other) const {
            return ptr < other.ptr;
        }

        template <typename Derived>
        bool operator <= (const shared_ptr<Derived> & other) const {
            return ptr <= other.ptr;
        }

        template <typename Derived>
        bool operator > (const shared_ptr<Derived> & other) const {
            return ptr > other.ptr;
        }

        template <typename Derived>
        bool operator >= (const shared_ptr<Derived> & other) const {
            return ptr >= other.ptr;
        } 

        T* get() const {
            return ptr;
        }

        unsigned use_count() const {
            return ptr == nullptr ? 0 : *counter;
        }

        T& operator*() const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        void swap(shared_ptr& x) noexcept {
            std::swap(ptr, x.ptr);
            std::swap(counter, x.counter);
        }

        void reset(T *ptr = 0) {
            shared_ptr temp(ptr);
            swap(temp);
        }

      
    private:
        void dec_counter() {
            if (--(*counter) == 0) {
                delete ptr; 
                delete counter; 
            }
        }
      
        void inc_counter() {
            (*counter)++;
        }
      
    private:
        T* ptr;
        unsigned* counter;

    };      
}
