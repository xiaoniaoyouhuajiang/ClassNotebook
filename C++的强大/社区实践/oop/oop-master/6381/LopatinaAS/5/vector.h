#pragma once

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace stepik {
  template <typename Type>
  class vector {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0) { //создает контейнер с count элементами
        if (count == 0)
            m_first = m_last = nullptr;
        else {
            m_first = new Type [count];
            m_last = m_first + count;
        }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last){
        Type *vec = new Type[last-first];
        copy(first, last, vec);
        m_first = vec;
        m_last = m_first + (last-first);
    }

    vector(std::initializer_list<Type> init): vector(init.begin(), init.end()) {}//конструктор списка инициализаторов

    vector(const vector& other) : vector(other.m_first, other.m_last){} // конструктор копирования

    vector(vector&& other) { // конструктор перемещения
        cout << "The move constructor is invoked" << endl;
        m_first = other.begin();
        m_last = other.end();
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector() {
        delete [] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other){
        cout << "The assigment operator is invoked" << endl;
        delete [] m_first;
        vector temp {other};
        m_first = temp.m_first;
        m_last = temp.m_last;
        temp.m_first = temp.m_last = nullptr;
        return *this;
    }

    vector& operator=(vector&& other) { // оператор перемещения
        cout << "The displacement operator is invoked" << endl;
        delete [] m_first;
        m_first = other.m_first;
        m_last = other.m_last;
        other.m_first = other.m_last = nullptr;
        return *this;       
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) { //назначает новое содержимое вектору
        delete [] m_first;
        vector temp {first,last};
        m_first = temp.m_first;
        m_last = temp.m_last;
        temp.m_first = temp.m_last = nullptr;
    }

     // resize methods
    void resize(size_t count) {
        vector new_vec (count);
        iterator new_last;
        if (size()>count)
            new_last = m_first + count;
        else 
            new_last = m_last;
        move(m_first, new_last, new_vec.m_first); 
        swap(m_first, new_vec.m_first); // меняем местами
        swap(m_last, new_vec.m_last);  
    }

    //erase methods
    iterator erase(const_iterator pos){
        size_t dist = pos - m_first;
        iterator begin_pos = m_first+dist;
        rotate (begin_pos, begin_pos+1, m_last); // pos перемещаем в конец, а pos+1 первый
        resize (size()-1);
        return (m_first+dist); // итератор, следующий за удаленным элементом
    }

    iterator erase(const_iterator first, const_iterator last){ // удаление в диапазоне [first; last)
        size_t dist = first - m_first;
        for (int i=0; i<(last-first);i++){
            iterator begin_pos = m_first+dist;
            erase(begin_pos);
        }
        return (m_first+dist); //итератор, следующий за последним удаленным элементом
    }

     //insert methods
     iterator insert(const_iterator pos, const Type& value) { // вставляет value перед pos
            size_t dist = pos - m_first;
            resize (size()+1);
            iterator begin_pos = m_first+dist;
            for (int i=0; i<(m_last-begin_pos); i++)
                 *(m_last-i-1)=*(m_last-i-2); // сдвигаем с конца
            *begin_pos = value;
            return (m_first+dist); // итератор на value
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last){ // вставляет элементы из диапазона [first, last) перед элементом, на который указывает pos
        size_t dist = pos - m_first;
        iterator begin_pos = m_first+dist;
        for (int j=(last-first-1); j>=0; j--) //заполняем с наибольшего элемента
            begin_pos = insert (begin_pos, *(first+j));
        return (m_first+dist);
    }

    //push_back methods
    void push_back(const value_type& value) {
      insert (m_last, value);
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
}// namespace stepik
