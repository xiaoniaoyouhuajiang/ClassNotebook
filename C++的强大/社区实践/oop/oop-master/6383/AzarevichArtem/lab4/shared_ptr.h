template <typename T>
 class shared_ptr
 {
     template <typename Derived>
     friend class shared_ptr;
	 
 public:
 
    explicit shared_ptr(T *ptr = 0) : index(ptr), counter(new long(1))
    {}

    ~shared_ptr()
    {
         crusher();
    }
//////////////////////////////////////////////////////////////
// Конструктор копирования
    shared_ptr(const shared_ptr & other) : index(other.index), counter(other.counter)
    {
         (*counter)++;
    }

    template <typename Derived>
    shared_ptr(const shared_ptr<Derived> & other) : index( (T *)other.index), counter(other.counter)
    {
         (*counter)++;
    }
//////////////////////////////////////////////////////////////
// Оператор копирования
    shared_ptr& operator=(const shared_ptr & other)
    {
         if ( (void *)this == (void *)&other ) return *this;

         crusher();

         index = (T*)other.index;
         counter = other.counter;

         (*counter)++;

         return *this;
    }

    template <typename Derived>
    shared_ptr& operator=(const shared_ptr<Derived> & other)
    {
         if ( (void *)this == (void *)&other ) return *this;

         crusher();

         index = (T*)other.index;
         counter = other.counter;

         (*counter)++;

         return *this;
    }
//////////////////////////////////////////////////////////////
// Оператор сравнения
    bool operator==(const shared_ptr &other) const
    {
        return (void*)index==(void*)other.index;
    }

    template <typename Derived>
    bool operator==(const shared_ptr<Derived> &other) const
    {
        return (void*)index==(void*)other.index;
    }
//////////////////////////////////////////////////////////////

	// Храним ли что-то?
    explicit operator bool() const
    {
         return index != NULL;
    }

	// Доступ к хранимому
    T* get() const
    {
         return index;
    }

    // Возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
    long use_count() const
    {
         return ( index == NULL) ? 0 : *counter;
    }

    // Ссылка на управляемый объект
    T& operator*() const
    {
         return *index;
    }

    // Указатель на управляемый объект
    T* operator->() const
    {
         return index;
    }

    // Обменивает указатели
    void swap(shared_ptr& x) //noexcept
    {
         std::swap( this->index, x.index);
         std::swap( this->counter, x.counter);
    }

    // Замещает указатель другим
    void reset(T *ptr = 0)
    {
         shared_ptr x(ptr);
         swap( x );
    }


  private:

     // Убирает контроль за указателем
     void crusher()
     {
         //if ( *counter == 0 ) throw " ";

         if( (*counter) > 1)
         {
             (*counter)--;
             return;
         }

         delete index;
         delete counter;
     }

     T *index = NULL;
     long *counter;

  };