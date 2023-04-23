#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>


template <class Type>
struct node
{
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev) : value(value), next(next), prev(prev)
    {}
};


template <class Type>
class list; //forward declaration

template <class Type>
class list_iterator
{
public:
  typedef ptrdiff_t difference_type;
  typedef Type value_type;
  typedef Type* pointer;
  typedef Type& reference;
  typedef size_t size_type;
  typedef std::forward_iterator_tag iterator_category;

  list_iterator() : m_node(NULL)
  {}

  // Конструктор копирования
  list_iterator(const list_iterator& other) : m_node(other.m_node)
  {}

  // Оператор присваивания
  list_iterator& operator = (const list_iterator& other)
  {
      m_node = other.m_node;
      return *this;
  }

  // Оператор сравнения
  bool operator == (const list_iterator& other) const
  {
        return m_node == other.m_node;
  }

  // Оператор сравнения
  bool operator != (const list_iterator& other) const
  {
        return m_node != other.m_node;
  }

  // Ссылка на хранимое
  reference operator * ()
  {
        return m_node->value;
  }

  // Указатель на хранимое
  pointer operator -> ()
  {
        return &(m_node->value);
  }

  // ++object
  list_iterator& operator ++ ()
  {
     m_node = m_node->next;

     return *this;
  }

  // object++
  list_iterator operator ++ (int)
  {
     auto ret = *this;

     m_node = m_node->next;

     return ret;
  }

private:
  friend class list<Type>;

  list_iterator(node<Type>* p) : m_node(p)
  {}

  node<Type>* m_node;
};


template <class Type>
class list
{
public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list() : m_head(nullptr), m_tail(nullptr)
    {}

/////////////////////////////////////////////////
    ~list()
    {
          clear();
    }

	// Конструктор копирования
    list(const list& other)
    {
          for ( auto c = other.m_head; c != NULL; c = c->next)
              push_back(c->value);
    }

	// Конструктор перемещения
    list(list&& other)
    {
          m_head = other.m_head;
          m_tail = other.m_tail;

          other.m_head = other.m_tail = NULL;
    }

	// Оператор присваивания
    list& operator= (const list& other)
    {
        if ( this == &other ) return *this;
        clear();

        for ( auto c = other.m_head; c != NULL; c = c->next)
            push_back(c->value);

        return *this;
    }

/////////////////////////////////////////////////
    // Вставить в конец
    void push_back(const value_type& value)
    {
        if ( empty() )
        {
            m_head = m_tail = new node<Type>( value, NULL, NULL);
            return;
        }
        m_tail->next = new node<Type>( value, NULL, m_tail);
        m_tail = m_tail->next;
    }

    // Вставить в начало
    void push_front(const value_type& value)
    {
        if ( empty() )
        {
            m_head = m_tail = new node<Type>( value, NULL, NULL);
            return;
        }
        m_head->prev = new node<Type>( value, m_head, NULL);
        m_head = m_head->prev;
    }

    // Доступ к первому элементу
    reference front()
    {
      return m_head->value;
    }

    // Недодоступ к первому элементу
    const_reference front() const
    {
      return m_head->value;
    }

    // Доступ к последнему элементу
    reference back()
    {
      return m_tail->value;
    }

    // Недодоступ к последнему элементу
    const_reference back() const
    {
      return m_tail->value;
    }

    //Удаляет первый элемент
    void pop_front()
    {
        if (m_head == NULL) return;
        if (m_head==m_tail)
        {
            delete m_head;
            m_head = m_tail = NULL;
            return;
        }
        m_head = m_head->next;
        delete m_head->prev;
        m_head->prev = NULL;
    }

    //Удаляет последний элемент
    void pop_back()
    {
        if (m_tail == NULL) return;
        if (m_head==m_tail)
        {
            delete m_head;
            m_head = m_tail = NULL;
            return;
        }
        m_tail = m_tail->prev;
        delete m_tail->next;
        m_tail->next = NULL;
    }

    // Полное очищение
    void clear()
    {
          while ( !empty() )
              pop_front();
    }

    // Пуст?
    bool empty() const
    {
        return m_tail==NULL;
    }

	// Размер списка
    size_t size() const
    {
        size_t i = 0;

        node<Type> *a = m_head;

        while( a != NULL)
        {
            i++;
            a = a->next;
        }
        return i;
    }


//////////////////////////////////////////////

    //Вставляет value перед элементом, на который указывает pos.
    iterator insert(iterator pos, const Type& value)
    {
          if (pos.m_node == NULL)
          {
              push_back( value);
              return iterator(m_tail);
          }
          if (pos.m_node == m_head)
          {
              push_front(value);
              return iterator(m_head);
          }

          pos.m_node->prev->next = new node<Type>( value, pos.m_node, pos.m_node->prev);
          pos.m_node->prev = pos.m_node->prev->next;

          return iterator(pos.m_node->prev);
    }

	// Удалить pos
    iterator erase(iterator pos)
    {
          if ( pos.m_node == m_head)
          {
              pop_front();
              return iterator(m_head);
          }

          if ( pos.m_node == m_tail)
          {
              pop_back();
              return iterator(m_tail);
          }

          node<Type> *ret = pos.m_node->next;
          ret->prev = pos.m_node->prev;
          ret->prev->next = ret;

          delete pos.m_node;

          return iterator(ret);
    }

/////////////////////////////////////////////////////
    void write()
    {
        node<Type> *writter = m_head;

        while(writter!=NULL)
        {
            std::cout << writter->value <<"\n";
            writter = writter->next;
        }
    }

//////////////////////////////// ниндзи
    iterator begin()
        {
          return iterator(m_head);
        }

     iterator end()
        {
          return iterator();
        }



  private:

    node<Type>* m_head = NULL;
    node<Type>* m_tail = NULL;
  };
