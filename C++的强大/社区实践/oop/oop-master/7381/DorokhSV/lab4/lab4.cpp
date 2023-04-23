namespace stepik
{
  template <typename T>
  class shared_ptr
  {
      public:
      template <typename S>
      friend class shared_ptr;
      explicit shared_ptr(T *ptr = nullptr) : m_ptr(ptr), m_count(ptr ? new size_t(1) : nullptr) {}

      ~shared_ptr()
      {
          destroy();
      }

      shared_ptr(const shared_ptr & other) : m_ptr(other.m_ptr), m_count(other.m_count)
      {
          if(m_count)
              (*m_count)++;
      }
      
      template <typename S>
      shared_ptr(const shared_ptr<S> & other) : m_ptr(other.m_ptr), m_count(other.m_count)
      {
          if(m_count)
              (*m_count)++;
      }

      shared_ptr& operator=(const shared_ptr & other)
      {
          shared_ptr tmp(other);
          swap(tmp);
          return *this;
      }
      
      template <typename S>
      shared_ptr& operator=(const shared_ptr<S> & other)
      {
          shared_ptr tmp(other);
          swap(tmp);
          return *this;
      }

      explicit operator bool() const
      {
          return (m_ptr != nullptr);
      }

      T* get() const
      {
          return m_ptr;
      }

      long use_count() const
      {
          return (m_count ? *m_count : 0);
      }

      T& operator*() const
      {
          return *m_ptr;
      }

      T* operator->() const
      {
          return m_ptr;
      }

      void swap(shared_ptr& x) noexcept
      {
          std::swap(m_ptr, x.m_ptr);
          std::swap(m_count, x.m_count);
      }

      void reset(T *ptr = nullptr)
      {
          shared_ptr tmp(ptr);
          swap(tmp);
      }
      
      template <typename S>
      bool operator==(const shared_ptr<S> &other) const
      {
          return (m_ptr == other.m_ptr);
      }
      

      private:
      T *m_ptr;
      size_t *m_count;
      void destroy() {
          if (m_count) {
              (*m_count)--;
              if (*m_count == 0)
              {
                  delete m_ptr;
                  delete m_count;
              }
          }
      }
  };      
}