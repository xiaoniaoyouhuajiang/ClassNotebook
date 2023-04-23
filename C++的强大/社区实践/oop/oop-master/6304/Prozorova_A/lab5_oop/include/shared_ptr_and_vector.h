#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>
namespace stepik
{
  template <typename T>
  class shared_ptr
  {
    public:

        explicit shared_ptr(T *ptr = 0)
            :m_ptr(ptr), count( ptr ? new size_t(1) : nullptr )
        {}

        ~shared_ptr()
        {
            if (use_count() > 1) --(*count);
            else
            {
                delete m_ptr;
                delete count;
                m_ptr = nullptr;
                count = nullptr;
            }
        }

        shared_ptr(const shared_ptr & other)
        {
            m_ptr = other.get();
            count = other.get_count();
            if (use_count()) ++(*count);
        }

        shared_ptr& operator=(const shared_ptr & other)
        {
            if (this != &other) {
                this->~shared_ptr();
                m_ptr = other.get();
                count = other.get_count();
                if (use_count()) ++(*count);
            }
            return *this;
        }

      //--------------------------------------------------

        //копирование указателей на полиморфные объекты
        template <typename S>
        shared_ptr(const shared_ptr<S> & other)
        {
            m_ptr = other.get();
            count = other.get_count();
            if (use_count()) ++(*count);
        }

        template <typename S>
        shared_ptr& operator=(const shared_ptr<S> & other)
        {
            if (get()!= other.get()) {
                this->~shared_ptr();
                m_ptr = other.get();
                count = other.get_count();
                if (use_count()) ++(*count);
            }
            return *this;
        }

      //---------------------------------------------------

        explicit operator bool() const
        {
            return m_ptr != nullptr;
        }

        T* get() const
        {
            return m_ptr;
        }

        //возвращает количество объектов shared_ptr, которые ссылаются на тот же управляемый объект
        size_t use_count() const
        {
            if (m_ptr) return *count;
            else return 0;
        }

        size_t* get_count() const
        {
            if (m_ptr) return count;
            else return nullptr;
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
            std::swap(count, x.count);
        }

        //заменяет объект, которым владеет
        void reset(T *ptr = 0)
        {
            shared_ptr<T>(ptr).swap(*this);
        }

       //оператор сравнения
        template <typename S>
        bool operator ==(const shared_ptr<S> &other) const {
            return get() == other.get();
        }


      private:
      T* m_ptr;
      size_t* count;

    };


  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

      //конструкторы
    explicit vector(size_t count = 0)
    {
        m_first = new Type[count];
        m_last = m_first + count;
    }

    template <typename InputIterator>
    //Создает вектор из элементов, лежащих между first и last
    vector(InputIterator first, InputIterator last)
    {
        int count = last - first;
        m_first = new Type[count];
        for(int i = 0; i<count; ++i)
        {
            m_first[i] = *first;
            first++;
        }
        m_last = m_first + count;
    }

    vector(std::initializer_list<Type> init)
    {
        int count = init.size();
        m_first = new Type[count];
        int i = 0;
        for(Type it : init) {
               m_first[i] = it;
               ++i;
        }
        m_last = m_first + count;
    }

    //конструктор копирования
    vector(const vector& other)
    {
        int count = other.size();
        m_first = new Type[count];
        for(int i = 0; i < count; ++i)
        {
            m_first[i] = other[i];
        }
        m_last = m_first + count;
    }

    //конструктор перемещения
    vector(vector&& other)
               :vector()
    {
       std::swap(m_first, other.m_first);
       std::swap(m_last, other.m_last);
    }

   //деструктор
    ~vector()
    {
        delete [] m_first;
    }

    //операторы присваивания
    vector& operator=(const vector& other)
    {
        int count = other.size();
        if(!empty()) delete [] m_first;
        m_first = new Type[count];
        for(int i = 0; i < count; i++)
                m_first[i] = other.m_first[i];

         m_last = m_first + count;
         return *this;
    }

    vector& operator=(vector&& other)
    {
         std::swap(m_first, other.m_first);
         std::swap(m_last, other.m_last);
    }

    // метод assign: заменяет содержимое вектора элементами, лежащими между first и last
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
          int count = last - first;
          if(!empty()) delete [] m_first;
          m_first = new Type[count];
          for(int i = 0; i < count; ++i)
          {
              m_first[i] = *first;
              ++first;
          }
          m_last = m_first + count;
    }


    // resize methods
    //Изменяет размер вектора на заданную величину
    void resize(size_t count)
    {
        vector temp = *this;
        if(!empty()) delete[] m_first;
        m_first = new Type[count];
        m_last = m_first + count;
        if (count > temp.size()) count = temp.size();
        for(int i = 0; i < count; i++)
        {
            m_first[i] = temp.m_first[i];
        }
    }

    //erase methods
    //Удаляет указанные элементы вектора
    //возвращает итератор, следующий за последним удаленным элементом
    iterator erase(const_iterator pos)
    {
        int num = pos - m_first;
        //rotate - меняет местами элементы в двух соседних диапазонах
        std::rotate(m_first + num, m_first+ num + 1, m_last);
        resize(size() - 1);
        return m_first + num;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        int num = first - m_first;
        int num2 = last - first;
        std::rotate(m_first + num, m_first + num + num2, m_last);
        resize(size() - num2);
        return m_first + num;
    }

    //insert methods

    //вставляет value перед элементом, на который указывает pos
    iterator insert(const_iterator pos, const Type& value)
    {
         int num;
         if(size() == 0) num = 0;
         else num = pos - m_first;
         resize(size() + 1);
         m_first[size() - 1] = value;
         std::rotate(m_first + num, m_first + size() - 1, m_last);
         return m_first + num;
    }

    //Вставляет элементы из диапазона [first, last) перед элементом, на который указывает pos
    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
         int num = pos - m_first;
         int len = last - first;
         int last_size = size();
         resize(size() + len);
         std::copy(first, last, m_first + last_size);
         std::rotate(m_first + num, m_first + last_size, m_last);
         return m_first + num;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
         insert(m_last, value);
    }

    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }


    void print()
    {
        if (empty()){
               std::cout <<"Vector is empty" << std::endl;
               return;
        }
        else {
               for (int i = 0; i < size(); i++){
                   std::cout << at(i) << " ";
               }
               std::cout << std::endl;
         }
    }

  private:
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
} // namespace stepik

#endif // SHARED_PTR_H
