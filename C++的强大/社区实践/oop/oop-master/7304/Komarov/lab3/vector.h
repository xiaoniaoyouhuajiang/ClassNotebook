#ifndef VECTOR_H
#define VECTOR_H
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>


  template <typename Type>
  class Vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit Vector(size_t count = 0);

      template <typename InputIterator>
          Vector(InputIterator first, InputIterator last);

    Vector(std::initializer_list<Type> init);

    Vector(const Vector& other);

    Vector(Vector&& other);

    ~Vector();

    //assignment operators
    Vector &operator=(const Vector &other);

    // Оператор перемещения
    Vector& operator=(Vector&& other);
        // assign method
        template <typename InputIterator>
    void assign(InputIterator first, InputIterator last);

    // resize methods
    void resize(size_t count);

    // Удаление элемента
       iterator erase(const_iterator pos);


       // Удаление элементов
       iterator erase(const_iterator first, const_iterator last);

       // Вставляет value перед элементом, на который указывает pos.
               iterator insert(const_iterator pos, const Type& value);

               // Вставляет элементы из диапазона [first, last) перед элементом, на который указывает pos.
               template <typename InputIterator>
               iterator insert(const_iterator pos, InputIterator first, InputIterator last);
               // Добавляет данный элемент value до конца контейнера.
               void push_back(const value_type& value);

    //at methods
    reference at(size_t pos);
    const_reference at(size_t pos) const;

    //[] operators
    reference operator[](size_t pos);

    const_reference operator[](size_t pos) const;

    //*begin methods
    iterator begin();

    const_iterator begin() const;

    //*end methods
    iterator end();

    const_iterator end() const;

    //size method
    size_t size() const;

    //empty method
    bool empty() const;
  private:
    reference checkIndexAndGet(size_t pos) const;
    void swap(Vector &v1, Vector &v2);
    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };

#endif // VECTOR_H
