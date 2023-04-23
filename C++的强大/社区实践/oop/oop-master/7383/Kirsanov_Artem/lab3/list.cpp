#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <iostream>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
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

    list_iterator()
      : m_node(NULL)
    {
    }

    list_iterator(const list_iterator& other)
      : m_node(other.m_node)
    {
    }

    list_iterator& operator = (const list_iterator& other)
    {
        m_node = other.m_node;
    }

    bool operator == (const list_iterator& other) const
    {
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        return m_node != other.m_node;
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        list_iterator<value_type> tmp = *this;
        m_node = tmp.m_node->next;
        return *this;
    }

    list_iterator& operator -- ()
    {
        m_node = m_node->prev;
        return *this;
    }
    list_iterator& operator -- (int)
    {
        list_iterator<value_type> tmp = *this;
        m_node = tmp.m_node->prev;
        return *this;
    }

  private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
      : m_node(p)
    {
    }

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

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
        clear();
    }

    list(const list& other)
        : m_head(nullptr), m_tail(nullptr)
    {
        iterator it = other.begin();
        while (it.m_node) {
            push_back(it.m_node->value);
            it++;
        }
    }

    list(list&& other)
        : m_head(other.m_head), m_tail(other.m_tail)
    {
        other.m_head = other.m_tail = nullptr;
    }

    list& operator = (const list& other)
    {
        if(m_head == other.m_head) return *this;
        clear();
        list* tmp = new list(other);
        m_head = tmp->m_head;
        m_tail = tmp->m_tail;
        return *this;
    }

    void push_back(const value_type& value)
    {
        value_type tmpval = value;
        if(empty()){
            m_head = new node<value_type>(tmpval, nullptr, nullptr);
            m_tail = m_head;
        }
        else{
            m_tail->next = new node<value_type>(tmpval, nullptr, m_tail);
            m_tail = m_tail->next;
        }
    }

    void push_front(const value_type& value)
    {
        value_type tmpval = value;
        if(empty()){
            m_head = new node<value_type>(tmpval, nullptr, nullptr);
            m_tail = m_head;
        }
        else{
            m_head->prev = new node<value_type>(tmpval, m_head, nullptr);
            m_head = m_head->prev;
        }
    }

    void pop_front()
    {
        if(empty())
            return;
        if(m_head -> next == nullptr){
            delete m_head;
            m_tail = m_head = nullptr;
        }
        else{
            m_head = m_head -> next;
            delete m_head -> prev;
            m_head -> prev = nullptr;
        }
    }

    void pop_back()
    {
        if(empty())
            return;
        if(m_tail -> prev == nullptr){
            delete m_head;
            m_head = m_tail = nullptr;
        }
        else{
            m_tail = m_tail -> prev;
            delete m_tail->next;
            m_tail->next = nullptr;
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(empty() || pos == m_head){
            push_front(value);
            pos.m_node->prev = m_head;
            return --pos;
        }
        else{
            pos.m_node = new node<value_type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node -> prev -> next = pos.m_node;
            pos.m_node -> next -> prev = pos.m_node;
            return pos;
        }
    }

    iterator erase(iterator pos)
    {
        if(empty()) return nullptr;
        if(pos == m_head){
            pop_back();
            return pos;
        }
        if(pos == m_tail){
            pop_front();
            return --pos;
        }
        node<value_type>* tmp = pos.m_node;
        tmp -> prev -> next = tmp -> next;
        tmp -> next -> prev = tmp -> prev;
        delete tmp;
        return ++pos;
    }

    reference front()
    {
        return m_head->value;
    }

    const_reference front() const
    {
        return m_head->value;
    }

    reference back()
    {
        return m_tail->value;
    }

    const_reference back() const
    {
        return m_tail->value;
    }

    list::iterator begin()
    {
        return iterator(m_head);
    }

    list::iterator begin() const
    {
        return iterator(m_head);
    }

    list::iterator end()
    {
        return iterator();
    }

    bool empty() const
    {
        return m_head == nullptr;
    }

    size_t size() const
    {
        size_t size = 0;
        iterator it = begin();
        while (it.m_node) {
            it++;
            size++;
        }
        return size;
    }

    void clear()
    {
        while (!empty())
            pop_back();
    }

  private:
    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik
