#ifndef LIST_H
#define LIST_H

#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

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
        return *this;
      // implement this
    }

     bool operator == (const list_iterator& other) const
    {
        return (m_node == other.m_node);
      // implement this
    }

    bool operator != (const list_iterator& other) const
    {
       return (m_node != other.m_node)  ;
      // implement this
    }

    reference operator * ()
    {
      return (m_node->value);
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
      // implement this
      list_iterator* next = new list_iterator(*this);
      m_node = m_node->next;
      return *next;
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

    void clear()
    {
      while(!empty())
          pop_back();
    }

    bool empty() const
    {
      return !m_head;
    }

    list(const list& other):m_head(nullptr), m_tail(nullptr)
       {
           node<Type>* new_node = other.m_head;
           for (;new_node;new_node = new_node->next)
               push_back(new_node->value);
       }

       list(list&& other):m_head(nullptr), m_tail(nullptr)
       {
           std::swap(m_head, other.m_head);
           std::swap(m_tail, other.m_tail);
       }

       list& operator= (const list& other)
       {
         if (this != &other) {
               clear();
               node<Type>* new_node = other.m_head;
               for (;new_node;new_node = new_node->next)
               push_back(new_node->value);
         }
               return *this;
       }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

   void push_back(const value_type& value)
    {
        node<Type>* new_node = new node<Type>(value, nullptr, m_tail);
        if (!m_head) m_head = new_node;
        else m_tail->next = new_node;
        m_tail = new_node;
    }

    void push_front(const value_type& value)
    {
        node<Type>* new_node = new node<Type>(value, m_head, nullptr);
        if (!m_tail) m_tail = new_node;
        else m_head->prev = new_node;
        m_head = new_node;
    }

    void pop_front()
    {
      if (!m_head) return;
          node<Type>* new_head = m_head->next;
          delete m_head;
          if (new_head)
              new_head->prev = nullptr;
          else m_tail = new_head;
          m_head = new_head;
    }

    void pop_back()
    {
        if (!m_tail) return;
            node<Type>* new_tail = m_tail->prev;
            delete m_tail;
            if (new_tail)
                new_tail->next = nullptr;
            else m_head = new_tail;
            m_tail = new_tail;
    }

    iterator insert(iterator pos, const Type& value)
    {
        node<Type>* pos_node = pos.m_node;
        if (pos_node == nullptr) {
            push_back(value);
            return iterator(m_tail);
        }
        if (pos_node == m_head) {
            push_front(value);
            return begin();
        }
        node<Type>* new_node = new node<Type>(value, pos_node, pos_node->prev);
        pos_node->prev->next = new_node;
        pos_node->prev = new_node;
        return iterator(new_node);
    }

    iterator erase(iterator pos)
    {
          node<Type>* pos_node = pos.m_node;
          if (pos_node == nullptr)
                return pos;
          if (pos_node->prev == nullptr) {
                pop_front();
                return begin();
            }
            if (pos_node->next == nullptr) {
                pop_back();
                return end();
            }
            pos_node->prev->next = pos_node->next;
            pos_node->next->prev = pos_node->prev;
            iterator next_pos = iterator(pos_node->next);
            delete pos_node;
            return next_pos;
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


    size_t size() const
    {
        int size = 0;
        node<Type>* tmp = m_head;
        while (tmp) {
            tmp = tmp->next;
            size++;
        }
        return size;
      // implement this
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik

#endif // LIST_H
