#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik {
  template <class Type>
  struct node {
    Type value; //значение переменной
    node* next; //указатель на следующий элемент
    node* prev; //указатель на предыдущий элемент

    node(const Type& value, node<Type>* next, node<Type>* prev): value(value), next(next), prev(prev) {}
  };

  template <class Type>
  class list; //forward declaration

  template <class Type>
  class list_iterator {
  public:
    typedef ptrdiff_t difference_type; //можно использовать для представления количества элементов в списке в диапазоне между элементами
    typedef Type value_type; //тип данных элементов, сохраняемых в списке
    typedef Type* pointer; //указатель на элемент в списке
    typedef Type& reference; //ссылка на элемент в списке
    typedef size_t size_type; //количество элементов в списке
    typedef std::forward_iterator_tag iterator_category;

    list_iterator(): m_node(NULL) {}

    list_iterator(const list_iterator& other): m_node(other.m_node) {} //конструктор копирования

    list_iterator& operator = (const list_iterator& other) {
      m_node = other.m_node;
      return *this; 
    }

    bool operator == (const list_iterator& other) const {
      return (m_node == other.m_node);
    }

    bool operator != (const list_iterator& other) const {
      return m_node != other.m_node; 
    }

    reference operator * () {
      return m_node -> value;
    }

    pointer operator -> () {
      return &(m_node -> value);
    }

    list_iterator& operator ++ () {
      m_node = m_node -> next;
      return *this;
    }

    list_iterator operator ++ (int) {
      list_iterator temp(*this);
      ++(*this);
      return temp;
    }

  private:
    friend class list <Type>;
    list_iterator(node <Type> *p): m_node(p) {}
    node <Type> *m_node;
  };

  template <class Type>
  class list {
  public:
    typedef Type value_type; //тип данных элементов, сохраняемых в списке
    typedef value_type& reference; //тип, предоставляющий ссылку на элемент в списке
    typedef const value_type& const_reference; //не используется для изменения значения
    typedef list_iterator<Type> iterator;

    list(): m_head(nullptr), m_tail(nullptr) {} //конструктор по умолчанию

    ~list() { //деструктор
      clear();
    }

    list::iterator begin() {
      return iterator(m_head);
    }

    list::iterator end() {
      return iterator();
    }
    
    
    list(const list& other): list() { //конструктор копирования, создаёт контейнер с копией содержимого в other
      node <Type> *temp = other.m_head;
      while(temp) {
          push_back(temp -> value);
          temp = temp -> next;
      }
    }

    list(list&& other): m_head(other.m_head), m_tail(other.m_tail) { //конструктор перемещения
      other.m_head = other.m_tail = nullptr;
    }

    list& operator= (const list& other) { //оператор присваивания
      if(m_head == other.m_head) return *this;
      if(other.size()) {
        this -> clear();
        node <Type> *temp = other.m_head;
        while(temp) {
            push_back(temp -> value);
            temp = temp -> next;
        }
        return *this;
      }
      else {
          m_head = nullptr;
          m_tail = nullptr;
          return *this;
      }
    }

    void push_back(const value_type& value) { //вставка элемента в конец списка
      node <Type> *element = new node <Type> (value, nullptr, m_tail);
      if(empty()) {
          m_head = element;
          m_tail = m_head;
      }
      else {
          m_tail -> next = element;
          m_tail = element;
      }
    }
    
    void push_front(const value_type& value) { //вставка элемента в начало списка
      node <Type> *element = new node <Type> (value, m_head, nullptr);
      if(empty()) {
          m_head = element;
          m_tail = m_head;
      }
      else {
          m_head -> prev = element;
          m_head = element;
      }
    }

    iterator insert(iterator pos, const Type& value) { //вставка элемента
      if(pos.m_node == nullptr) { //end возвращает итератор на элемент, следующий за последним элементом контейнера
          push_back(value);
          return iterator(m_tail);
      }
      if(pos == begin()) { //begin возвращает итератор на первый элемент 
          push_front(value);
          return iterator(m_head);
      }
      node <Type> *tmp = pos.m_node -> prev;
      pos.m_node -> prev = new node <Type> (value, pos.m_node, tmp);
      tmp -> next = pos.m_node -> prev;
      return iterator(pos.m_node -> prev);
    }

    iterator erase(iterator pos) { //удаление элементов
      if (pos.m_node -> next == nullptr) {
          pop_back();
          return iterator(m_tail);
        }
      if (pos == begin()) {
          pop_front();
          return iterator(m_head);
      }
      node <Type> *tmp = pos.m_node;
      delete pos.m_node;
      tmp -> prev -> next = tmp -> next;
      tmp -> next -> prev = tmp -> prev;
      return tmp -> next;  
    }

    reference front() { //возвращает ссылку на первый элемент в списке
      if(!empty()) return (m_head -> value);
    }
    
    const_reference front() const {
      if(!empty()) return (m_head -> value);  
    }

    reference back() { //возвращает ссылку на последний элемент в списке
      if(!empty()) return (m_tail -> value);
    }
    
    const_reference back() const {
      if(!empty()) return (m_tail -> value);  
    }
    
    void pop_front() { //удаляет элемент в начале списка
      node <Type> *element = m_head;
      if(size()==1) 
          m_head = m_tail = nullptr;
      else {
          m_head -> next -> prev = nullptr;
          m_head = m_head -> next;
      }
      delete element;
    }

    void pop_back() { //удаляет элемент в конце списка
      node <Type> *element = m_tail;
      if(size()==1) 
          m_head = m_tail = nullptr;
      else {
          m_tail -> prev -> next = nullptr;
          m_tail = m_tail -> prev;
      }
      delete element;
    }

    void clear() { //очистка списка
      while(m_head) 
          pop_back();
      m_head = m_tail = nullptr;      
    }

    bool empty() const { //пуст ли список?
      return (m_head == nullptr);
    }

    size_t size() const { //текущая длина списка
      size_t size = 0;
      node <Type> *element = m_head;
      while (element) {
          size++;
          element = element -> next;
      }
      return size;
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
