// 4 лабораторная работа
namespace stepik{
template <typename T>
class shared_ptr{
public:
    template <typename X>
    friend class shared_ptr;

    explicit shared_ptr(T *ptr = 0) : ptr_(ptr){
        if (ptr_)
            count_ = new int(1);
        else
            count_ = nullptr;
    }

    ~shared_ptr(){
        if (count_ && (!--(*count_))){
            delete ptr_;
            delete count_;
        }
    }


    shared_ptr(const shared_ptr<T> & other):ptr_(other.ptr_), count_(other.count_){
        if (count_)
            ++(*count_);
    }

    template <typename X>
    shared_ptr(const shared_ptr<X> & other):ptr_(other.ptr_), count_(other.count_){
        count_ = other.count_;
        if (count_)
            ++(*count_);
    }

    shared_ptr& operator=(const shared_ptr<T>& other){
        if(this != &other){
            this->~shared_ptr();
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_)
                ++(*count_);
        }
        return *this;
    }

    template <typename X>
    shared_ptr& operator=(const shared_ptr<X> & other){
        this->~shared_ptr();
        ptr_ = other.ptr_;
        count_ = other.count_;
        if (count_)
            ++(*count_);
        return *this;
    }

    explicit operator bool() const{ // without explicite it can update to int
        return !(ptr_ == nullptr);
    }

    T* get() const{
        return ptr_;
    }

    long use_count() const{
        if (count_)
            return *count_;
        return 0;
    }

    T& operator*() const{
        return *ptr_;
    }

    T* operator->() const{
        return ptr_;
    }

    void swap(shared_ptr& x) noexcept{
        std::swap(ptr_, x.ptr_);
        std::swap(count_, x.count_);
    }

    void reset(T *ptr = 0){
        shared_ptr<T>(ptr).swap(*this);
    }

private:
    T *ptr_;
    int* count_;
};
    template <typename T, typename  U> //1
    bool  operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs){
        return  lhs.get() == rhs.get();
    }
}
