#include "Vector.h"

using namespace std;

    template <typename Type>
   Vector<Type>::Vector(size_t count)
          {
       m_first = new Type[count];
       m_last = &(m_first[count]);
          }

    template <typename Type>
   template <typename InputIterator>
          Vector<Type>::Vector(InputIterator first, InputIterator last)
          {
             m_first = new value_type[last-first];
             m_last  = m_first + (last-first);

             std::copy(first, last, m_first);
          }
 template <typename Type>
    Vector<Type>::Vector(std::initializer_list<Type> init) : Vector<Type>::Vector(init.begin(), init.end())
        {}
 template <typename Type>
    Vector<Type>::Vector(const Vector& other) : Vector(other.begin(), other.end())
        {}
 template <typename Type>
    Vector<Type>::Vector(Vector&& other) : m_first(other.begin()), m_last(other.end())
        {
            other.m_first = other.m_last = NULL;
        }
  template <typename Type>
   Vector<Type>::~Vector()
        {
            delete [] m_first;
            m_first = m_last = NULL;
        }

    //assignment operators
   template <typename Type>
   Vector<Type>& Vector<Type>::operator=(const Vector<Type> &other)
   {
   if ( ((void *)this) == ((void *)(&other)) )
   return *this;

   Vector a(other);
   swap(*this, a);

   return *this;
   }

    // Оператор перемещения
    template <typename Type>
   Vector<Type>& Vector<Type>::operator=(Vector<Type>&& other)
    {
        if ( ((void *)this) == ((void *)(&other)) )
            return *this;

        swap( *this, other);

        return *this;
    }

        // assign method

    template <typename Type>
   template <typename InputIterator>
    void Vector<Type>::assign(InputIterator first, InputIterator last)
    {
      Vector a(first, last);
      swap(*this, a);
    }

    // resize methods
    template <typename Type>
    void Vector<Type>::resize(size_t count)
        {
             if ( count == (m_last-m_first) ){
                 return;
             }
             if ( count < (size()) )
             {
                 Vector<Type> a(m_first, m_first+count);
                 swap(*this, a);
             }
             else
             {
                Vector<Type> a(count);
                std::copy(m_first, m_last, a.m_first);
                swap(*this, a);
             }
        }

    // Удаление элемента
    template <typename Type>
       typename Vector<Type>::iterator Vector<Type>::erase(Vector<Type>::const_iterator pos)
       {
            size_t offset = pos-m_first;
            std::rotate( m_first+offset, m_first+offset+1, m_last);

            resize(size()-1);
            return m_first + offset;
       }


       // Удаление элементов
       template <typename Type>
       typename Vector<Type>::iterator Vector<Type>::erase(Vector<Type>::const_iterator first, Vector<Type>::const_iterator last)
       {
            size_t offset = first-m_first;
            std::rotate( m_first + offset, m_first + (last-m_first), m_last);

            resize(size() - (last-first));
            return m_first + offset;
       }

       // Вставляет value перед элементом, на который указывает pos.
       template <typename Type>
       typename Vector<Type>::iterator Vector<Type>::insert(Vector<Type>::const_iterator pos, const Type& value)
       {
       size_t offset = pos - m_first;

       resize(size()+1);
       *(m_last-1) = value;
       std::rotate(m_first+offset, m_last-1, m_last);

       return m_first + offset;
       }

               // Вставляет элементы из диапазона [first, last) перед элементом, на который указывает pos
       template <typename Type>
               template <typename InputIterator>

               typename Vector<Type>::iterator Vector<Type>::insert(Vector<Type>::const_iterator pos, InputIterator first, InputIterator last)
               {
                   size_t offset = pos - m_first;

                   resize( size() + (last-first));

                   std::copy(first, last, m_last - (last-first));
                   std::rotate(m_first+offset, m_last - (last-first) , m_last);

                   return m_first + offset;
               }

               // Добавляет данный элемент value до конца контейнера.
               template <typename Type>
               void Vector<Type>::push_back(const value_type& value)
               {
                   resize(size()+1);
                   *(m_last-1) = value;
               }

    //at methods
               template <typename Type>
    typename Vector<Type>::reference Vector<Type>::at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }
    template <typename Type>
    typename Vector<Type>::const_reference Vector<Type>::at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }
    template <typename Type>
    //[] operators
    typename Vector<Type>::reference Vector<Type>::operator[](size_t pos)
    {
      return m_first[pos];
    }
    template <typename Type>
    typename Vector<Type>::const_reference Vector<Type>::operator[](size_t pos) const
    {
      return m_first[pos];
    }
    template <typename Type>
    //*begin methods
    typename Vector<Type>::iterator Vector<Type>::begin()
    {
      return m_first;
    }
    template <typename Type>
    typename Vector<Type>::const_iterator Vector<Type>::begin() const
    {
      return m_first;
    }
    template <typename Type>
    //*end methods
    typename Vector<Type>::iterator Vector<Type>::end()
    {
      return m_last;
    }
    template <typename Type>
    typename Vector<Type>::const_iterator Vector<Type>::end() const
    {
      return m_last;
    }
    template <typename Type>
    //size method
    size_t Vector<Type>::size() const
    {
      return m_last - m_first;
    }
    template <typename Type>
    //empty method
    bool Vector<Type>::empty() const
    {
      return m_first == m_last;
    }
    template<typename Type>
    typename Vector<Type>::reference Vector<Type>::checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }
    template <typename Type>
    void Vector<Type>::swap(Vector &v1,Vector &v2)
    {
        std::swap(v1.m_first, v2.m_first);
        std::swap(v1.m_last, v2.m_last);
    }
