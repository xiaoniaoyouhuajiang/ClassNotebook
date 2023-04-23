using namespace std;

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  template<typename U>
  friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0) : ptr(ptr), count(new int(1)) {}

    ~shared_ptr() {
        if (--(*count) == 0) {
            delete ptr;
            delete count;
        }
    }

	shared_ptr(const shared_ptr & other) : ptr(other.ptr), count(other.count) {
        ++(*count);
    }

    template <typename U>
    shared_ptr(const shared_ptr<U> & other) : ptr(other.ptr), count(other.count) {
        if (count)
            ++(*count);
    }

	shared_ptr& operator=(const shared_ptr & other) { 
        shared_ptr ptr(other);
        swap(ptr);
        return *this;
    }

    template <typename U>
    shared_ptr& operator=(const shared_ptr<U> & other) {
        shared_ptr ptr(other);
        swap(ptr);
        return *this;
    }

    bool operator == (const shared_ptr &other) const {
        return ptr == other.ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    T* get() const {
        return ptr;
    }

    unsigned use_count() const {
        return (ptr) ? *count : 0;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    void swap(shared_ptr& x) noexcept {
        std::swap(this->ptr, x.ptr);
        std::swap(this->count, x.count);
    }

    void reset(T *ptr = 0) {
        shared_ptr<T>(ptr).swap(*this);   
    }

  private:
      T* ptr;
      int *count;
  };      
} 