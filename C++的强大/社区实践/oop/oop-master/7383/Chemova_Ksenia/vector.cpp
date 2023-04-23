#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik{
  template <typename Type>
  class vector{
  public:
    typedef Type* iterator; //используется для обращения к определённому элементу в контейнерах
    typedef const Type* const_iterator; //если контейнер представлет константу, такой итератор считывает элементы, но не изменяет их

    typedef Type value_type; //тип, представляющий тип данных, хранящихся в векторе.

    typedef value_type& reference; //тип, предоставляющий ссылку на элемент, хранящийся в векторе.
    typedef const value_type& const_reference; //тип, предоставляющий ссылку на элемент const, для чтения и выполнения операций с элементами const.

    typedef std::ptrdiff_t difference_type; //тип, предоставляющий разницу между двумя итераторами, ссылающимися на элементы в одном и том же векторе.

    explicit vector(size_t count = 0) : m_first(new Type[count]), m_last(m_first + count){ } //создание нового контейнера диапазоном (m_first, m_last), используя аллокатор (new)

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last): vector(last - first){
      std::copy(first, last, m_first); //(first, last) - диапазон копируемых элементов, m_first - куда копируем; создаёт вектор из элементов лежащих между first и last
    }

    vector(std::initializer_list <Type> init){ //для возможности использования в данном контейнерном классе списока инициализации
      if (init.size()){
        m_first = new value_type[init.size()];
        std::copy(init.begin(), init.end(), m_first);
        m_last = m_first + init.size();
      }
      else{
        m_last = nullptr;  //итератор на последний элемент
        m_first = nullptr; //итератор на первый элемент
        return;
      }
    }

    vector(const vector& other): vector(other.size()) { //конструктор копирования
      std:: copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other) { //конструктор перемещения
      m_first = other.begin();
      m_last = other.end();
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector() { //деструктор
      if (!empty()){
        delete[] m_first;
        m_first = m_last = nullptr;
      }
    }

    //операторы присваивания
    vector& operator=(const vector& other) { //заменяет содержимое текущего контейнера на содержимое other
      delete[] m_first;
      m_first = new Type[other.size()];
      m_last = m_first + other.size();
      std:: copy(other.begin(), other.end(), m_first);
      return *this;
    }

    vector& operator=(vector&& other) { //замена местами двух контейнеров
      std::swap(m_first, other.m_first);
      std::swap(m_last, other.m_last);
      return *this;
    }

    template <typename InputIterator> //заменяет содержимое с тем, что находится в диапазоне (first, last)
    void assign(InputIterator first, InputIterator last) {
      delete[] m_first;
      m_first = new Type[last - first]; //last - first = size
      m_last = m_first + (last - first);
      std:: copy(first, last, m_first);
    }
    // resize methods, изменяет размер контейнера
    void resize(size_t count) {
      if(count == size()) return; //m_last - m_first - текущий размер
      iterator temp = new value_type[count]; //создали указатель на новый массив
      if(count < size()) std:: copy (m_first, (m_first + count), temp); //сместили итератор конца вектора
      else std:: copy (m_first, m_last, temp);
      delete[] m_first;
      m_first = temp;
      m_last = m_first + count;
    }

    //erase methods, удаляет элемент в текущей позиции
    iterator erase(const_iterator pos) {
      size_t size = m_last - m_first;
      size_t index = pos - m_first;
      for (size_t i = index; i < size - 1; i++)
        m_first[i] = m_first[i + 1];
      m_last = m_first + size - 1;
      resize(size - 1);
      return m_first + index; //итератор, следующий за последним удаленным элементом
    }

    iterator erase(const_iterator first, const_iterator last) { //удаляет элементы в диапазоне
      size_t size = m_last - m_first;
      size_t size_ = last - first;
      size_t index = first - m_first;
      for (size_t i = index; i < size - size_; i++)
        m_first[i] = m_first[i + size_];
      resize(size - size_);
      return m_first + index;
    }

    //insert methods, вставка
    iterator insert(const_iterator pos, const Type& value){
    //вставляет переменную перед элементом, на который указывает pos
      size_t index = pos - m_first;
      size_t new_size = size() + 1;
      resize(new_size);
      std::copy(m_first + index, m_last, m_first + index + 1);
      m_first[index] = value;
      return m_first + index;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last){ //вставляет элементы из диапазона перед элементом, на который указывает pos
      size_t size = m_last - m_first;
      size_t size_add = last - first;
      size_t index = pos - m_first;
      Type new_arr[size];
      std::copy(m_first, m_last, new_arr);
      resize(size + size_add);
      std::copy(new_arr, new_arr + index, m_first); //записываем первую часть до pos
      std::copy(first, last, m_first + index); //вставка
      std::copy(new_arr + index, new_arr + size, m_first + index + size_add); //записываем оставшуюся часть
      return m_first + index;
    }

    //push_back methods, вставка в конец вектора
    void push_back(const value_type& value) {
      insert(m_last, value);
    }

    reference at(size_t pos) {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos) {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const {
      return m_first[pos];
    }

    //*begin methods
    iterator begin() {
      return m_first;
    }

    const_iterator begin() const{
      return m_first;
    }

    //*end methods
    iterator end() {
      return m_last;
    }

    const_iterator end() const{
      return m_last;
    }

    //size method
    size_t size() const{
      return m_last - m_first;
    }

    //empty method
    bool empty() const{
      return m_first == m_last;
    }

  private:
    reference checkIndexAndGet(size_t pos) const{
      if (pos >= size()){
        throw std::out_of_range("out of range");
      }
      return m_first[pos];
    }

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik
