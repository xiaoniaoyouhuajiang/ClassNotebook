namespace stepik
{
    template <typename T>
    class shared_ptr
    {
        template <typename V>
        friend class shared_ptr;
    public:
        explicit shared_ptr(T *ptr = 0)
        	:ptr(ptr), cnt(new long(1))
        {}

        ~shared_ptr(){
            count_dec();
        }

        template<typename V>
        shared_ptr(const shared_ptr<V>& other)
        	:ptr(other.ptr), cnt(other.cnt){
            (*cnt)++;
        }

        template<typename V>
        shared_ptr& operator=(const shared_ptr<V>& other){
            if (*this != other){
        		count_dec();
        		ptr = other.ptr;
        		cnt = other.cnt;
        		(*cnt)++;
        	}
            return *this;
        }

        explicit operator bool() const{
            return ptr != nullptr;
        }

        T* get() const{
            return ptr;
        }

        long use_count() const{
            return ptr ? *cnt : 0;
        }

        T& operator*() const{
            return *ptr;
        }

        T* operator->() const{
            return ptr;
        }

        void swap(shared_ptr& x) noexcept{
            std::swap(ptr, x.ptr);
            std::swap(cnt, x.cnt);
        }

        void reset(T *ptr = 0){
            count_dec();
            this->ptr = ptr;
            cnt = new long(1);
        }

        template<typename V>
        bool operator==(const shared_ptr<V>& other) const{
        	return ptr == other.ptr;
        }

        template<typename V>
        bool operator!=(const shared_ptr<V>& other) const{
        	return ptr != other.ptr;
        }

    private:
    	void count_dec(){
            if (--(*cnt) == 0){
                delete ptr;
                delete cnt;
            }
        }

        T* ptr;
        long* cnt;
    };
}
