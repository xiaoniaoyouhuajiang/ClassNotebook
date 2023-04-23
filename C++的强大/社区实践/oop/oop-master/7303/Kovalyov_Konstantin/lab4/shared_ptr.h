namespace stepik
{
  template <typename T>
  class shared_ptr
  {
      template <typename Type>
      friend class shared_ptr;
      
  public:
    explicit shared_ptr(T *ptr = 0) {
        m_ptr = ptr;
        counter = ptr ? new long(1) : 0;
    }

    ~shared_ptr() {
        decrease_or_free();
    }

    template <typename Type>
    shared_ptr(const shared_ptr<Type> &other) : m_ptr(other.m_ptr), counter(other.counter) {
        if (m_ptr) {
            ++*counter;
        }
    }

    template <typename Type>
    shared_ptr& operator=(const shared_ptr<Type> &other) {
        if (*this == other)
            return *this;
        
        decrease_or_free();
        m_ptr = other.m_ptr;
        counter = other.counter;
            
        if (m_ptr) ++*counter;
        
        return *this;
    }

    explicit operator bool() const {
        return !(m_ptr == nullptr);
    }

    T* get() const {
        return m_ptr;
    }

    long use_count() const {
        return m_ptr ? *counter : 0;
    }

    T& operator*() const {
        return *m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }
      
    template <typename Type>
    bool operator==(const shared_ptr<Type> &x) const {
        return (m_ptr == x.m_ptr);    
    }

    void swap(shared_ptr &x) noexcept {
        if (this != &x) {
            shared_ptr<T> temp(*this);
            m_ptr = x.m_ptr;
            counter = x.counter;
            x = temp;
        }
    }

    void reset(T *ptr = 0) {
        decrease_or_free();
        m_ptr = ptr;
        counter = ptr ? new long(1) : 0;
    }
      
  private:
      void decrease_or_free() {
          /*if (m_ptr && --(*counter) != 0) {
              delete m_ptr;
              delete counter;
          }*/
      }

  private:
      T *m_ptr;
      long *counter;
  };      
} // namespace stepik
