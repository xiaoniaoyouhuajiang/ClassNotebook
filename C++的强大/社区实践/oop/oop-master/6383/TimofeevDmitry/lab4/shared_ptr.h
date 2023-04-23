namespace stepik {
    template<typename T>
    class shared_ptr {
        template<typename TT>
        friend class shared_ptr;
    public:
        explicit shared_ptr(T *ptr = 0) {
            ref=ptr;
            count=new unsigned int(1);
        }

        ~shared_ptr() {
            dec();
        }

        shared_ptr(const shared_ptr &other){
            ref=other.ref;
            count=other.count;
            inc();
        }

        template<typename TT>
        shared_ptr(const shared_ptr<TT> &other){
            ref=other.ref;
            count=other.count;
            inc();
        }

        shared_ptr &operator=(const shared_ptr &other) {
            if((void*)this==(void*)&other)return *this;
            dec();
            ref=(T*)other.ref;
            count=other.count;
            inc();
            return *this;
        }

        template<typename TT>
        shared_ptr &operator=(const shared_ptr<TT> &other) {
            if((void*)this==(void*)&other)return *this;
            dec();
            ref=(T*)other.ref;
            count=other.count;
            inc();
            return *this;
        }


        bool operator==(const shared_ptr &other)const{
            return (void*)ref==(void*)other.ref;
        }
        template<typename TT>
        bool operator==(const shared_ptr<TT> &other)const{
            return (void*)ref==(void*)other.ref;
        }


        explicit operator bool() const {
            return ref != nullptr;
        }

        T *get() const {
            return ref;
        }

        long use_count() const {
            return  (ref== nullptr)?0:*count;
        }

        T &operator*() const {
            return *ref;
        }

        T *operator->() const {
            return ref;
        }

        void swap(shared_ptr &x) noexcept {
            auto t=ref;
            auto c=count;
            ref=x.ref;
            x.ref=t;
            count=x.count;
            x.count=c;
        }

        void reset(T *ptr = 0) {
            dec();
            count=new unsigned int(1);
            ref=ptr;
        }

    private:
        T *ref;
        unsigned int* count;

        void inc(){
            (*count)++;
        }
        void dec(){
            if((*count==0))throw " ";
            (*count)--;
            if((*count)==0){
                delete ref;
                delete count;
            }
        }
    };
}