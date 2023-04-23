#include <assert.h>
#include <algorithm>                // std::copy, std::rotate
#include <cstddef>                  // size_t
#include <initializer_list>
#include <stdexcept>


namespace stepik
{

template <typename Type>
class vector
{
public:
    typedef Type* iterator;                             //указатель
    typedef const Type* const_iterator;                 // указатель на константу

    typedef Type value_type;                            //какое-то значение типа Type

    typedef value_type& reference;                      //ссылка
    typedef const value_type& const_reference;          //ссылка на константу


    typedef std::ptrdiff_t difference_type;             //знаковое целое (вроде int)


    //Конструктор обычный
    explicit vector(size_t count = 0)
    {
       m_first = new value_type[count];
       m_last  = m_first + count;
    }

    // Создает контейнер с содержимым диапазона [first, last).
    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
       m_first = new value_type[last-first];
       m_last  = m_first + (last-first);

       std::copy(first, last, m_first);
    }

    // Создает контейнер с содержимым списка инициализации init.
    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
    {}

    // Конструктор копирования
    vector(const vector& other) : vector(other.begin(), other.end())
    {}

    // Конструктор перемещения
    vector(vector&& other) : m_first(other.begin()), m_last(other.end())
    {
        other.m_first = other.m_last = NULL;
    }

    // Деструктор
    ~vector()
    {
        delete [] m_first;
        m_first = m_last = NULL;
    }

/////////////////////////////////////////////////////////
    // Оператор присваивания
    vector &operator=(const vector &other)
    {
        if ( ((void *)this) == ((void *)(&other)) )
            return *this;

        vector a(other);
        swap(*this, a);

        return *this;
    }

    // Оператор перемещения
    vector& operator=(vector&& other)
    {
        if ( ((void *)this) == ((void *)(&other)) )
            return *this;

        swap( *this, other);

        return *this;
    }

    // Замена содержимого в векторе
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      vector a(first, last);
      swap(*this, a);
    }
 ///////////////////////////////////////////////////

	// Изменение размера
    void resize(size_t count)
    {
         if ( count == (m_last-m_first) )
             return;

         if ( count < (size()) )
         {
             vector a(m_first, m_first+count);
             swap(*this, a);
         }
         else
         {
            vector a(count);
            std::copy(m_first, m_last, a.m_first);

            swap(*this, a);
         }
    }


    // Удаление элемента
    iterator erase(const_iterator pos)
    {
         size_t offset = pos-m_first;
         std::rotate( m_first+offset, m_first+offset+1, m_last);

         resize(size()-1);
         return m_first + offset;
    }


    // Удаление элементов
    iterator erase(const_iterator first, const_iterator last)
    {
         size_t offset = first-m_first;
         std::rotate( m_first + offset, m_first + (last-m_first), m_last);

         resize(size() - (last-first));
         return m_first + offset;
    }
////////////////////////////////////////////////////

        // Вставляет value перед элементом, на который указывает pos.
        iterator insert(const_iterator pos, const Type& value)
        {
            size_t offset = pos - m_first;

            resize(size()+1);
            *(m_last-1) = value;
            std::rotate(m_first+offset, m_last-1, m_last);

            return m_first + offset;
        }

        // Вставляет элементы из диапазона [first, last) перед элементом, на который указывает pos.
        template <typename InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last)
        {
            size_t offset = pos - m_first;

            resize( size() + (last-first));

            std::copy(first, last, m_last - (last-first));
            std::rotate(m_first+offset, m_last - (last-first) , m_last);

            return m_first + offset;
        }

        // Добавляет данный элемент value до конца контейнера.
        void push_back(const value_type& value)
        {
            resize(size()+1);
            *(m_last-1) = value;
        }

////////////////////////////////////////////////////
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

  private:
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }


    static void swap(vector &v1, vector &v2)
    {
        std::swap(v1.m_first, v2.m_first);
        std::swap(v1.m_last, v2.m_last);
    }


    //Мои спец. функции

  private:
    iterator m_first;
    iterator m_last;
  };


}
