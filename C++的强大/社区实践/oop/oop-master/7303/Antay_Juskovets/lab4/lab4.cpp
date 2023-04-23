namespace stepik
{
  template <typename T>
  class shared_ptr {
    template <typename U>
    friend class shared_ptr;
    public:
        explicit shared_ptr(T *ptr = 0): ref(ptr), count(new unsigned int(1)) { }

        ~shared_ptr() {
            dec();
        }

        template <typename U>
        shared_ptr(const shared_ptr<U> &other){
            ref = dynamic_cast<const T*>(other.ref);
            count = other.count;
            inc();
        }

        template <typename U>
        shared_ptr &operator=(const shared_ptr<U> &other) {
            if(reinterpret_cast<void*>(this) != reinterpret_cast<const void*>(&other)) {
                dec();

                ref = dynamic_cast<T*>(other.ref);
                count = other.count;
                inc();
            };

            return *this;
        }

        explicit operator bool() const {
            return ref != nullptr;
        }

        template <typename U>
        bool operator == (const shared_ptr<U> &other)const{
            return reinterpret_cast<void*>(ptr) == reinterpret_cast<const void*>(other.ptr);
        }

        T *get() const {
            return ref;
        }

        long use_count() const {
            return  (ref == nullptr) ? 0 : *count;
        }

        T &operator*() const {
            return *ref;
        }

        T *operator->() const {
            return ref;
        }

        void swap(shared_ptr &x) noexcept {
            T* temp_ref = ref;
            unsigned int* temp_count = count;

            ref = x.ref;
            x.ref = temp_ref;
            count = x.count;
            x.count = temp_count;
        }

        void reset(T *ptr = 0) {
            dec();
            count = new unsigned int(1);
            ref = ptr;
        }

    private:
        T *ref;
        unsigned int* count;

        void inc(){
            (*count)++;
        }
        void dec(){
            (*count)--;
            if((*count) == 0){
                delete ref;
                delete count;
            }
        }
    };
} // namespace stepik
